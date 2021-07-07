#pragma once

#include "../tier0/shareddefs.h"
#include "../tier0/Vector.h"
class CViewSetup;
enum class ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};
class CGlobalVarsBase
{
public:
	float			realtime;
	int				framecount;
	float			absoluteframetime;
	float			curtime;
	float			frametime;
	int				maxClients;
	int				tickcount;
	float			interval_per_tick;
	float			interpolation_amount;
	int				simTicksThisFrame;
	int				network_protocol;
	void* pSaveData;
private:
	bool			m_bClient;
	int				nTimestampNetworkingBase;
	int				nTimestampRandomizeWindow;

};
// Auto reconstructed from vtable block @ 0x0087DA90
// from "client.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class CHLClient
{
public:
	// https://github.com/NicknineTheEagle/TF2-Base/blob/master/src/public/cdll_int.h
	/*0*/	virtual void* Init(void* (*)(char const*, int*), void* (*)(char const*, int*), CGlobalVarsBase*, void*) = 0;
	/*1*/	virtual void* PostInit(void) = 0;
	/*2*/	virtual void* Shutdown(void) = 0;
	/*3*/	virtual void* ReplayInit(void* (*)(char const*, int*)) = 0;
	/*4*/	virtual void* ReplayPostInit(void) = 0;
	/*5*/	virtual void* LevelInitPreEntity(char const*) = 0;
	/*6*/	virtual void* LevelInitPostEntity(void) = 0;
	/*7*/	virtual void* LevelShutdown(void) = 0;
	/*8*/	virtual void* GetAllClasses(void) = 0;
	/*9*/	virtual void* HudVidInit(void) = 0;
	/*10*/	virtual void* HudProcessInput(bool) = 0;
	/*11*/	virtual void* HudUpdate(bool) = 0;
	/*12*/	virtual void* HudReset(void) = 0;
	/*13*/	virtual void* HudText(char const*) = 0;
	/*14*/	virtual void IN_ActivateMouse(void) = 0;
	/*15*/	virtual void IN_DeactivateMouse(void) = 0;
	/*16*/	virtual void IN_Accumulate(void) = 0;
	/*17*/	virtual void IN_ClearStates(void) = 0;
	/*18*/	virtual bool IN_IsKeyDown(char const* keyName, bool& isdown) = 0;

	/*19*/	virtual void* IN_OnMouseWheeled(int) = 0;
	/*20*/	virtual void CreateMove(int sequence_number, float input_sample_frametime, bool active) = 0;
	/*21*/	virtual void* ExtraMouseSample(float, bool) = 0;
	/*22*/	virtual void* IN_KeyEvent(int, ButtonCode_t, char const*) = 0;

	/*23*/	virtual void* WriteUsercmdDeltaToBuffer(void*, int, int, bool) = 0;
	/*24*/	virtual void* EncodeUserCmdToBuffer(void*, int) = 0;
	/*25*/	virtual void* DecodeUserCmdFromBuffer(void*, int) = 0;
	/*26*/	virtual void* View_Render(void*) = 0;
	/*27*/	virtual void RenderView(const CViewSetup& view, int nClearFlags, int whatToDraw) = 0;
	/*28*/	virtual void View_Fade(void*) = 0;
	/*29*/	virtual void SetCrosshairAngle(QAngle const&) = 0;
	/*30*/	virtual void InitSprite(void*, char const*) = 0;
	/*31*/	virtual void ShutdownSprite(void*) = 0;
	/*32*/	virtual int GetSpriteSize(void)const = 0;
	/*33*/	virtual void VoiceStatus(int entindex, int bTalking) = 0;
	/*34*/	virtual void* InstallStringTableCallback(char const*) = 0;
	/*35*/	virtual void FrameStageNotify(ClientFrameStage_t curStage) = 0;
	/*36*/	virtual bool DispatchUserMessage(int, void*) = 0;
	/*37*/	virtual void* SaveInit(int) = 0;
	/*38*/	virtual void* SaveWriteFields(void*, char const*, void*, void*, void*, int) = 0;
	/*39*/	virtual void* SaveReadFields(void*, char const*, void*, void*, void*, int) = 0;
	/*40*/	virtual void* PreSave(void*) = 0;
	/*41*/	virtual void* Save(void*) = 0;
	/*42*/	virtual void* WriteSaveHeaders(void*) = 0;
	/*43*/	virtual void* ReadRestoreHeaders(void*) = 0;
	/*44*/	virtual void* Restore(void*, bool) = 0;
	/*45*/	virtual void* DispatchOnRestore(void) = 0;
	/*46*/	virtual void* GetStandardRecvProxies(void) = 0;
	/*47*/	virtual void* WriteSaveGameScreenshot(char const*) = 0;
	/*48*/	virtual void* EmitSentenceCloseCaption(char const*) = 0;
	/*49*/	virtual void* EmitCloseCaption(char const*, float) = 0;
	/*50*/	virtual void* CanRecordDemo(char*, int)const = 0;
	/*51*/	virtual void* OnDemoRecordStart(char const*) = 0;
	/*52*/	virtual void* OnDemoRecordStop(void) = 0;
	/*53*/	virtual void* OnDemoPlaybackStart(char const*) = 0;
	/*54*/	virtual void* OnDemoPlaybackStop(void) = 0;
	/*55*/	virtual bool ShouldDrawDropdownConsole(void) = 0;
	/*56*/	virtual int GetScreenWidth(void) = 0;
	/*57*/	virtual int GetScreenHeight(void) = 0;
	/*58*/	virtual void* WriteSaveGameScreenshotOfSize(char const*, int, int, bool, bool) = 0;
	/*59*/	virtual void* GetPlayerView(void*) = 0;
	/*60*/	virtual void* SetupGameProperties(void*) = 0;
	/*61*/	virtual void* GetPresenceID(char const*) = 0;
	/*62*/	virtual void* GetPropertyIdString(unsigned int) = 0;
	/*63*/	virtual void* GetPropertyDisplayString(unsigned int, unsigned int, char*, int) = 0;
	/*64*/	virtual void* InvalidateMdlCache(void) = 0;
	/*65*/	virtual void* IN_SetSampleTime(float) = 0;
	/*66*/	virtual void* ReloadFilesInList(void*) = 0;
	/*67*/	virtual void* StartStatsReporting(void*, bool) = 0;
	/*68*/	virtual void* HandleUiToggle(void) = 0;
	/*69*/	virtual bool ShouldAllowConsole(void) = 0;
	/*70*/	virtual void* GetRenamedRecvTableInfos(void) = 0;
	/*71*/	virtual void* GetClientUIMouthInfo(void) = 0;
	/*72*/	virtual void* FileReceived(char const*, unsigned int) = 0;
	/*73*/	virtual void* TranslateEffectForVisionFilter(char const*, char const*) = 0;
	/*74*/	virtual void* ClientAdjustStartSoundParams(void*) = 0;
	/*75*/	virtual void* DisconnectAttempt(void) = 0;
	/*76*/	virtual void* GMOD_ReceiveServerMessage(void*, int) = 0;
	/*77*/	virtual void* GMOD_DoSnapshots(void) = 0;
	/*78*/	virtual void* GMOD_VoiceVolume(unsigned int, float) = 0;
	/*79*/	virtual void* GMOD_OnDrawSkybox(void) = 0;
	/*80*/	virtual void* IN_MouseWheelAnalog(int) = 0;
	/*81*/	virtual void* GMOD_RequestLuaFiles(void) = 0;
	/*82*/	virtual void* GMOD_SignOnStateChanged(int, int, int) = 0;

	bool IsKeyDown(const char* name){ // this doesn't works i think
		bool b = false;
		IN_IsKeyDown(name, b);
		return b;
	}
};