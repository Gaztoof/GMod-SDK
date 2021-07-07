#pragma once
#include <Windows.h>
#include "../globals.h"
#include "menu/drawing.h"
#include "Utils.h"

void doEsp()
{
	for (int i = 0; i < ClientEntityList->GetHighestEntityIndex(); i++)
	{
		C_BasePlayer* entity = (C_BasePlayer*)ClientEntityList->GetClientEntity(i);
		if (entity == nullptr || entity == localPlayer || entity->getTeamNum() == 1002) // https://wiki.facepunch.com/gmod/Enums/TEAM
			continue;
		if (!Settings::ESP::espDormant && entity->IsDormant())
			continue;

		bool isEntity = false;
		const char* entName = GetClassName(entity);

		Settings::luaEntListMutex.lock();
		if(Settings::ESP::entEsp)
		for (auto var : Settings::luaEntList)
		{
			if (!strcmp(var.first, entName) && var.second)
			{
				isEntity = true;
				break;
			}
		}
		Settings::luaEntListMutex.unlock();

		if (!isEntity && (!entity->IsPlayer() || !entity->IsAlive()))
			continue;

		Vector screenPos;
		Vector screenTopPos;

		Vector hisOrigPos = entity->GetAbsOrigin();
		Vector hisPos;
		Vector hisEyePos;
		entity->GetCollideable()->WorldSpaceTriggerBounds(&hisPos, &hisEyePos);
		if (WorldToScreen(hisPos, screenPos) &&
			WorldToScreen(hisEyePos, screenTopPos))
		{
			if (isEntity)
			{
				DrawTextW(Vector(screenTopPos.x, screenPos.y, 0), StringToWString(std::string(entName)), 0xFFFFFFFF, true);

				if (Settings::ESP::espShapeInt == 0)
					DrawEsp2D(screenPos, screenTopPos, D3DCOLOR_ARGB((uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[3] * 255), (uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[0] * 255), (uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[1] * 255), (uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[2] * 255)));
				else if (Settings::ESP::espShapeInt == 1)
					DrawEspBox3D(hisEyePos, hisPos, entity->EyeAngles().y, D3DCOLOR_ARGB((uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[3] * 255), (uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[0] * 255), (uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[1] * 255), (uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[2] * 255)));
				continue;
			}

			matrix3x4_t bones[128];
			if(((Settings::ESP::skeletonEsp) || Settings::Aimbot::drawAimbotHeadlines)  && // Sometimes SetupBones will crash, and so adding these checks won't make you crash at round beginning if you disable features that need setupbones
				((uintptr_t)entity->GetClientRenderable() < 0x1000 ||
				!entity->GetClientRenderable()->SetupBones(bones, 128, BONE_USED_BY_HITBOX, EngineClient->Time())))
				continue;

			int z = -1;

			studiohdr_t* studioHdr = ModelInfo->GetStudiomodel((const model_t*)entity->GetClientRenderable()->GetModel());

			if(Settings::ESP::skeletonEsp)
			for (int z = 0; z < studioHdr->numbones; z++)
			{
				auto bone = studioHdr->pBone(z);
				if (bone && bone->parent >= 0)
				{
					if (!Settings::ESP::skeletonDetails && !(bone->flags & 256))
						continue;
					Vector normalBonePos = Vector(bones[z][0][3], bones[z][1][3], bones[z][2][3]);
					Vector normalParentBonePos = Vector(bones[bone->parent][0][3], bones[bone->parent][1][3], bones[bone->parent][2][3]);
					if (normalBonePos == Vector(0, 0, 0) || normalParentBonePos == Vector(0, 0, 0))
						continue;

					Vector bonePosFrom;
					Vector parentBonePos;
					if (!WorldToScreen(normalBonePos, bonePosFrom) || !WorldToScreen(normalParentBonePos, parentBonePos))
						continue;
					DrawLine(bonePosFrom, parentBonePos, D3DCOLOR_ARGB((uint8_t)(Settings::ESP::skeletonEspColor.fCol[3] * 255), (uint8_t)(Settings::ESP::skeletonEspColor.fCol[0] * 255), (uint8_t)(Settings::ESP::skeletonEspColor.fCol[1] * 255), (uint8_t)(Settings::ESP::skeletonEspColor.fCol[2] * 255)));
					//DrawTextW(bonePosFrom, std::to_wstring(z), 0xFFFFFFFF, true); // write bone ids
				}
			}
			
			int selectedHitBox = 0; // that crashes x86
			Studio_BoneIndexByName(studioHdr, IntToBoneName(Settings::Aimbot::aimbotHitbox), &selectedHitBox);

			Vector screenEyePos;
			screenEyePos.z = 0;
			if (Settings::Aimbot::drawAimbotHeadlines && WorldToScreen(Vector(bones[selectedHitBox][0][3], bones[selectedHitBox][1][3], bones[selectedHitBox][2][3]), screenEyePos) && Vector(screenWidth / 2, screenHeight / 2, 0).DistTo(screenEyePos) < Settings::Aimbot::aimbotFOV)
			{
				int color = entity == Settings::Aimbot::finalTarget ? 0xFF3333FF : 0xFFFFFFFF;
				DrawLine(Vector(screenWidth / 2, screenHeight / 2, 0), screenEyePos, color);
			}

			player_info_s info;
			EngineClient->GetPlayerInfo(i, &info);

			Vector hisHeadPos;
			Vector hisBottom;
			if (WorldToScreen(entity->GetAbsOrigin(), hisBottom) && WorldToScreen(entity->EyePosition(), hisHeadPos))
			{
				std::wstring playerInfo = L"";
				if (Settings::ESP::espName)
					playerInfo = StringToWString(info.name) + L"\n";

				if (Settings::ESP::weaponText)
				{
					const char* weaponName = "";
					if (entity->GetActiveWeapon())
					{
						playerInfo += L"Weapon: " + StringToWString(entity->GetActiveWeapon()->GetName()) + L"\n";
					}
				}
				if (Settings::ESP::espHealthBar)
				{
					playerInfo += L"Health: " + std::to_wstring(entity->GetHealth()) + L"/" + std::to_wstring(entity->GetMaxHealth()) + L"\n";
				}
				if (Settings::ESP::weaponAmmo)
				{
					playerInfo += L"Ammos: " + std::to_wstring(entity->GetActiveWeapon()->PrimaryAmmoCount()) + L"\n";
				}
				if (Settings::ESP::espDistance)
				{
					playerInfo += L"Distance: " + std::to_wstring((int)entity->GetAbsOrigin().DistTo(localPlayer->GetAbsOrigin())) + L"\n";
				}

				if (playerInfo.length() > 1)
				{
					Vector pos;
					switch (Settings::ESP::infosEmplacement)
					{
					case 0: // Above
						pos = Vector(hisHeadPos.x , hisHeadPos.y, 0);
						break;
					case 1: // Below
						pos = Vector(hisHeadPos.x, hisBottom.y, 0);
						break;
					case 2: // Right
						pos = Vector(hisHeadPos.x - (hisHeadPos.y - hisBottom.y) / 4, hisHeadPos.y, 0);
						break;
					case 3: // Left
						pos = Vector(hisHeadPos.x - (hisHeadPos.y - hisBottom.y) / 4, hisHeadPos.y, 0);
						break;
					}
					DrawTextW(pos, playerInfo, 0xFFFFFFFF, true);
				}
				if (Settings::ESP::espBoundingBox)
				{
					if (Settings::ESP::espShapeInt == 0)
						DrawEsp2D(hisBottom, hisHeadPos, D3DCOLOR_ARGB((uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[3] * 255), (uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[0] * 255), (uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[1] * 255), (uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[2] * 255)));
					else if (Settings::ESP::espShapeInt == 1)
						DrawEspBox3D(hisEyePos, hisPos, entity->EyeAngles().y, D3DCOLOR_ARGB((uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[3] * 255), (uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[0] * 255), (uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[1] * 255), (uint8_t)(Settings::ESP::espBoundingBoxColor.fCol[2] * 255)));
				}
			}
		}
		
	}


}