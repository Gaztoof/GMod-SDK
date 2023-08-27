#pragma once

#define CheatVersion "1.2.4"

#include <map>
#include <mutex>
#include <d3dx9.h>
#include <d3d9.h>

#include "tier1/checksum_crc.h"
#include "engine/vmatrix.h"
#include "lua_shared/CLuaInterface.h"
#include "lua_shared/CLuaShared.h"
#include "client/CClientEntityList.h"
#include "client/CHLClient.h"
#include "client/ClientModeShared.h"
#include "client/C_BasePlayer.h"
#include "engine/CEngineClient.h"
#include "engine/CVRenderView.h"
#include "client/CInputSystem.h"
#include "engine/CModelRender.h"
#include "tier1/KeyValues.h"
#include "engine/CMaterialSystem.h"
#include "client/CViewRender.h"
#include "tier0/Color.h"
#include "tier0/Vector.h"
#include "client/ConVar.h"
#include "client/CUniformRandomStream.h"
#include "engine/CModelInfo.h"
#include "client/CInput.h"
#include "engine/CModelInfo.h"
#include "engine/CIVDebugOverlay.h"
#include "engine/CGameEventManager.h"
#include "vgui/VPanelWrapper.h"
#include "vphysics/CPhysicsSurfaceProps.h"
#include "vguimatsurface/CMatSystemSurface.h"
#include "client/IPrediction.h"
#include "client/IGameMovement.h"
#include "hacks/ConVarSpoofing.h"

#include <math.h>


#ifdef _WIN64
#define ViewRenderOffset 0xC4
#define GlobalVarsOffset 0x94
#define ClientModeOffset 0x0
#define InputOffset 0x0
#define RandomSeedOffset 0x2
#define PresentModule "gameoverlayrenderer64"
#define PresentPattern "\xFF\x15????\x8B\xF8\xEB\x1E"
#define GetClassNamePattern "\xE8????\x4D\x8B\x47\x10"
#define CL_MovePattern "\xE8????\xFF\x15????\xF2\x0F\x10\x0D????\x85\xFF"
#define PredictionSeedPattern "\x48\x8B\xD1\x8B\x0D????"
#define BSendPacketOffset 0x62
#define ConColorMsgDec "?ConColorMsg@@YAXAEBVColor@@PEBDZZ"
#define CClientStateOffset 0x3
#define CClientStateSize 0x7
#define HostNamePattern "\x48\x8D\x15????\x45\x33\xC0\x48\x8B\x01\xFF\x90????\xB8????\x48\x83\xC4\x28\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC"
#define MoveHelperPattern "\x48\x89\x05????\xE9????\xCC\xCC\xCC\xCC\xCC\xCC\x48\x83\xEC\x28"
#else
#define ViewRenderOffset 0xA6
#define GlobalVarsOffset 0x59
#define ClientModeOffset 0x5
#define InputOffset 0x5
#define RandomSeedOffset 0x5
#define PresentModule "gameoverlayrenderer"
#define PresentPattern  "\xFF\x15????\x8B\xF0\x85\xFF"
#define GetClassNamePattern "\xE8????\x50\x8B\x43\x08"
#define CL_MovePattern "\xE8????\x83\xC4\x08\xFF\x15????\xDC\x25????"
#define BSendPacketOffset 0x2F
#define ConColorMsgDec "?ConColorMsg@@YAXABVColor@@PBDZZ"
#define CClientStateOffset 0x1
#define CClientStateSize 0x5
#endif

