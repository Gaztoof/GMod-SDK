#pragma once

#include "../globals.hpp"
#include "../client/usercmd.h"
#include "../hacks/Misc.h"
#include "../hacks/Utils.h"

typedef bool(__thiscall* _RenderView)(CViewRender*, CViewSetup&, int, int);
_RenderView oRenderView;

bool __fastcall hkRenderView(CViewRender* ViewRender, 
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif
CViewSetup& view, int nClearFlags, int whatToDraw)
{
	bool zoomKeyDown = false;
	getKeyState(Settings::Misc::zoomKey, Settings::Misc::zoomKeyStyle, &zoomKeyDown, henlo69, henlo70, henlo71);

	// make this run only if not holding right click for instance to restore fov to what it should be while aiming
	if (zoomKeyDown && Settings::Misc::zoom)
		view.fov = Settings::Misc::zoomFOV;
	else view.fov = Settings::Visuals::fov;

	//view.angles = Settings::lastCmd.viewangles;
	view.fovViewmodel = Settings::Visuals::viewModelFOV;
	
	static Vector camPos = Vector(0,0,0);

	bool thirdpKeyDown = false;
	getKeyState(Settings::Misc::thirdpersonKey, Settings::Misc::thirdpersonKeyStyle, &thirdpKeyDown, henlo1, henlo2, henlo3);
	static bool lastThirdPersonState = false;
	if (localPlayer && Settings::Misc::thirdperson && thirdpKeyDown) {
		lastThirdPersonState = true;
		ThirdPerson(view);
		view.angles = Settings::lastCmd.viewangles;

		Input->m_fCameraInThirdPerson = true;		
	}
	else {
		if (lastThirdPersonState)
			Input->m_fCameraInThirdPerson = false;
		lastThirdPersonState = false;
		
	}

	bool freeCamKeyDown = false;
	getKeyState(Settings::Misc::freeCamKey, Settings::Misc::freeCamKeyStyle, &freeCamKeyDown, henlo4, henlo5, henlo6);

	static bool lastFreeCamState = false;
	if (localPlayer && Settings::Misc::freeCam && freeCamKeyDown)
	{
		view.angles = Settings::lastCmd.viewangles;
		lastFreeCamState = true;
		Settings::currentlyInFreeCam = true;
		FreeCam(view, camPos);
		Input->m_fCameraInThirdPerson = true;
	}
	else {
		if (lastFreeCamState)
		{
			EngineClient->SetViewAngles(Settings::lastRealCmd.viewangles);
			Input->m_fCameraInThirdPerson = false;
		}
		lastFreeCamState = false;
		camPos = Vector(0, 0, 0);
		Settings::currentlyInFreeCam = false;
	}

	if ((!freeCamKeyDown || !Settings::Misc::freeCam) && (!thirdpKeyDown || !Settings::Misc::thirdperson))
	{
		//view.angles = Settings::lastCmd.viewangles;
	}
	
	return oRenderView(ViewRender, view, nClearFlags, whatToDraw);
}