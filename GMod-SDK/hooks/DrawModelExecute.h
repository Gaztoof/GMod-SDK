#pragma once

#include "../globals.hpp"
#include "../client/usercmd.h"
#include "../client/ClientModeShared.h"
#include "../tier0/Vector.h"
#include "../engine/vmatrix.h"

typedef void(__thiscall* _DrawModelExecute)(CModelRender*, const DrawModelState_t&, const ModelRenderInfo_t*, matrix3x4_t*);
_DrawModelExecute oDrawModelExecute;



void __fastcall hkDrawModelExecute(CModelRender* modelrender, 
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif 
const DrawModelState_t& state, ModelRenderInfo_t* pInfo, matrix3x4_t* pCustomBoneToWorld = NULL)
{
	if (pInfo->entity_index)
	{
		C_BasePlayer* entity = (C_BasePlayer*)ClientEntityList->GetClientEntity(pInfo->entity_index);
		if(!entity || !entity->IsAlive() || (!entity->IsPlayer() && !entity->IsRagdoll() && !entity->IsBaseCombatCharacter() && !entity->IsWeapon() && !entity->IsARagdoll() && (!strstr(pInfo->pModel->name, "models/weapons/") || !Settings::Misc::removeHands)))
			return oDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		chamsSetting setting;

		if (entity == localPlayer)
		{
			rainbowColor(Settings::Chams::localPlayerChamsSettings.hiddenColor, Settings::Misc::rainbowSpeed);
			rainbowColor(Settings::Chams::localPlayerChamsSettings.visibleColor, Settings::Misc::rainbowSpeed);

			setting = Settings::Chams::localPlayerChamsSettings;
		}
		else if (entity->IsPlayer())
		{
			rainbowColor(Settings::Chams::playerChamsSettings.hiddenColor, Settings::Misc::rainbowSpeed);
			rainbowColor(Settings::Chams::playerChamsSettings.visibleColor, Settings::Misc::rainbowSpeed);
			 rainbowColor(Settings::Chams::teamMateSettings.hiddenColor, Settings::Misc::rainbowSpeed);
			rainbowColor(Settings::Chams::teamMateSettings.visibleColor, Settings::Misc::rainbowSpeed);

			if(entity->getTeamNum() == localPlayer->getTeamNum())
			setting = Settings::Chams::teamMateSettings;
			else setting = Settings::Chams::playerChamsSettings;
		}
		else if (entity->IsBaseCombatCharacter() && !entity->IsPlayer()) // IF ITS A NPC
		{
			rainbowColor(Settings::Chams::npcChamsSettings.hiddenColor, Settings::Misc::rainbowSpeed);
			rainbowColor(Settings::Chams::npcChamsSettings.visibleColor, Settings::Misc::rainbowSpeed);
			setting = Settings::Chams::npcChamsSettings;
		}
		else if (entity->IsRagdoll() || entity->IsARagdoll()) // Isragdoll = ragdoll entity, isaragdoll = ragdolled player cuz dead
		{
			rainbowColor(Settings::Chams::ragdollChamsSettings.hiddenColor, Settings::Misc::rainbowSpeed);
			rainbowColor(Settings::Chams::ragdollChamsSettings.visibleColor, Settings::Misc::rainbowSpeed);
			setting = Settings::Chams::ragdollChamsSettings;
		}
		else if (entity->IsWeapon())
		{
			rainbowColor(Settings::Chams::weaponChamsSettings.hiddenColor, Settings::Misc::rainbowSpeed);
			rainbowColor(Settings::Chams::weaponChamsSettings.visibleColor, Settings::Misc::rainbowSpeed);
			setting = Settings::Chams::weaponChamsSettings;
		}
		else if (!entity->IsWeapon() && strstr(pInfo->pModel->name, "models/weapons/") && Settings::Misc::removeHands)
		{
			return;
		}
		else {
			return oDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		}

		IMaterial* DebugWhite = MaterialSystem->FindMaterial("models/debug/debugwhite", TEXTURE_GROUP_MODEL);
		DebugWhite->AddRef(); // that's so the game loads it, if 0 stuff on the map uses this texture, the game will simply unload it

		bool didDraw = false;
		if (entity == localPlayer && Settings::Chams::netLocalChamsSettings.visibleMaterial && Globals::lastNetworkedCmd.command_number) // ghetto asf...
		{
			if (Settings::Chams::netLocalChamsSettings.visibleMaterial == 1)
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
			else if (Settings::Chams::netLocalChamsSettings.visibleMaterial == 2)
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);

			RenderView->SetBlend(Settings::Chams::netLocalChamsSettings.visibleColor.fCol[3]);
			RenderView->SetColorModulation(Settings::Chams::netLocalChamsSettings.hiddenColor.fCol);
			modelrender->ForcedMaterialOverride(DebugWhite); //entity->SetMaterialOverridePointer(DebugWhite); <- this works too


			oDrawModelExecute(modelrender, state, pInfo, Globals::lastMatrix);
		}

		if (setting.hiddenMaterial)
		{
			didDraw = true;
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true); // xqz = true, normal = false

			if(setting.hiddenMaterial == 1)
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
			else if(setting.hiddenMaterial == 2)
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);

			RenderView->SetBlend(setting.visibleColor.fCol[3]);
			RenderView->SetColorModulation(setting.hiddenColor.fCol);
			modelrender->ForcedMaterialOverride(DebugWhite); //entity->SetMaterialOverridePointer(DebugWhite); <- this works too
			oDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		}
		if (setting.visibleMaterial)
		{
			didDraw = true;
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false); // xqz = true, normal = false

			if (setting.visibleMaterial == 1)
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
			else if (setting.visibleMaterial == 2)
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);

			RenderView->SetBlend(setting.visibleColor.fCol[3]);
			RenderView->SetColorModulation(setting.visibleColor.fCol);
			modelrender->ForcedMaterialOverride(DebugWhite); //entity->SetMaterialOverridePointer(DebugWhite); <- this works too but i prefer forcedmaterialoverride /shrug
			oDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		}
		
		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);

		RenderView->SetBlend(1.f);
		RenderView->SetColorModulation(Color(255, 255, 255).fCol);
		modelrender->ForcedMaterialOverride(nullptr);
		if (!didDraw)
			oDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		return;
	}
	return oDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
}