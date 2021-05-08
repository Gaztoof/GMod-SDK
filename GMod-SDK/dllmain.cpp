#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>

#include "Vector.h"

#include "Interface.h"
#include "globals.h"

#include "CHLClient.h"
#include "ClientModeShared.h"
#include "CLuaInterface.h"
#include "CLuaShared.h"
#include "CLuaConVars.h"
#include "CClientEntityList.h"
#include "C_BasePlayer.h"
#include "c_basecombatweapon.h"

#include "DrawModelExecute.h"
#include "CreateMove.h"
#include "FrameStageNotify.h"
#include "RenderView.h"
#include "Memory.h"
#include "Present.h"

using namespace std;

void Main()
{
    srand(time(nullptr));
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);
    SetConsoleTitle(L"GMod SDK - WIP - Coded by t.me/Gaztoof");

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
    engineTrace = (IEngineTrace*)GetInterface("engine.dll", "EngineTraceClient003");


    ViewRender = **(CViewRender***)((*(uintptr_t**)CHLclient)[27] + 0x5); // CHLClient::Shutdown points to _view https://i.imgur.com/3Ad96gY.png


    clientMode = **(ClientModeShared***)((*(uintptr_t**)(CHLclient))[10] + 0x5); // HudProcessInput points to g_pClientMode, and we retrieve it.  https://i.imgur.com/h0qYd5q.png I got the information from the .dylib -> https://i.imgur.com/kBaS7Vq.png
    GlobalVars = **(CGlobalVarsBase***)((*(uintptr_t**)CHLclient)[0] + 0x59); // CHLClient::Init points to gpGlobals https://i.imgur.com/aIwpS45.png
    //Input = **(void***)((*(uintptr_t**)CHLclient)[20] + 0x4); // CHLClient::CreateMove points to input https://i.imgur.com/TnEcetn.png <- make CInput class tysm gaz
    

    localPlayer = (C_BasePlayer*)ClientEntityList->GetClientEntity(EngineClient->GetLocalPlayer());

    oCreateMove = (_CreateMove)VMTHook((PVOID**)clientMode, (PVOID)hkCreateMove, 21);
    oFrameStageNotify = (_FrameStageNotify)VMTHook((PVOID**)CHLclient, hkFrameStageNotify, 35);
    oRenderView = (_RenderView)VMTHook((PVOID**)ViewRender, (PVOID)hkRenderView, 6);

    oDrawModelExecute = (_DrawModelExecute)VMTHook((PVOID**)ModelRender, (PVOID)hkDrawModelExecute, 20);

    uintptr_t present = (findPattern("gameoverlayrenderer", "\xFF\x15????\x8B\xF8\x85\xDB") + 0x2);
    oPresent = **(_Present**)(present);
    **(_Present***)(present) = (_Present*)hkPresent;
}

BOOL APIENTRY DllMain(HMODULE hModule, uintptr_t ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        std::thread(Main).detach();
    return TRUE;
}

