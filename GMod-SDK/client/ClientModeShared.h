#pragma once
#include "C_BasePlayer.h"
#include "usercmd.h"

// Auto reconstructed from vtable block @ 0x0087DE78
// from "client.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class ClientModeShared
{
public:
	/*0*/	virtual void* destr() = 0;
	/*1/	virtual void* InitViewport(void) = 0;
	/*2*/	virtual void* Init(void) = 0;
	/*3*/	virtual void* VGui_Shutdown(void) = 0;
	/*4*/	virtual void* Shutdown(void) = 0;
	/*5*/	virtual void* Enable(void) = 0;
	/*6*/	virtual void* Disable(void) = 0;
	/*7*/	virtual void* Layout(void) = 0;
	/*8*/	virtual void* GetViewport(void) = 0;
	/*9*/	virtual void* GetViewportAnimationController(void) = 0;
	/*10*/	virtual void* ProcessInput(bool) = 0;
	/*11*/	virtual bool ShouldDrawDetailObjects(void) = 0;
	/*12*/	virtual bool ShouldDrawEntity(C_BaseEntity*) = 0;
	/*13*/	virtual bool ShouldDrawLocalPlayer(C_BasePlayer*) = 0;
	/*14*/	virtual bool ShouldDrawParticles(void) = 0;
	/*15*/	virtual bool ShouldDrawFog(void) = 0;
	/*16*/	virtual void* OverrideView(void*) = 0;
	/*17*/	virtual void* KeyInput(int,ButtonCode_t,char const*) = 0;
	/*18*/	virtual void* StartMessageMode(int) = 0;
	/*19*/	virtual void* GetMessagePanel(void) = 0;
	/*20*/	virtual void* OverrideMouseInput(float*,float*) = 0;
	/*21*/	virtual void* CreateMove(float,CUserCmd*) = 0;
	/*22*/	virtual void* LevelInit(char const*) = 0;
	/*23*/	virtual void* LevelShutdown(void) = 0;
	/*24*/	virtual bool ShouldDrawViewModel(void) = 0;
	/*25*/	virtual bool ShouldDrawCrosshair(void) = 0;
	/*26*/	virtual void* AdjustEngineViewport(int&,int&,int&,int&) = 0;
	/*27*/	virtual void* PreRender(void*) = 0;
	/*28*/	virtual void* PostRender(void) = 0;
	/*29*/	virtual void* PostRenderVGui(void) = 0;
	/*30*/	virtual void* ActivateInGameVGuiContext(void*) = 0;
	/*31*/	virtual void* DeactivateInGameVGuiContext(void) = 0;
	/*32*/	virtual void* GetViewModelFOV(void) = 0;
	/*33*/	virtual void* CanRecordDemo(char*,int)const = 0;
	/*34*/	virtual void* ComputeVguiResConditions(void*) = 0;
	/*35*/	virtual const char* GetServerName(void) = 0;
	/*36*/	virtual const char* SetServerName(wchar_t*) = 0;
	/*37*/	virtual void* GetMapName(void) = 0;
	/*38*/	virtual void* SetMapName(wchar_t*) = 0;
	/*39*/	virtual void* DoPostScreenSpaceEffects(void const*) = 0;
	/*40*/	virtual void* DisplayReplayMessage(char const*,float,bool,char const*,bool) = 0;
	/*41*/	virtual void* Update(void) = 0;
	/*42*/	virtual bool ShouldBlackoutAroundHUD(void) = 0;
	/*43*/	virtual bool ShouldOverrideHeadtrackControl(void) = 0;
	/*44*/	virtual bool IsInfoPanelAllowed(void) = 0;
	/*45*/	virtual void* InfoPanelDisplayed(void) = 0;
	/*46*/	virtual void* ReloadScheme(void) = 0;
	/*47*/	virtual void* HudElementKeyInput(int,ButtonCode_t,char const*) = 0;
	/*48*/	virtual void* HandleSpectatorKeyInput(int,ButtonCode_t,char const*) = 0;
	/*49*/	virtual void* GetHUDChatPanel(void) = 0;
	/*50*/	virtual void* UpdateReplayMessages(void) = 0;
};