#pragma once

#include "globals.h"
#include "Misc.h"


void DoEvent(IGameEvent* event)
{
	KillMessage(event);
	HitmarkerSound(event);
}
bool __fastcall hkFireEvent(CGameEventManager* manager,
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif 
	IGameEvent* event)
{
	DoEvent(event);
	return oFireEvent(manager, event);
}
