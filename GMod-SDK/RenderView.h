#pragma once

#include "globals.h"
#include "usercmd.h"
#include "ClientModeShared.h"
#include "CViewRender.h"
#include "Misc.h"

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
	if (zoomKeyDown && Settings::Misc::zoom)
		view.fov = Settings::Misc::zoomFOV;
	else view.fov = Settings::Visuals::fov;

	view.angles = Settings::lastCmd.viewangles;
	view.fovViewmodel = Settings::Visuals::viewModelFOV;

	static Vector camPos = Vector(0,0,0);

	bool thirdpKeyDown = false;
	getKeyState(Settings::Misc::thirdpersonKey, Settings::Misc::thirdpersonKeyStyle, &thirdpKeyDown, henlo1, henlo2, henlo3);
	if (localPlayer && Settings::Misc::thirdperson && thirdpKeyDown) {
		ThirdPerson(view);
		Input->m_fCameraInThirdPerson = true;		
	} else Input->m_fCameraInThirdPerson = false;

	bool freeCamKeyDown = false;
	getKeyState(Settings::Misc::freeCamKey, Settings::Misc::freeCamKeyStyle, &freeCamKeyDown, henlo4, henlo5, henlo6);

	if (localPlayer && Settings::Misc::freeCam && freeCamKeyDown)
	{
		Settings::currentlyInFreeCam = true;
		FreeCam(view, camPos);
	}
	else {
		camPos = Vector(0, 0, 0);
		Settings::currentlyInFreeCam = false;
	}
	if ((!freeCamKeyDown || !Settings::Misc::freeCam) && (!thirdpKeyDown || !Settings::Misc::thirdperson))
	{
		view.angles = Settings::lastCmd.viewangles;
	}
	
	return oRenderView(ViewRender, view, nClearFlags, whatToDraw);
}