#pragma once

#include "globals.h"
#include "usercmd.h"
#include "ClientModeShared.h"
#include <Windows.h>

typedef void(__thiscall* _FrameStageNotify)(CHLClient*, ClientFrameStage_t);
_FrameStageNotify oFrameStageNotify;

void __fastcall hkFrameStageNotify(CHLClient* client, 
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif
ClientFrameStage_t stage)
{

	localPlayer = (C_BasePlayer*)ClientEntityList->GetClientEntity(EngineClient->GetLocalPlayer());
	Input->m_fCameraInThirdPerson = Settings::Misc::thirdperson;
	//Input->cameraoffset
	//if (silentAim)EngineClient->SetViewAngles(lastRealAngles);

	if (localPlayer && localPlayer->IsAlive())
	{
		//https://i.imgur.com/Y5hSyqS.png
		if (Settings::Visuals::noVisualRecoil)
			localPlayer->GetViewPunch() = QAngle(0, 0, 0);
		//if(Settings::Misc::noRecoil)
			//localPlayer->GetAimPunch() = QAngle(0, 0, 0);
	}

	// i guess this enum's wrong as norecoil in renderstart didnt work at all
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
				if (Settings::Visuals::changeWorldColor)
				{
					material->AlphaModulate(Settings::Visuals::worldColor.fCol[3]);
					material->ColorModulate(Settings::Visuals::worldColor.fCol[0], Settings::Visuals::worldColor.fCol[1], Settings::Visuals::worldColor.fCol[2]);
				}
				else
				{
					material->AlphaModulate(1.f);
					material->ColorModulate(1.f, 1.f, 1.f);
				}
			}
#pragma endregion
#pragma region PropColor
			if (Settings::Visuals::changeWorldColor && (!strcmp(material->GetTextureGroupName(), TEXTURE_GROUP_MODEL) || strstr(material->GetName(), "models/prop") != 0))
			{
				if (Settings::Visuals::changeWorldColor)
				{
					/*static bool doneOnce = false;
					if (!doneOnce)
					EngineClient->ClientCmd("r_DrawSpecificStaticProp 0");
					doneOnce = true;*/
					material->AlphaModulate(Settings::Visuals::worldColor.fCol[3]);
					material->ColorModulate(Settings::Visuals::worldColor.fCol[0], Settings::Visuals::worldColor.fCol[1], Settings::Visuals::worldColor.fCol[2]);
				}
				else
				{
					material->AlphaModulate(1.f);
					material->ColorModulate(1.f, 1.f, 1.f);
				}
			}
#pragma endregion

		}
		static bool lastSkyBox = false;
		if (Settings::Visuals::disableSkyBox != lastSkyBox)
		{
			lastSkyBox = Settings::Visuals::disableSkyBox;
			if (lastSkyBox)
			{
				EngineClient->ClientCmd("r_3dsky 0");
			}
			else {
				EngineClient->ClientCmd("r_3dsky 1");
			}
		}
	}

	if(oFrameStageNotify)
	return oFrameStageNotify(client, stage);
}