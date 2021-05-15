#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>

#include "Vector.h"

#include "Interface.h"
#include "globals.h"

#include "DrawModelExecute.h"
#include "CreateMove.h"
#include "FrameStageNotify.h"
#include "RenderView.h"
#include "Present.h"
#include "FireEvent.h"
#include "PaintTraverse.h"

#include "Memory.h"


using namespace std;


void Main()
{
    ZeroMemory(Settings::ScriptInput, sizeof(Settings::ScriptInput));
    srand(time(nullptr));
#ifdef _DEBUG
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);
    SetConsoleTitle(L"GMod SDK - WIP - Coded by t.me/Gaztoof");
#endif

    ConfigSystem::LoadConfig("Default");

    LuaShared = (CLuaShared*)GetInterface("lua_shared.dll", "LUASHARED003");
    LuaInterface = (CLuaInterface*)LuaShared->GetLuaInterface(0);

    ClientEntityList = (CClientEntityList*)GetInterface("client.dll", "VClientEntityList003");
    CHLclient = (CHLClient*)GetInterface("client.dll", "VClient017");

    MaterialSystem = (CMaterialSystem*)GetInterface("materialsystem.dll", "VMaterialSystem080");

    InputSystem = (CInputSystem*)GetInterface("inputsystem.dll", "InputSystemVersion001");
    CVar = (CCvar*)GetInterface("vstdlib.dll", "VEngineCvar007");

    EngineClient = (CEngineClient*)GetInterface("engine.dll", "VEngineClient015");
    ModelRender = (CModelRender*)GetInterface("engine.dll", "VEngineModel016");
    RenderView = (CVRenderView*)GetInterface("engine.dll", "VEngineRenderView014");
    EngineTrace = (IEngineTrace*)GetInterface("engine.dll", "EngineTraceClient003");
    IVDebugOverlay = (CIVDebugOverlay*)GetInterface("engine.dll", "VDebugOverlay003");
    GameEventManager = (CGameEventManager*)GetInterface("engine.dll", "GAMEEVENTSMANAGER002");
    MatSystemSurface = (void*)GetInterface("vguimatsurface.dll", "VGUI_Surface030");
    PanelWrapper = (VPanelWrapper*)GetInterface("vgui2.dll", "VGUI_Panel009");

    
    ViewRender = GetVMT<CViewRender>((uintptr_t)CHLclient, 2, ViewRenderOffset); // CHLClient::Shutdown points to _view https://i.imgur.com/3Ad96gY.png

    ModelInfo = (CModelInfo*)GetInterface("engine.dll", "VModelInfoClient006");


    ClientMode = GetVMT<ClientModeShared>((uintptr_t)CHLclient, 10, ClientModeOffset); // HudProcessInput points to g_pClientMode, and we retrieve it.  https://i.imgur.com/h0qYd5q.png I got the information from the .dylib -> https://i.imgur.com/kBaS7Vq.png
    GlobalVars = GetVMT<CGlobalVarsBase>((uintptr_t)CHLclient, 0, GlobalVarsOffset); // CHLClient::Init points to gpGlobals https://i.imgur.com/aIwpS45.png
    Input = GetVMT<CInput>((uintptr_t)CHLclient, 10, InputOffset); // CHLClient::CreateMove points to input https://i.imgur.com/TnEcetn.png <- make CInput class tysm gaz


    UniformRandomStream = GetVMT<CUniformRandomStream>((uintptr_t)GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed"), RandomSeedOffset); // RandomSeed points to s_pUniformStream https://i.imgur.com/bddk0QK.png
    
    localPlayer = (C_BasePlayer*)ClientEntityList->GetClientEntity(EngineClient->GetLocalPlayer());

    oCreateMove = (_CreateMove)VMTHook((PVOID**)ClientMode, (PVOID)hkCreateMove, 21);
    oFrameStageNotify = (_FrameStageNotify)VMTHook((PVOID**)CHLclient, hkFrameStageNotify, 35);
    oRenderView = (_RenderView)VMTHook((PVOID**)ViewRender, (PVOID)hkRenderView, 6);
    oFireEvent = (_FireEvent)VMTHook((PVOID**)GameEventManager, (PVOID)hkFireEvent, 7);
    oPaintTraverse = (_PaintTraverse)VMTHook((PVOID**)PanelWrapper, (PVOID)hkPaintTraverse, 41);

    oDrawModelExecute = (_DrawModelExecute)VMTHook((PVOID**)ModelRender, (PVOID)hkDrawModelExecute, 20);
    // /!\\ ^ When adding hooks, make sure you add them to GUI.h's Unload button too!


    present = GetRealFromRelative((char*)findPattern(PresentModule, PresentPattern), 0x2);

    //GlobalVars->maxClients
    //GlobalVars + 0x14 = 1 will let u do anything lua related
    
// To-do: clean the following:
#ifdef _WIN64
    oPresent = *(_Present*)(present);
    *(_Present**)(present) = (_Present*)hkPresent;
#else
    oPresent = **(_Present**)(present);
    **(_Present***)(present) = (_Present*)hkPresent;
#endif
}

BOOL APIENTRY DllMain(HMODULE hModule, uintptr_t ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        std::thread(Main).detach();
    return TRUE;
}