typedef HRESULT(__stdcall* _Present)(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
typedef bool(__thiscall* _FireEvent)(CGameEventManager*, IGameEvent*);
typedef void(__thiscall* _PaintTraverse)(void*, VPanel*, bool, bool);
typedef const char* (__thiscall* _GetClassName)(C_BasePlayer*);
typedef void(__cdecl* MsgFn)(Color const& color, const char* msg, ...);

CLuaShared* LuaShared;
CLuaInterface* Lua;
CClientEntityList* ClientEntityList;
CHLClient* CHLclient;
ClientModeShared* ClientMode;
CGlobalVarsBase* GlobalVars;
IEngineTrace* EngineTrace;
C_BasePlayer* localPlayer;
CEngineClient *EngineClient;
CViewRender* ViewRender;
CInputSystem* InputSystem;
CModelRender* ModelRender;
CMaterialSystem* MaterialSystem;
CVRenderView* RenderView;
CCvar* CVar;
CUniformRandomStream* UniformRandomStream;
CModelInfo* ModelInfo;
CInput* Input;
CIVDebugOverlay* IVDebugOverlay;
CGameEventManager* GameEventManager;
VPanelWrapper* PanelWrapper;
CPhysicsSurfaceProps* PhysicsSurfaceProps;
CMatSystemSurface* MatSystemSurface;
void* ClientState; // implement that?
CPrediction* Prediction; // implement that?
CGameMovement* GameMovement;
void* EngineVGui;
void* MoveHelper;

_PaintTraverse oPaintTraverse;
_FireEvent oFireEvent;
char* present; // clean that
_Present oPresent;
MsgFn ConColorMsg;

const void ConPrint(const char* text, Color col)
{
	Color color(153,204,255);
	ConColorMsg(color, "[GMOD-SDK] ");
	ConColorMsg(col, text);
	ConColorMsg(col, "\n");
}


SpoofedConVar* spoofedAllowCsLua;
SpoofedConVar* spoofedCheats;

struct chamsSetting {
	Color hiddenColor = Color(255, 255, 255, 255);
	Color visibleColor = Color(255, 255, 255, 255);
	int hiddenMaterial = 0;
	int visibleMaterial = 0;
	chamsSetting(){
		hiddenColor = Color(255, 255, 255, 255);
		visibleColor = Color(255, 255, 255, 255);
		hiddenMaterial = 0;
		visibleMaterial = 0;
	}
	chamsSetting(Color hiddenCol, Color visibleCol, int hiddenmaterial, int visiblematerial)
	{
		hiddenColor = hiddenCol;
		visibleColor = visibleCol;
		hiddenMaterial = hiddenmaterial;
		visibleMaterial = visiblematerial;
	}
};
#define ColorToRGBA(x) D3DCOLOR_ARGB((uint8_t)(x.fCol[3] * 255), (uint8_t)(x.fCol[0] * 255), (uint8_t)(x.fCol[1] * 255), (uint8_t)(x.fCol[2] * 255))
namespace Globals {
	bool openMenu = false;
	bool nothing;
	bool Untrusted;
	CUserCmd lastCmd;
	CUserCmd lastEndCmd;
	CUserCmd lastRealCmd;
	CUserCmd lastNetworkedCmd;
	matrix3x4_t lastMatrix[128];
	bool choke;
	VPanel* lastPanelIdentifier;

	SpoofedConVar* spoofedAllowCsLua;
	SpoofedConVar* spoofedCheats;

	std::atomic<vmatrix_t> viewMatr;
	std::atomic<std::pair<bool, LPCSTR>> waitingToBeExecuted;
	int executeState = 0;

	int screenWidth, screenHeight;
	int screenWidthCenter, screenHeightCenter;

	void* damageEvent;
	void* deathEvent;

	bool* bSendpacket;
	unsigned int* predictionRandomSeed;
	char* hostName; // UTF-8 encoding C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 59 C3 CC CC CC CC CC CC CC CC CC CC 68 ? ? ? ?

	HWND window;
	WNDPROC oWndProc;
}
namespace Settings {
	ButtonCode_t menuKey = KEY_INSERT;
	int menuKeyStyle = 1;
	Color menuColor(142, 181, 53);

	std::map<C_BasePlayer*, std::pair<bool, int>> friendList;
	std::vector<C_BasePlayer*> selectedFriendList;

	std::map<std::string, bool> luaEntList;
	std::vector<std::string> selectedLuaEntList;

	float lastHitmarkerTime = -1.f;
	std::mutex friendListMutex;
	std::mutex luaEntListMutex;
	char ScriptInput[131070];

	bool currentlyInFreeCam;
	namespace Chams {
		chamsSetting playerChamsSettings;

		chamsSetting teamMateSettings;

		chamsSetting ragdollChamsSettings;
		chamsSetting weaponChamsSettings;

		chamsSetting npcChamsSettings;

		chamsSetting armChamsSettings;

		chamsSetting localPlayerChamsSettings;
		chamsSetting netLocalChamsSettings;
	}

	namespace ESP {
		int infosEmplacement;
		bool espDormant;
		bool espBoundingBox;
		Color espBoundingBoxColor(255, 255, 255);
		bool espHealthBar;
		Color espHealthColor(255, 255, 255);
		bool espName;
		Color espNameColor(255, 255, 255);
		bool weaponText;
		Color espWeaponColor(255, 255, 255);
		bool weaponAmmo;
		Color espAmmoColor(255, 255, 255);
		bool espDistance;
		Color espDistanceColor(255, 255, 255);
		bool skeletonEsp;		
		bool skeletonDetails;
		Color skeletonEspColor(255, 255, 255);
		int espShapeInt = 0;

		bool entEsp = false;

		bool onlyFriends = false;
	}

	namespace Visuals {
		float fov = 120.f;
		bool fovEnabled = false;
		float viewModelFov = 90.f;
		bool viewModelFovEnabled = false;
		bool noVisualRecoil;
		Color worldColor(17.f, 33.f, 71.f, 255.f);
		bool changeWorldColor;
		bool fullBright;
		bool disableSkyBox;
	}

	namespace Aimbot {
		float aimbotFOV;
		bool silentAim;
		bool lockOnTarget;
		ButtonCode_t aimbotKey = KEY_NONE;
		int aimbotKeyStyle = 1;
		bool enableAimbot;
		int aimbotHitbox;
		bool aimbotAutoWall;
		bool aimbotAutoFire;
		float aimbotMinDmg;
		bool aimbotFovEnabled;
		bool drawAimbotFov;
		int aimbotSelection;
		bool drawAimbotHeadlines;
		bool aimAtTeammates;
		bool aimAtFriends;
		bool onlyAimAtFriends;
		C_BasePlayer* finalTarget = nullptr;

		bool pistolFastShoot;

		bool smoothing;
		float smoothSteps;

		Color fovColor(255, 255, 255);
	}

	namespace Triggerbot {
		bool triggerbot;
		bool triggerbotHead;
		bool triggerbotChest;
		bool triggerbotStomach;
		bool triggerbotFastShoot;
	}

	namespace AntiAim {
		int currentAntiAimPitch = 0;
		int currentAntiAimYaw = 0;
		bool enableAntiAim;
		ButtonCode_t antiAimKey = KEY_NONE;
		int antiAimKeyStyle = 1; // KEY_NONE;
		float fakePitch;
	}

	namespace Misc {
		bool scriptDumper;

		bool drawSpectators;

		Color crossHairColor(255, 255, 255);
		bool drawCrosshair;

		bool quickStop;

		bool killMessage;
		bool killMessageOOC;

		bool bunnyHop;
		bool autoStrafe;
		int autoStrafeStyle;

		bool fastWalk;
		bool edgeJump;

		bool optiClamp;
		float optiStrength;
		bool optiStyle;
		bool optiRandomization;
		bool optiAutoStrafe;

		float crosshairSize;
		
		bool thirdperson;
		ButtonCode_t thirdpersonKey = KEY_NONE;
		int thirdpersonKeyStyle = 1;
		float thirdpersonDistance;

		bool removeHands;

		bool flashlightSpam;
		bool useSpam;

		bool noRecoil;
		bool noSpread;

		bool freeCam;
		ButtonCode_t freeCamKey = KEY_NONE;
		int freeCamKeyStyle = 1;
		float freeCamSpeed;

		bool hitmarkerSoundEnabled;
		int hitmarkerSound;
		bool hitmarker;
		float hitmarkerSize = 10.f;

		bool fakeLag;
		float fakeLagTicks;
		ButtonCode_t fakeLagKey = KEY_NONE;
		int fakeLagKeyStyle = 1;

		bool zoom;
		ButtonCode_t zoomKey = KEY_NONE;
		int zoomKeyStyle = 1;
		float zoomFOV = 90.f;

		bool svCheats;
		bool svAllowCsLua;

		float rainbowSpeed = 1.f;
	}
}

void rainbowColor(Color& col, float speed) noexcept
{
	if (!col.rainbow)return;
	col.fCol[0] = std::sin(speed * GlobalVars->realtime) * 0.5f + 0.5f;
	col.fCol[1] = std::sin(speed * GlobalVars->realtime + 2 * PI / 3) * 0.5f + 0.5f;
	col.fCol[2] = std::sin(speed * GlobalVars->realtime + 4 * PI / 3) * 0.5f + 0.5f;
}
// Make sure to add everything to ConfigSystem.h too! both ResetConfig, LoadConfig, and SaveConfig!!
