#pragma once

#include <map>
#include <mutex>
#include <d3dx9.h>
#include <d3d9.h>

#include "CLuaInterface.h"
#include "CLuaShared.h"
#include "CClientEntityList.h"
#include "CHLClient.h"
#include "ClientModeShared.h"
#include "C_BasePlayer.h"
#include "CEngineClient.h"
#include "CVRenderView.h"
#include "CInputSystem.h"
#include "CModelRender.h"
#include "KeyValues.h"
#include "CMaterialSystem.h"
#include "CViewRender.h"
#include "Color.h"
#include "Vector.h"
#include "ConVar.h"
#include "CUniformRandomStream.h"
#include "CModelInfo.h"
#include "CInput.h"
#include "CModelInfo.h"
#include "CIVDebugOverlay.h"
#include "CGameEventManager.h"
#include "VPanelWrapper.h"

#ifdef _WIN64
#define ViewRenderOffset 0xC4
#define GlobalVarsOffset 0x94
#define ClientModeOffset 0x0
#define InputOffset 0x0
#define RandomSeedOffset 0x2
#define PresentModule "gameoverlayrenderer64"
#define PresentPattern "\xFF\x15????\x8B\xF8\x48\x85\xDB\x74\x37\x85\xC0\x75\x33\x38\x43\x5B\x74\x2E\xF3\x0F\x10\x05????\x44\x8D\x48\x01\x4C\x8B\x16\x45\x33\xC0\x89\x44\x24\x30\x33\xD2\xF3\x0F\x11\x44\x24?\x48\x8B\xCE\x89\x44\x24\x20\x41\xFF\x92????\x8B\xC7\x4C\x8D\x9C\x24????"
#define GetClassNamePattern "\xE8????\x4D\x8B\x47\x10"
#define CL_MovePattern "\xE8????\xFF\x15????\xF2\x0F\x10\x0D????\x85\xFF"
#define BSendPacketOffset 0x62
#else
#define ViewRenderOffset 0xA6
#define GlobalVarsOffset 0x59
#define ClientModeOffset 0x5
#define InputOffset 0x5
#define RandomSeedOffset 0x5
#define PresentModule "gameoverlayrenderer"
#define PresentPattern  "\xFF\x15????\x8B\xF8\x85\xDB"
#define GetClassNamePattern "\xE8????\x50\x8B\x43\x08"
#define CL_MovePattern "\xE8????\x83\xC4\x08\xFF\x15????\xDC\x25????"
#define BSendPacketOffset 0x2F
#endif

typedef HRESULT(__stdcall* _Present)(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
typedef bool(__thiscall* _FireEvent)(CGameEventManager*, IGameEvent*);
typedef void(__thiscall* _PaintTraverse)(void*, VPanel*, bool, bool);
typedef const char* (__thiscall* _GetClassName)(C_BasePlayer*);

_PaintTraverse oPaintTraverse;
_FireEvent oFireEvent;
char* present; // clean that
bool* bSendpacket;

CLuaShared* LuaShared;
CClientEntityList* ClientEntityList;
CHLClient* CHLclient;
ClientModeShared* ClientMode;
CGlobalVarsBase* GlobalVars;
IEngineTrace* EngineTrace;
CLuaInterface* LuaInterface;
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
void* MatSystemSurface;
VPanelWrapper* PanelWrapper;

int screenWidth, screenHeight;

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

namespace Settings {
	bool openMenu = true;
	ButtonCode_t menuKey = KEY_INSERT;
	int menuKeyStyle = 1;
	Color menuColor(0, 255, 0);
	bool nothing;
	bool Untrusted;
	CUserCmd lastCmd;
	CUserCmd lastRealCmd;
	CUserCmd lastNetworkedCmd;
	bool choke; 

	std::map<C_BasePlayer*, std::pair<bool, int>> friendList;
	std::map<const char*, bool> luaEntList;

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

	}
	namespace ESP {
		int infosEmplacement;
		bool espDormant;
		bool espBoundingBox;
		Color espBoundingBoxColor(255, 255, 255);
		bool espHealthBar;
		bool espName;
		bool weaponText;
		bool weaponAmmo;
		bool espDistance;
		bool skeletonEsp;
		bool skeletonDetails;
		Color skeletonEspColor(255, 255, 255);
		int espShapeInt = 0;

		bool entEsp = false;

	}
	namespace Visuals {
		float fov = 130.f;
		float viewModelFOV = 130.f;
		bool noVisualRecoil;
		Color worldColor(17.f, 33.f, 71.f, 255.f);
		bool changeWorldColor;

		bool disableSkyBox;

	}
	namespace AntiAim {
		int currentAntiAimPitch = 0;
		int currentAntiAimYaw = 0;
		bool enableAntiAim;
		ButtonCode_t antiAimKey = KEY_NONE;
		int antiAimKeyStyle = 1; // KEY_NONE;
		float fakePitch;
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
		C_BasePlayer* finalTarget = nullptr;

		bool aimAtFriends;
		bool onlyAimAtFriends;

	}
	namespace Misc {

		bool drawSpectators;
		bool drawCrosshair;

		bool quickStop;

		bool killMessage;
		bool killMessageOOC;

		bool bunnyHop;
		bool autoStrafe;
		int autoStrafeStyle;

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

		bool fakeLag;
		ButtonCode_t fakeLagKey = KEY_NONE;
		int fakeLagKeyStyle = 1;

		bool zoom;
		ButtonCode_t zoomKey = KEY_NONE;
		int zoomKeyStyle = 1;
		float zoomFOV = 90.f;

	}
	namespace Triggerbot {
		bool triggerBot;
		bool triggerBotHead;
		bool triggerBotChest;
		bool triggerBotStomach;
		bool triggerbotFastShoot;
	}
}
// Make sure to add everything to ConfigSystem.h too! both ResetConfig, LoadConfig, and SaveConfig!!