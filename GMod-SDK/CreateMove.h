#pragma once

#include "globals.h"
#include "usercmd.h"
#include "ClientModeShared.h"
#include "Vector.h"
#include "AntiAim.h"
#include "LegitAim.h"
#include "GunHacks.h"
#include "Triggerbot.h"
#include "Misc.h"

typedef bool(__thiscall* _CreateMove)(ClientModeShared*, float, CUserCmd*);
_CreateMove oCreateMove;

bool __fastcall hkCreateMove(ClientModeShared* ClientMode,
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif
	float flInputSampleTime, CUserCmd* cmd)
{
	Settings::lastCmd = *cmd;
	uintptr_t stackTop;
	//_asm mov stackTop, ebp;
	//bool& bSendpacket = *(***(bool****)(stackTop)-1);
	bool bSendpacket = false;

	localPlayer = (C_BasePlayer*)ClientEntityList->GetClientEntity(EngineClient->GetLocalPlayer());
	LuaInterface = LuaShared->GetLuaInterface(0);

	if (localPlayer && localPlayer->IsAlive() && LuaInterface && !Settings::currentlyInFreeCam)
	{
		Settings::lastRealCmd = *cmd;
		DoMisc(cmd);
		BackupCMD(cmd, false);

		int flags = localPlayer->getFlags();

		C_BaseCombatWeapon* currWeapon = localPlayer->GetActiveWeapon();

		bool inCombat = (cmd->buttons & IN_ATTACK);

		GunHacks(currWeapon);

		//if ((cmd->buttons & IN_ATTACK) && (currWeapon && currWeapon->nextPrimaryAttack() <= GlobalVars->curtime) && (currWeapon->PrimaryAmmoCount() > 0))


		//antiaim v
		bool antiAimKeyDown;
		getKeyState(Settings::AntiAim::antiAimKey, Settings::AntiAim::antiAimKeyStyle, &antiAimKeyDown, henlo1, henlo2, henlo3);
		if (antiAimKeyDown && !inCombat && Settings::AntiAim::enableAntiAim) {
			AntiAimPitch(cmd, Settings::AntiAim::currentAntiAimPitch);
			AntiAimYaw(cmd, Settings::AntiAim::currentAntiAimYaw, bSendpacket);
			if (!Settings::Untrusted)
				cmd->viewangles.FixAngles();
		}

		DoLegitAimbot(cmd);

		TriggerBot(cmd);

		// implement localplayer->movetype() and make sure it's not ladder or noclip before bhopping

		if (currWeapon && currWeapon->SecondaryAmmoCount() > 0 && currWeapon->PrimaryAmmoCount() == 0)
		{
			cmd->buttons |= IN_RELOAD;
			cmd->buttons &= ~(IN_ATTACK | IN_ATTACK2);
		}
		BackupCMD(cmd, true);
		EngineClient->GetViewAngles(lastRealAngles);
	}
	if (Settings::currentlyInFreeCam)
	{
		cmd->buttons &= ~(IN_FORWARD | IN_BACK | IN_LEFT | IN_RIGHT | IN_JUMP | IN_DUCK);
		cmd->forwardmove = cmd->sidemove = cmd->upmove = 0.f;
		cmd->viewangles = Settings::lastRealCmd.viewangles;
	}
	oCreateMove(ClientMode, flInputSampleTime, cmd);
	return false;
}