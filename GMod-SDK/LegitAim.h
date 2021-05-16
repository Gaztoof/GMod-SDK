#pragma once

#include <Windows.h>
#include "globals.h"
#include "AutoWall.h"
#include "Utils.h"
	
void DoLegitAimbot(CUserCmd* cmd)
{
	static bool tempState = false;

	bool keyDown;
	getKeyState(Settings::Aimbot::aimbotKey, Settings::Aimbot::aimbotKeyStyle, &keyDown, henlo1, henlo2, henlo3);

	if (!keyDown || !Settings::Aimbot::enableAimbot) { Settings::Aimbot::finalTarget = nullptr; return; }

	if (Settings::Aimbot::lockOnTarget && (Settings::Aimbot::finalTarget && !Settings::Aimbot::finalTarget->IsAlive()))Settings::Aimbot::finalTarget = localPlayer;
	if (Settings::Aimbot::finalTarget == localPlayer) return;

	int selectedHitBox = 0;

	Vector eyePos = localPlayer->EyePosition();
	bool canHit = false;
	if (!Settings::Aimbot::lockOnTarget || !Settings::Aimbot::finalTarget || !Settings::Aimbot::finalTarget->IsAlive()) // isNotLock or if final is bad, or dead
	{
		Settings::Aimbot::finalTarget = nullptr;
		float finalDistance = FLT_MAX;
		for (int i = 0; i < ClientEntityList->GetHighestEntityIndex(); i++)
		{
			C_BasePlayer* entity = (C_BasePlayer*)ClientEntityList->GetClientEntity(i);
			if (!entity || !entity->IsAlive() || !entity->IsPlayer() || entity == localPlayer)
				continue;

			if (!Settings::Aimbot::aimAtTeammates && entity->getTeamNum() == localPlayer->getTeamNum())
				continue;
			bool isFriend = false;
			Settings::friendListMutex.lock();
			for (auto var : Settings::friendList)
			{
				if (var.first == entity && var.second.first)
				{
					isFriend = true;
					break;
				}
			}
			Settings::friendListMutex.unlock();

			if (isFriend && !Settings::Aimbot::aimAtFriends && !Settings::Aimbot::onlyAimAtFriends)
				continue;
			if (Settings::Aimbot::onlyAimAtFriends && !isFriend)
				continue;

			matrix3x4_t bones[128];
			if (!entity->GetClientRenderable()->SetupBones(bones, 128, BONE_USED_BY_HITBOX, GlobalVars->curtime))
				continue;

			auto bone = Studio_BoneIndexByName(ModelInfo->GetStudiomodel((const model_t*)entity->GetClientRenderable()->GetModel()), IntToBoneName(Settings::Aimbot::aimbotHitbox),&selectedHitBox);

			Vector entPos = Vector(bones[selectedHitBox][0][3], bones[selectedHitBox][1][3], bones[selectedHitBox][2][3]); // 6 = hitbox https://i.imgur.com/0WZNkbC.jpg
			canHit = CanHit(entity, eyePos, entPos);
			if (!canHit && Settings::Aimbot::aimbotAutoWall)
				continue;
			if (!Settings::Aimbot::aimAtFriends && Settings::friendList.find(entity) != Settings::friendList.find(entity))
				continue;


			float distance = FLT_MAX;
			float fovDistance = FLT_MAX;
			if (Settings::Aimbot::aimbotSelection == 0) // Distance
			{
				distance = localPlayer->GetAbsOrigin().DistTo(entPos);
				if (distance > finalDistance)
					continue;
			}
			else if (Settings::Aimbot::aimbotSelection == 1) // Health
			{
				distance = entity->GetHealth();
				if (distance > finalDistance)
					continue;
			}
			else if (Settings::Aimbot::aimbotSelection == 2) // FOV
			{
				const VMatrix viewMatrix = EngineClient->WorldToScreenMatrix();
				Vector screenPos;
				if (!WorldToScreen(entPos, screenPos))
					continue;
				screenPos.z = 0;
				distance = Vector(screenWidth / 2, screenHeight / 2, 0).DistTo(screenPos);
				fovDistance = distance;
				if (distance > finalDistance)
					continue;
			}
			// do min damage sorting here with ray tracing
			if (Settings::Aimbot::aimbotFovEnabled)
			{
				if (fovDistance == FLT_MAX)
				{
					const VMatrix viewMatrix = EngineClient->WorldToScreenMatrix();
					Vector screenPos;
					if (!WorldToScreen(entPos, screenPos))
						continue;
					screenPos.z = 0;
					fovDistance = Vector(screenWidth / 2, screenHeight / 2, 0).DistTo(screenPos);
				}
				if (fovDistance > Settings::Aimbot::aimbotFOV)
					continue;
			}

			finalDistance = distance;
			Settings::Aimbot::finalTarget = entity;
		}
	}

	if (Settings::Aimbot::finalTarget && Settings::Aimbot::finalTarget->IsAlive())
	{
		matrix3x4_t b[128];
		if (!Settings::Aimbot::finalTarget->GetClientRenderable()->SetupBones(b, 128, BONE_USED_BY_HITBOX, GlobalVars->curtime))
			return;

		Studio_BoneIndexByName(ModelInfo->GetStudiomodel((const model_t*)Settings::Aimbot::finalTarget->GetClientRenderable()->GetModel()), IntToBoneName(Settings::Aimbot::aimbotHitbox), &selectedHitBox);

		// https://i.imgur.com/0WZNkbC.jpg
		// https://i.imgur.com/rRxWCUN.jpeg
		// 6 head
		// 3 torso
		Vector targetPos = Vector(b[selectedHitBox][0][3], b[selectedHitBox][1][3], b[selectedHitBox][2][3]);
		//targetPos += (finalTarget->getVelocity() / 15);
		QAngle calc = targetPos.AngleTo(eyePos);
		canHit = CanHit(Settings::Aimbot::finalTarget, eyePos, targetPos);

		if (Settings::Aimbot::aimbotAutoFire)
		{
			if (canHit)
			{
				static bool toggle = false;
				toggle = !toggle;
				if (toggle)
					cmd->buttons |= IN_ATTACK;
				else cmd->buttons &= ~IN_ATTACK;
			}
		}

		if(cmd->buttons & IN_ATTACK)
		cmd->viewangles = calc;

		if (!Settings::Aimbot::silentAim)
			EngineClient->SetViewAngles(calc);
	}
}