#pragma once

#pragma once

#include "../globals.hpp"
#include "../hacks/ScriptDumper.h"
#include <Windows.h>
#include <optional>

typedef bool(__thiscall* _RunStringEx)(CLuaInterface*, const char*, const char*, const char*, bool, bool, bool, bool);
_RunStringEx oRunStringEx;

bool __fastcall hkRunStringEx(CLuaInterface* _this,
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif
	const char* filename, const char* path, const char* stringToRun, bool run, bool printErrors, bool dontPushErrors, bool noReturns)
{
	const std::optional<std::string> script = SaveScript(std::string(filename), std::string(stringToRun));

	return oRunStringEx(_this, filename, path, script.has_value() ? script.value().c_str() : stringToRun, run, printErrors, dontPushErrors, noReturns);
}