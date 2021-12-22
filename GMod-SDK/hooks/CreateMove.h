#pragma once

#include "../globals.hpp"
#include "../client/usercmd.h"
#include "../tier0/Vector.h"
#include "../hacks/AntiAim.h"
#include "../hacks/LegitAim.h"
#include "../hacks/GunHacks.h"
#include "../hacks/Triggerbot.h"
#include "../hacks/Misc.h"

typedef bool(__thiscall* _CreateMove)(ClientModeShared*, float, CUserCmd*);
_CreateMove oCreateMove;

bool __fastcall hkCreateMove(ClientModeShared* ClientMode,
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif
	float flInputSampleTime, CUserCmd* cmd)
{
	Globals::lastCmd = *cmd;
	uintptr_t stackTop;

	localPlayer = (C_BasePlayer*)ClientEntityList->GetClientEntity(EngineClient->GetLocalPlayer());
	LuaInterface = LuaShared->GetLuaInterface(0);
	*Globals::bSendpacket = true;

	if (localPlayer && localPlayer->IsAlive() && LuaInterface && !Settings::currentlyInFreeCam)
	{

		Globals::lastRealCmd = *cmd;
		DoMisc(cmd);
		BackupCMD(cmd, false);

		int flags = localPlayer->getFlags();

		C_BaseCombatWeapon* currWeapon = localPlayer->GetActiveWeapon();

		bool inCombat = (cmd->buttons & IN_ATTACK);


		//if ((cmd->buttons & IN_ATTACK) && (currWeapon && currWeapon->nextPrimaryAttack() <= GlobalVars->curtime) && (currWeapon->PrimaryAmmoCount() > 0))


		bool antiAimKeyDown;
		getKeyState(Settings::AntiAim::antiAimKey, Settings::AntiAim::antiAimKeyStyle, &antiAimKeyDown, henlo1, henlo2, henlo3);
		if (antiAimKeyDown && !inCombat && Settings::AntiAim::enableAntiAim) {
			AntiAimPitch(cmd, Settings::AntiAim::currentAntiAimPitch);
			AntiAimYaw(cmd, Settings::AntiAim::currentAntiAimYaw);
			if (!Globals::Untrusted)
				cmd->viewangles.FixAngles();
		}

		DoLegitAimbot(cmd);

		TriggerBot(cmd);
		GunHacks(cmd, currWeapon);

		if (currWeapon && currWeapon->SecondaryAmmoCount() > 0 && currWeapon->PrimaryAmmoCount() == 0)
		{
			cmd->buttons |= IN_RELOAD;
			cmd->buttons &= ~(IN_ATTACK | IN_ATTACK2);
		}
		BackupCMD(cmd, true);
	}
	if (Settings::currentlyInFreeCam)
	{
		cmd->buttons = NULL;
		cmd->forwardmove = cmd->sidemove = cmd->upmove = 0.f;
		cmd->viewangles = Globals::lastRealCmd.viewangles;
	}

	oCreateMove(ClientMode, flInputSampleTime, cmd);
	CNetChan* NetChan = EngineClient->GetNetChannelInfo();
	static int m_nChokedPackets = 0;
	bool fakeLagKeyDown = false;
	getKeyState(Settings::Misc::fakeLagKey, Settings::Misc::fakeLagKeyStyle, &fakeLagKeyDown, henlo1, henlo2, henlo3);

	if (fakeLagKeyDown && Settings::Misc::fakeLag)
	{
		if (m_nChokedPackets < (int)Settings::Misc::fakeLagTicks)
		{
			*Globals::bSendpacket = false;
			++m_nChokedPackets;
		}
		else
		{
			*Globals::bSendpacket = true;
			m_nChokedPackets = 0;
		}
	}
	if (*Globals::bSendpacket)
	{
		Globals::lastNetworkedCmd = *cmd;
	}

	return false;
}