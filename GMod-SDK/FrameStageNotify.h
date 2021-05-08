#pragma once

#include "globals.h"
#include "usercmd.h"
#include "ClientModeShared.h"
#include <Windows.h>

typedef void(__thiscall* _FrameStageNotify)(CHLClient*, ClientFrameStage_t);
_FrameStageNotify oFrameStageNotify;

void __fastcall hkFrameStageNotify(CHLClient* client, void*, ClientFrameStage_t stage)
{
	if (stage == ClientFrameStage_t::FRAME_RENDER_START)
	{
		// do thirdperson
	}
	if (stage == ClientFrameStage_t::FRAME_RENDER_END)
	{
		for (MaterialHandle_t i = MaterialSystem->FirstMaterial(); i != MaterialSystem->InvalidMaterial(); i = MaterialSystem->NextMaterial(i))
		{
			auto material = MaterialSystem->GetMaterial(i);
			if (!material || material->IsErrorMaterial())
				continue;
#pragma region WorldColor
			if (!strcmp(material->GetTextureGroupName(), TEXTURE_GROUP_WORLD))
			{
				material->AlphaModulate(worldColor.fCol[3]);
				material->ColorModulate(worldColor.fCol[0], worldColor.fCol[1], worldColor.fCol[2]);
			}
#pragma endregion

		}

		ConVar* var = CVar->FindVar("r_3dsky"); // simply doesn't works.
		if (var)
			var->SetValue(!disableSkyBox);
	}
	return oFrameStageNotify(client, stage);
}