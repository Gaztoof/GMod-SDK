#pragma once

#include "globals.h"
#include "usercmd.h"
#include "ClientModeShared.h"
#include "CViewRender.h"

typedef bool(__thiscall* _RenderView)(CViewRender*, CViewSetup&, int, int);
_RenderView oRenderView;

bool __fastcall hkRenderView(CViewRender* ViewRender, void*, CViewSetup& view, int nClearFlags, int whatToDraw)
{
	view.fov = fov;
	view.fovViewmodel = viewModelFOV;
	
	return oRenderView(ViewRender, view, nClearFlags, whatToDraw);
}