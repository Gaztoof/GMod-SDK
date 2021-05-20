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

	//Input->cameraoffset
	//if (silentAim)EngineClient->SetViewAngles(lastRealAngles);

	if (localPlayer && localPlayer->IsAlive())
	{
		//https://i.imgur.com/Y5hSyqS.png
		if (Settings::Visuals::noVisualRecoil)
			localPlayer->GetViewPunch() = QAngle(0, 0, 0);
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
			// that's quite a big FPS killer
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
	bool thirdpKeyDown = false;
	getKeyState(Settings::Misc::thirdpersonKey, Settings::Misc::thirdpersonKeyStyle, &thirdpKeyDown, henlo1, henlo2, henlo3);

	if(stage == ClientFrameStage_t::FRAME_RENDER_START && localPlayer && Settings::Misc::thirdperson && thirdpKeyDown)
		localPlayer->SetLocalViewAngles(Settings::lastNetworkedCmd.viewangles);
	oFrameStageNotify(client, stage);
	if (stage == ClientFrameStage_t::FRAME_RENDER_START && localPlayer && Settings::Misc::thirdperson && thirdpKeyDown)
		localPlayer->SetLocalViewAngles(Settings::lastRealCmd.viewangles);
}