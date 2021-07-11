#pragma once

#pragma once

#include "../globals.hpp"
#include "../hacks/ScriptDumper.h"
#include <Windows.h>

typedef bool(__thiscall* _RunStringEx)(CLuaInterface*, const char*, const char*, const char*, bool, bool, bool, bool);
_RunStringEx oRunStringEx;

bool __fastcall hkRunStringEx(CLuaInterface* _this,
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif
	const char* filename, const char* path, const char* stringToRun, bool run, bool printErrors, bool dontPushErrors, bool noReturns)
{
	const std::string script = SaveScript(std::string(filename), std::string(stringToRun));
	const char* content = script.c_str();

	return oRunStringEx(_this, filename, path, content, run, printErrors, dontPushErrors, noReturns);
}