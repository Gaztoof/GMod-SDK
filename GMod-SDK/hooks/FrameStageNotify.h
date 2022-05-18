#pragma once

#include "../globals.hpp"
#include "../client/usercmd.h"
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

	static ConVar* fullbrightCvar = CVar->FindVar("mat_fullbright");
	if (fullbrightCvar && fullbrightCvar->intValue != Settings::Visuals::fullBright) fullbrightCvar->SetValue(Settings::Visuals::fullBright);
	if (Settings::Misc::svAllowCsLua && !spoofedAllowCsLua) {
		spoofedAllowCsLua = new SpoofedConVar(CVar->FindVar("sv_allowcslua"));
		spoofedAllowCsLua->m_pOriginalCVar->DisableCallback();
	}if (Settings::Misc::svCheats && !spoofedCheats) {
		spoofedCheats = new SpoofedConVar(CVar->FindVar("sv_cheats"));
		spoofedCheats->m_pOriginalCVar->DisableCallback();
	}

	if (spoofedAllowCsLua && spoofedAllowCsLua->m_pOriginalCVar->intValue != Settings::Misc::svAllowCsLua) spoofedAllowCsLua->m_pOriginalCVar->SetValue(Settings::Misc::svAllowCsLua);
	if (spoofedCheats && spoofedCheats->m_pOriginalCVar->intValue != Settings::Misc::svCheats) spoofedCheats->m_pOriginalCVar->SetValue(Settings::Misc::svCheats);

	//Input->cameraoffset

	if(localPlayer && localPlayer->IsAlive())
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
	static bool appliedNightMode = false;
	static bool waitingForLoadingEnd = false;
	static bool lastNightModeState = false;
	static Color lastNightModeColor = Color(255, 255, 255);
	if (lastNightModeState != Settings::Visuals::changeWorldColor || lastNightModeColor != Settings::Visuals::worldColor)
	{
		lastNightModeColor = Settings::Visuals::worldColor;
		lastNightModeState = Settings::Visuals::changeWorldColor;
		appliedNightMode = false;
	}

	if (EngineClient->IsDrawingLoadingImage())
	{
		waitingForLoadingEnd = true;
	}
	else if (waitingForLoadingEnd) {
		appliedNightMode = false;
		waitingForLoadingEnd = false;
	}

	if (!waitingForLoadingEnd && stage == ClientFrameStage_t::FRAME_RENDER_END)
	{
		for (MaterialHandle_t i = MaterialSystem->FirstMaterial(); i != MaterialSystem->InvalidMaterial(); i = MaterialSystem->NextMaterial(i))
		{
			auto material = MaterialSystem->GetMaterial(i);
			if (!material || material->IsErrorMaterial() || !material->IsPrecached())
				continue;
			// that's quite a big FPS killer
#pragma region WorldColor
			if (!strcmp(material->GetTextureGroupName(), TEXTURE_GROUP_WORLD))
			{
				if (Settings::Visuals::changeWorldColor && !appliedNightMode)
				{
					material->AlphaModulate(Settings::Visuals::worldColor.fCol[3]);
					material->ColorModulate(Settings::Visuals::worldColor.fCol[0], Settings::Visuals::worldColor.fCol[1], Settings::Visuals::worldColor.fCol[2]);
				}
				else if(!Settings::Visuals::changeWorldColor && !appliedNightMode)
				{
					material->AlphaModulate(1.f);
					material->ColorModulate(1.f, 1.f, 1.f);
				}
			}
#pragma endregion

		}
		appliedNightMode = true;
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
	getKeyState(Settings::Misc::thirdpersonKey, Settings::Misc::thirdpersonKeyStyle, &thirdpKeyDown);
	bool freecamKeyDown = false;
	getKeyState(Settings::Misc::freeCamKey, Settings::Misc::freeCamKeyStyle, &freecamKeyDown);

	// check toggle instead of key if we have the toggle option on
	bool thirdPersonEnabled = (Settings::Misc::thirdperson && (Settings::Misc::toggleThirdperson || thirdpKeyDown));
	bool needsSetViewAngles = thirdPersonEnabled || (Settings::Misc::freeCam && freecamKeyDown);

	if(localPlayer && localPlayer->IsAlive() && stage == ClientFrameStage_t::FRAME_RENDER_START && needsSetViewAngles)
		localPlayer->SetLocalViewAngles(Globals::lastNetworkedCmd.viewangles);
	if(oFrameStageNotify)
	oFrameStageNotify(client, stage);
	if (localPlayer && localPlayer->IsAlive() && stage == ClientFrameStage_t::FRAME_RENDER_START && needsSetViewAngles)
		localPlayer->SetLocalViewAngles(Globals::lastRealCmd.viewangles);
	return;
}