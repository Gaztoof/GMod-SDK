#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>

#include "tier0/Vector.h"

#include "Interface.h"
#include "globals.hpp"

#include "hooks/DrawModelExecute.h"
#include "hooks/CreateMove.h"
#include "hooks/FrameStageNotify.h"
#include "hooks/RenderView.h"
#include "hooks/Present.h"
#include "hooks/PaintTraverse.h"
#include "hooks/RunStringEx.h"
#include "hooks/ProcessGMODServerToClient.h"

#include "Memory.h"

#include "hacks/ConVarSpoofing.h"
#include "engine/inetmessage.h"
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
    ConColorMsg = (MsgFn)GetProcAddress(GetModuleHandleW(L"tier0.dll"), ConColorMsgDec);

    ConPrint("Successfully injected!", Color(0, 255, 0));

    ConfigSystem::LoadConfig("Default");
    Globals::bSendpacket = (bool*)(GetRealFromRelative((char*)findPattern("engine", CL_MovePattern, "CL_MOVE"), 0x1, 5) + BSendPacketOffset);

    DWORD originalProtection;
    VirtualProtect(Globals::bSendpacket, sizeof(bool), PAGE_EXECUTE_READWRITE, &originalProtection);

    EngineClient = (CEngineClient*)GetInterface("engine.dll", "VEngineClient015");

    // x64: thats directly the vtable pointer // CEngineClient::IsPaused points to clientstate https://i.imgur.com/4aWvQbs.png
    ClientState = GetRealFromRelative((*(char***)(EngineClient))[84], CClientStateOffset, CClientStateSize, false) ;

    //void* plim = (plim*)(GetRealFromRelative((char*), 0x1, 5) + BSendPacketOffset);

    LuaShared = (CLuaShared*)GetInterface("lua_shared.dll", "LUASHARED003");

    ClientEntityList = (CClientEntityList*)GetInterface("client.dll", "VClientEntityList003");
    CHLclient = (CHLClient*)GetInterface("client.dll", "VClient017");

    MaterialSystem = (CMaterialSystem*)GetInterface("materialsystem.dll", "VMaterialSystem080");

    InputSystem = (CInputSystem*)GetInterface("inputsystem.dll", "InputSystemVersion001");
    CVar = (CCvar*)GetInterface("vstdlib.dll", "VEngineCvar007");

    ModelRender = (CModelRender*)GetInterface("engine.dll", "VEngineModel016");
    RenderView = (CVRenderView*)GetInterface("engine.dll", "VEngineRenderView014");
    EngineTrace = (IEngineTrace*)GetInterface("engine.dll", "EngineTraceClient003");
    IVDebugOverlay = (CIVDebugOverlay*)GetInterface("engine.dll", "VDebugOverlay003");
    GameEventManager = (CGameEventManager*)GetInterface("engine.dll", "GAMEEVENTSMANAGER002");
    MatSystemSurface = (CMatSystemSurface*)GetInterface("vguimatsurface.dll", "VGUI_Surface030");
    PanelWrapper = (VPanelWrapper*)GetInterface("vgui2.dll", "VGUI_Panel009");
    PhysicsSurfaceProps = (CPhysicsSurfaceProps*)GetInterface("vphysics.dll", "VPhysicsSurfaceProps001");

    
    ViewRender = GetVMT<CViewRender>((uintptr_t)CHLclient, 2, ViewRenderOffset); // CHLClient::Shutdown points to _view https://i.imgur.com/3Ad96gY.png

    ModelInfo = (CModelInfo*)GetInterface("engine.dll", "VModelInfoClient006");


    ClientMode = GetVMT<ClientModeShared>((uintptr_t)CHLclient, 10, ClientModeOffset); // HudProcessInput points to g_pClientMode, and we retrieve it.  https://i.imgur.com/h0qYd5q.png I got the information from the .dylib -> https://i.imgur.com/kBaS7Vq.png
    GlobalVars = GetVMT<CGlobalVarsBase>((uintptr_t)CHLclient, 0, GlobalVarsOffset); // CHLClient::Init points to gpGlobals https://i.imgur.com/aIwpS45.png
    Input = GetVMT<CInput>((uintptr_t)CHLclient, 20, InputOffset); // CHLClient::CreateMove points to input https://i.imgur.com/TnEcetn.png


    UniformRandomStream = GetVMT<CUniformRandomStream>((uintptr_t)GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed"), RandomSeedOffset); // RandomSeed points to s_pUniformStream https://i.imgur.com/bddk0QK.png
    
    localPlayer = (C_BasePlayer*)ClientEntityList->GetClientEntity(EngineClient->GetLocalPlayer());

    oCreateMove = VMTHook<_CreateMove>((PVOID**)ClientMode, (PVOID)hkCreateMove, 21);
    oFrameStageNotify = VMTHook< _FrameStageNotify>((PVOID**)CHLclient, hkFrameStageNotify, 35);
    oRenderView = VMTHook<_RenderView>((PVOID**)ViewRender, (PVOID)hkRenderView, 6);
    oPaintTraverse = VMTHook< _PaintTraverse>((PVOID**)PanelWrapper, (PVOID)hkPaintTraverse, 41);

    oDrawModelExecute = VMTHook< _DrawModelExecute>((PVOID**)ModelRender, (PVOID)hkDrawModelExecute, 20);
    oProcessGMOD_ServerToClient = VMTHook< _ProcessGMOD_ServerToClient>((PVOID**)ClientState, (PVOID)hkProcessGMOD_ServerToClient, 64);

    //RunStringEx is getting hooked at the end of this function
    // /!\\ ^ When adding hooks, make sure you add them to GUI.h's Unload button too!


    present = GetRealFromRelative((char*)findPattern(PresentModule, PresentPattern, "Present"), 0x2, 6, false);

    EngineClient->ClientCmd_Unrestricted("gmod_mcore_test 0");
    
    Globals::damageEvent = (void*)new DamageEvent();
    Globals::deathEvent = (void*)new DeathEvent();

    GameEventManager->AddListener((IGameEventListener2*)Globals::damageEvent, "player_hurt", false);
    GameEventManager->AddListener((IGameEventListener2*)Globals::deathEvent, "entity_killed", false);
    
    
    ConVar* cvar = CVar->FindVar("mat_fullbright");
    cvar->RemoveFlags(FCVAR_CHEAT);
    
    //This'll let you change your name ingame freely
    cvar = CVar->FindVar("name");
    cvar->RemoveFlags(FCVAR_SERVER_CAN_EXECUTE);
    cvar->DisableCallback();
    

    //GlobalVars->maxClients
    //GlobalVars + 0x14 = 1 will let u do anything lua related
    oPresent = *(_Present*)(present);
    *(_Present**)(present) = (_Present*)hkPresent;

    //EngineClient->ClientCmd_Unrestricted("play \"items/suitchargeok1.wav\"");
        //Sleep(2200);
    Sleep(1000);
    MatSystemSurface->PlaySound("HL1/fvox/bell.wav");
    Sleep(1100);
    MatSystemSurface->PlaySound("HL1/fvox/activated.wav");
    Globals::openMenu = true;

    while (TRUE)
    {

        LuaInterface = LuaShared->GetLuaInterface((unsigned char)LuaSomething::LUA_CLIENT);
        if (LuaInterface)
        {
            oRunStringEx = VMTHook< _RunStringEx>((PVOID**)LuaInterface, (PVOID)hkRunStringEx, 111);
            break;

        }
        Sleep(1);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, uintptr_t ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        std::thread(Main).detach();
    return TRUE;
}

