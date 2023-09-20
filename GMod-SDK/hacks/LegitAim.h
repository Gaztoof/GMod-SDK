#pragma once

#include <Windows.h>
#include "../globals.hpp"
#include "AutoWall.h"
#include "Utils.h"
	
void DoLegitAimbot(CUserCmd* cmd)
{
	static C_BasePlayer* lastTarget = nullptr;
	static bool tempState = false;
	static int smoothSteps = 0;

	bool keyDown;
	getKeyState(Settings::Aimbot::aimbotKey, Settings::Aimbot::aimbotKeyStyle, &keyDown, henlo1, henlo2, henlo3);

	if (!keyDown || !Settings::Aimbot::enableAimbot) { Settings::Aimbot::finalTarget = nullptr; smoothSteps = 0; return; }

	if (Settings::Aimbot::lockOnTarget && (Settings::Aimbot::finalTarget && !Settings::Aimbot::finalTarget->IsAlive()))Settings::Aimbot::finalTarget = localPlayer;
	if (Settings::Aimbot::finalTarget == localPlayer) { smoothSteps = 0; return; }

	int selectedHitBox = 0;

	Vector eyePos = localPlayer->EyePosition();
	Vector finalPos;
	bool isErrorModel = false;
	bool canHit = false;
	if (!Settings::Aimbot::lockOnTarget || !Settings::Aimbot::finalTarget || !Settings::Aimbot::finalTarget->IsAlive() || Settings::Aimbot::finalTarget->IsDormant()) // isNotLock or if final is bad, or dead
	{
		Settings::Aimbot::finalTarget = nullptr;
		float finalDistance = FLT_MAX;
		for (int i = 0; i < ClientEntityList->GetHighestEntityIndex(); i++)
		{
			C_BasePlayer* entity = (C_BasePlayer*)ClientEntityList->GetClientEntity(i);
			if (!entity || !entity->IsAlive() || !entity->IsPlayer() || entity == localPlayer || entity->IsDormant())
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

			// This is an exemple of something you can do for a custom server.
			/*entity->PushEntity();
				Lua->GetField(-1, "GetNWInt");
				Lua->Push(-2);

				Lua->PushString("Buildmode");
				Lua->Call(2, 1);
				int buildMode = Lua->GetNumber(-1);
				Lua->Pop(2);
			if (buildMode) continue;*/
#pragma message("THIS IS TO BE TESTED!!")
			Vector entPos;
			auto model = ((model_t*)entity->GetClientRenderable()->GetModel());
			if (model && !_strcmpi(ModelInfo->GetStudiomodel(model)->name, "error.mdl"))
			{
				entPos = entity->EyePosition();
				isErrorModel = true;
			}
			else {
				// https://i.imgur.com/0WZNkbC.jpg
				// https://i.imgur.com/rRxWCUN.jpeg
				// 6 head
				// 3 torso

				isErrorModel = false;
				matrix3x4_t bones[128];
				if (!entity->GetClientRenderable()->SetupBones(bones, 128, BONE_USED_BY_HITBOX, GlobalVars->curtime))
					continue;
				//std::cout << ((model_t*)entity->GetClientRenderable()->GetModel())->name << std::endl;
				auto bone = Studio_BoneIndexByName(ModelInfo->GetStudiomodel((const model_t*)entity->GetClientRenderable()->GetModel()), IntToBoneName(Settings::Aimbot::aimbotHitbox), &selectedHitBox);

				entPos = Vector(bones[selectedHitBox][0][3], bones[selectedHitBox][1][3], bones[selectedHitBox][2][3]); // 6 = hitbox https://i.imgur.com/0WZNkbC.jpg
			}
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
				distance = Vector(Globals::screenWidth / 2, Globals::screenHeight / 2, 0).DistTo(screenPos);
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
					fovDistance = Vector(Globals::screenWidth / 2, Globals::screenHeight / 2, 0).DistTo(screenPos);
				}
				if (fovDistance > Settings::Aimbot::aimbotFOV)
					continue;
			}

			finalPos = entPos;
			finalDistance = distance;
			Settings::Aimbot::finalTarget = entity;
		}
	}

	if (Settings::Aimbot::finalTarget && Settings::Aimbot::finalTarget->IsAlive())
	{
		QAngle calc = finalPos.AngleTo(eyePos);
		canHit = CanHit(Settings::Aimbot::finalTarget, eyePos, finalPos);

		bool shouldFire = true;
		if (lastTarget != Settings::Aimbot::finalTarget)
			smoothSteps = 0;
		

		if (Settings::Aimbot::smoothing && !Settings::Aimbot::silentAim)
		{
			smoothSteps++;

			if (smoothSteps >= Settings::Aimbot::smoothSteps)
				shouldFire = true;
			else {
				shouldFire = false;
			}
			auto delta = calc - cmd->viewangles;
			auto smoothed = cmd->viewangles + (delta * (1.f / Settings::Aimbot::smoothSteps));

			calc = smoothed;
		}

		// it is better to use smoothing without silent aim.
		if (!Settings::Aimbot::silentAim)
		{
				EngineClient->SetViewAngles(calc);
		}

		if (Settings::Aimbot::aimbotAutoFire && shouldFire)
		{
			if (canHit)
			{
				static bool toggle = false;
				toggle = !toggle;
				if (toggle)
				{
					cmd->buttons |= IN_ATTACK;
				}
				else if (Settings::Aimbot::pistolFastShoot)cmd->buttons &= ~IN_ATTACK;
			}
		}

		if (cmd->buttons & IN_ATTACK)
		{
			cmd->viewangles = calc;
			if(Settings::Aimbot::silentAim)
				*Globals::bSendpacket = false;
		}

	} else smoothSteps = 0;
	lastTarget = Settings::Aimbot::finalTarget;

}