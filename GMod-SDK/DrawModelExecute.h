#pragma once

#include "globals.h"
#include "usercmd.h"
#include "ClientModeShared.h"
#include "Vector.h"
#include "vmatrix.h"

typedef void(__thiscall* _DrawModelExecute)(CModelRender*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4_t*);
_DrawModelExecute oDrawModelExecute;



void __fastcall hkDrawModelExecute(CModelRender* modelrender, 
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif 
const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld = NULL)
{
	if (pInfo.entity_index)
	{
		//std::cout << pInfo.pModel->name << std::endl;
		C_BasePlayer* entity = (C_BasePlayer*)ClientEntityList->GetClientEntity(pInfo.entity_index);
		if(!entity || !entity->IsAlive() || (!entity->IsPlayer() && !entity->IsRagdoll() && !entity->IsBaseCombatCharacter() && !entity->IsWeapon() && !entity->IsARagdoll() && (!strstr(pInfo.pModel->name, "models/weapons/") || !Settings::Misc::removeHands)))
			return oDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		chamsSetting setting;

		if (entity == localPlayer)
		{
			setting = Settings::Chams::localPlayerChamsSettings;
		}
		else if (entity->IsPlayer())
		{
			if(entity->getTeamNum() == localPlayer->getTeamNum())
			setting = Settings::Chams::teamMateSettings;
			else setting = Settings::Chams::playerChamsSettings;
		}
		else if (entity->IsBaseCombatCharacter() && !entity->IsPlayer()) // IF ITS A NPC
		{
			setting = Settings::Chams::npcChamsSettings;
		}
		else if (entity->IsRagdoll() || entity->IsARagdoll()) // Isragdoll = ragdoll entity, isaragdoll = ragdolled player cuz dead
		{
			setting = Settings::Chams::ragdollChamsSettings;
		}
		else if (entity->IsWeapon())
		{
			setting = Settings::Chams::weaponChamsSettings;
		}
		else if (!entity->IsWeapon() && strstr(pInfo.pModel->name, "models/weapons/") && Settings::Misc::removeHands)
		{
			return;
		}
		else {
			return oDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		}

		IMaterial* DebugWhite = MaterialSystem->FindMaterial("models/debug/debugwhite", TEXTURE_GROUP_MODEL);
		DebugWhite->AddRef(); // that's so the game loads it, if 0 stuff on the map uses this texture, the game will simply unload it

		bool didDraw = false;
		if (setting.hiddenMaterial)
		{
			didDraw = true;
			DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true); // xqz = true, normal = false

			if(setting.hiddenMaterial == 1)
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);
			else if(setting.hiddenMaterial == 2)
				DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);

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

			RenderView->SetColorModulation(setting.visibleColor.fCol);
			modelrender->ForcedMaterialOverride(DebugWhite); //entity->SetMaterialOverridePointer(DebugWhite); <- this works too but i prefer forcedmaterialoverride /shrug
			oDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		}
		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, false);

		RenderView->SetColorModulation(Color(255, 255, 255).fCol);
		modelrender->ForcedMaterialOverride(nullptr);
		if (!didDraw)
			oDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
		return;
	}
	return oDrawModelExecute(modelrender, state, pInfo, pCustomBoneToWorld);
}