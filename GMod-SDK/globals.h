#pragma once

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

CLuaShared* LuaShared;
CClientEntityList* ClientEntityList;
CHLClient* CHLclient;
ClientModeShared* clientMode;
CGlobalVarsBase* GlobalVars;
IEngineTrace* engineTrace;
CLuaInterface* LuaInterface;
C_BasePlayer* localPlayer;
CEngineClient *EngineClient;
CViewRender* ViewRender;
CInputSystem* InputSystem;
CModelRender* ModelRender;
CMaterialSystem* MaterialSystem;
CVRenderView* RenderView;
CCvar* CVar;

bool disableSkyBox = true;
bool openMenu = true;
bool styleSingleWindow = false;


bool visualsOpen = false;


struct chamsSetting {
	Color hiddenColor = Color(255, 255, 255, 255);
	Color visibleColor = Color(255, 255, 255, 255);
	int hiddenMaterial = 0;
	int visibleMaterial = 0;
	bool enableVisible = false;
	bool enableHidden = false;
	chamsSetting(){
		hiddenColor = Color(255, 255, 255, 255);
		visibleColor = Color(255, 255, 255, 255);
		hiddenMaterial = 0;
		visibleMaterial = 0;
		enableVisible = false;
		enableHidden = false;
	}
	chamsSetting(Color hiddenCol, Color visibleCol, int hiddenmaterial, int visiblematerial, bool visible, bool hidden)
	{
		hiddenColor = hiddenCol;
		visibleColor = visibleCol;
		hiddenMaterial = hiddenmaterial;
		visibleMaterial = visiblematerial;
		enableVisible = visible;
		enableHidden = hidden;
	}
};
chamsSetting playerChamsSettings;

chamsSetting ragdollChamsSettings;
chamsSetting weaponChamsSettings;

chamsSetting npcChamsSettings;

chamsSetting armChamsSettings;

Color worldColor(17.f, 33.f, 71.f, 255.f);

float fov = 130.f;
float viewModelFOV = 130.f;

bool hideHands = false;