#pragma once

#pragma once

#include "../globals.hpp"
#include "../hacks/ScriptDumper.h"
#include <Windows.h>
#include <optional>


typedef bool(__thiscall* _RunStringEx)(CLuaInterface*, const char*, const char*, const char*, bool, bool, bool, bool);
_RunStringEx oRunStringEx = nullptr;

bool __fastcall hkRunStringEx(CLuaInterface* _this,
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif
	const char* filename, const char* path, const char* stringToRun, bool run, bool printErrors, bool dontPushErrors, bool noReturns)
{
    std::optional<std::string> script = {};
    if (Settings::Misc::scriptDumper)
        script = SaveScript(std::string(filename), std::string(stringToRun));

	return oRunStringEx(_this, filename, path, script.has_value() ? script.value().c_str() : stringToRun, run, printErrors, dontPushErrors, noReturns);
}


typedef int (__thiscall* _CloseLuaInterfaceFn)(CLuaShared*, CLuaInterface*);
_CloseLuaInterfaceFn oCloseLuaInterfaceFn;
int __fastcall hkCloseInterfaceLuaFn(CLuaShared* _this,
#ifndef _WIN64
    void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif
    CLuaInterface* luaInterface) 
{
    if (luaInterface == Lua) Lua = nullptr;
    return oCloseLuaInterfaceFn(_this, luaInterface);
}


typedef CLuaInterface* (__thiscall* _CreateLuaInterfaceFn)(CLuaShared*, LuaInterfaceType, bool);
_CreateLuaInterfaceFn oCreateLuaInterfaceFn;
CLuaInterface* __fastcall hkCreateLuaInterfaceFn(CLuaShared* _this,
#ifndef _WIN64
    void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif 
    LuaInterfaceType luaState, bool renew) 
{
    auto luaInterface = oCreateLuaInterfaceFn(_this, luaState, renew);
    if (luaState != LuaInterfaceType::LUA_CLIENT) return luaInterface;

    Lua = luaInterface;

    if(!oRunStringEx) oRunStringEx = VMTHook<_RunStringEx>((PVOID**)Lua, (PVOID)hkRunStringEx, 111, true);

    return Lua;
}