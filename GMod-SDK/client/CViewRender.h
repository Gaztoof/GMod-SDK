#pragma once
#include "CViewSetup.h"
#include "../engine/imaterial.h"
// Auto reconstructed from vtable block @ 0x008EEC18
// from "client.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class CViewRender
{
public:
	/*0*/	virtual void* Init(void) = 0;
	/*1*/	virtual void* LevelInit(void) = 0;
	/*2*/	virtual void* LevelShutdown(void) = 0;
	/*3*/	virtual void* Shutdown(void) = 0;
	/*4*/	virtual void* OnRenderStart(void) = 0;
	/*5*/	virtual void* Render(vrect_t*) = 0;
	/*6*/	virtual void* RenderView(CViewSetup const&, int, int) = 0;
	/*7*/	virtual void* GetDrawFlags(void) = 0;
	/*8*/	virtual void* StartPitchDrift(void) = 0;
	/*9*/	virtual void* StopPitchDrift(void) = 0;
	/*10*/	virtual void* GetFrustum(void) = 0;
	/*11*/	virtual void* ShouldDrawBrushModels(void) = 0;
	/*12*/	virtual void* GetPlayerViewSetup(void)const = 0;
	/*13*/	virtual void* GetViewSetup(void)const = 0;
	/*14*/	virtual void* DisableVis(void) = 0;
	/*15*/	virtual void* BuildWorldListsNumber(void)const = 0;
	/*16*/	virtual void* SetCheapWaterStartDistance(float) = 0;
	/*17*/	virtual void* SetCheapWaterEndDistance(float) = 0;
	/*18*/	virtual void* GetWaterLODParams(float&, float&) = 0;
	/*19*/	virtual void* DriftPitch(void) = 0;
	/*20*/	virtual void* SetScreenOverlayMaterial(IMaterial*) = 0;
	/*21*/	virtual void* GetScreenOverlayMaterial(void) = 0;
	/*22*/	virtual void* WriteSaveGameScreenshot(char const*) = 0;
	/*23*/	virtual void* WriteSaveGameScreenshotOfSize(char const*, int, int, bool, bool) = 0;
	/*24*/	virtual void* WriteReplayScreenshot(void*) = 0;
	/*25*/	virtual void* UpdateReplayScreenshotCache(void) = 0;
	/*26*/	virtual void* QueueOverlayRenderView(CViewSetup const&, int, int) = 0;
	/*27*/	virtual void* GetZNear(void) = 0;
	/*28*/	virtual void* GetZFar(void) = 0;
	/*29*/	virtual void* GetScreenFadeDistances(float*, float*) = 0;
	/*30*/	virtual void* GetCurrentlyDrawingEntity(void) = 0;
	/*31*/	virtual void* SetCurrentlyDrawingEntity(void*) = 0;
	/*32*/	virtual void* UpdateShadowDepthTexture(ITexture*, ITexture*, CViewSetup const&) = 0;
	/*33*/	virtual void* FreezeFrame(float) = 0;
	/*34*/	virtual void* GetReplayScreenshotSystem(void) = 0;
};