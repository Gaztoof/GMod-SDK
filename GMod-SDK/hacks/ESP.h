#pragma once
#include <Windows.h>
#include "../globals.hpp"
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

		Vector entityAbsOrig = entity->GetAbsOrigin();
		Vector targetMinS;
		Vector targetMaxS;

		 rainbowColor(Settings::ESP::espNameColor, Settings::Misc::rainbowSpeed);
		 rainbowColor(Settings::ESP::espBoundingBoxColor, Settings::Misc::rainbowSpeed);
		 rainbowColor(Settings::ESP::skeletonEspColor, Settings::Misc::rainbowSpeed);
		 rainbowColor(Settings::ESP::espWeaponColor, Settings::Misc::rainbowSpeed);
		 rainbowColor(Settings::ESP::espHealthColor, Settings::Misc::rainbowSpeed);
		 rainbowColor(Settings::ESP::espAmmoColor, Settings::Misc::rainbowSpeed);
		 rainbowColor(Settings::ESP::espDistanceColor, Settings::Misc::rainbowSpeed);

		entity->GetCollideable()->WorldSpaceTriggerBounds(&targetMinS, &targetMaxS);
		Vector entCollMid = Vector(entity->GetCollideable()->OBBMins().x + entity->GetCollideable()->OBBMaxs().x, entity->GetCollideable()->OBBMins().y + entity->GetCollideable()->OBBMaxs().y, entity->GetCollideable()->OBBMins().z);

		if (WorldToScreen(entityAbsOrig + entCollMid, screenPos) &&
			WorldToScreen(entityAbsOrig + entCollMid + Vector(0,0,entity->GetCollideable()->OBBMaxs().z), screenTopPos))
		{
			if (isEntity)
			{

				DrawTextW(Vector(screenTopPos.x, screenTopPos.y, 0), StringToWString(std::string(entName)), ColorToRGBA(Settings::ESP::espNameColor), true);

				if (Settings::ESP::espShapeInt == 0)
					DrawEsp2D(screenPos, screenTopPos, ColorToRGBA(Settings::ESP::espBoundingBoxColor));
				else if (Settings::ESP::espShapeInt == 1)
					DrawEspBox3D(entity->GetCollideable()->OBBMaxs(), entity->GetCollideable()->OBBMins(), entity->GetAbsOrigin(), entity->GetAbsAngles(), ColorToRGBA(Settings::ESP::espBoundingBoxColor));
				continue;
			}

			auto foundFriend = Settings::friendList.find(entity);
			if (Settings::ESP::onlyFriends && (foundFriend == Settings::friendList.end() || !foundFriend->second.first))
					continue;


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
					DrawLine(bonePosFrom, parentBonePos, ColorToRGBA(Settings::ESP::skeletonEspColor));
					//DrawTextW(bonePosFrom, std::to_wstring(z), 0xFFFFFFFF, true); // write bone ids
				}
			}
			
			int selectedHitBox = 0; // that crashes x86
			Studio_BoneIndexByName(studioHdr, IntToBoneName(Settings::Aimbot::aimbotHitbox), &selectedHitBox);

			Vector screenEyePos;
			screenEyePos.z = 0;
			if (Settings::Aimbot::drawAimbotHeadlines && WorldToScreen(Vector(bones[selectedHitBox][0][3], bones[selectedHitBox][1][3], bones[selectedHitBox][2][3]), screenEyePos) && Vector(Globals::screenWidth / 2, Globals::screenHeight / 2, 0).DistTo(screenEyePos) < Settings::Aimbot::aimbotFOV)
			{
				// white if random person, blue'ish if target

				int color = entity == Settings::Aimbot::finalTarget ? 0xFF3333FF : 0xFFFFFFFF;
				DrawLine(Vector(Globals::screenWidth / 2, Globals::screenHeight / 2, 0), screenEyePos, color);
			}

			player_info_s info;
			EngineClient->GetPlayerInfo(i, &info);

			Vector targetScrMaxs;
			Vector targetScrMins;
			if (WorldToScreen(entity->GetAbsOrigin(), targetScrMins) && WorldToScreen(entity->EyePosition(), targetScrMaxs))
			{

				std::wstring playerInfo = L"";
				if (Settings::ESP::espName)
					playerInfo = StringToWString(info.name) + L"\n";


				Vector textPos;
				switch (Settings::ESP::infosEmplacement)
				{
				case 0: // Above
					textPos = Vector(targetScrMaxs.x, targetScrMaxs.y, 0);
					break;
				case 1: // Below
					textPos = Vector(targetScrMaxs.x, targetScrMins.y, 0);
					break;
				case 2: // Right
					textPos = Vector(targetScrMaxs.x - (targetScrMaxs.y - targetScrMins.y) / 4, targetScrMaxs.y, 0);
					break;
				case 3: // Left
					textPos= Vector(targetScrMaxs.x - (targetScrMaxs.y - targetScrMins.y) / 4, targetScrMaxs.y, 0);
					break;
				}
				DrawTextW(textPos, playerInfo, ColorToRGBA(Settings::ESP::espNameColor), true);

				if (Settings::ESP::weaponText)
				{
					const char* weaponName = "";
					if (entity->GetActiveWeapon())
					{
						playerInfo = L"Weapon: " + StringToWString(entity->GetActiveWeapon()->GetName());
						textPos.y += DrawingFontSize;
						DrawTextW(textPos, playerInfo, ColorToRGBA(Settings::ESP::espWeaponColor), true);
					}
				}
				if (Settings::ESP::espHealthBar)
				{
					playerInfo = L"Health: " + std::to_wstring(entity->GetHealth()) + L"/" + std::to_wstring(entity->GetMaxHealth()) ;
					textPos.y += DrawingFontSize;
					DrawTextW(textPos, playerInfo, ColorToRGBA(Settings::ESP::espHealthColor), true);
				}

				if (Settings::ESP::weaponAmmo)
				{
					playerInfo = L"Ammos: " + std::to_wstring(entity->GetActiveWeapon()->PrimaryAmmoCount()) ;
					textPos.y += DrawingFontSize;
					DrawTextW(textPos, playerInfo, ColorToRGBA(Settings::ESP::espAmmoColor), true);
				}

				if (Settings::ESP::espDistance)
				{
					playerInfo = L"Distance: " + std::to_wstring((int)entity->GetAbsOrigin().DistTo(localPlayer->GetAbsOrigin())) ;
					textPos.y += DrawingFontSize;
					DrawTextW(textPos, playerInfo, ColorToRGBA(Settings::ESP::espDistanceColor), true);
				}


				if (Settings::ESP::espBoundingBox)
				{
					if (Settings::ESP::espShapeInt == 0)
					{
							DrawEsp2D(targetScrMins, targetScrMaxs, ColorToRGBA(Settings::ESP::espBoundingBoxColor));
					}
					else if (Settings::ESP::espShapeInt == 1)
						DrawEspBox3D(entity->GetCollideable()->OBBMaxs(), entity->GetCollideable()->OBBMins(), entity->GetAbsOrigin(), entity->EyeAngles(), ColorToRGBA(Settings::ESP::espBoundingBoxColor));
				}
			}
		}
		
	}


}