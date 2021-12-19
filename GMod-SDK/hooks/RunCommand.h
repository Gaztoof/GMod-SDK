#pragma once

#pragma once

#include "../globals.hpp"
#include <Windows.h>
#include <optional>

typedef void(__thiscall* _RunCommand)(void*, CBasePlayer*, CUserCmd*, void*);
_RunCommand oRunCommand;

void __fastcall hkRunCommand(void* _this,
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif
	CBasePlayer* player, CUserCmd* ucmd, void* moveHelper)
{
	// https://www.unknowncheats.me/forum/2193961-post4.html
	if (Settings::Misc::noRecoil)
	{
		QAngle angle;
		EngineClient->GetViewAngles(angle);
		oRunCommand(_this, player, ucmd, moveHelper);
		EngineClient->SetViewAngles(angle);
	}
	else oRunCommand(_this, player, ucmd, moveHelper);
}