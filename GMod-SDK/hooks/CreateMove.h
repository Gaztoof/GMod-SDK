#pragma once

#include "../globals.hpp"
#include "../client/usercmd.h"
#include "../tier0/Vector.h"
#include "../hacks/AntiAim.h"
#include "../hacks/LegitAim.h"
#include "../hacks/GunHacks.h"
#include "../hacks/Triggerbot.h"
#include "../hacks/Misc.h"
#include "../hacks/Prediction.h"

typedef bool(__thiscall* _CreateMove)(ClientModeShared*, float, CUserCmd*);
_CreateMove oCreateMove;

bool __fastcall hkCreateMove(ClientModeShared* ClientMode,
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif
	float flInputSampleTime, CUserCmd* cmd)
{
//	oCreateMove(ClientMode, flInputSampleTime, cmd);
	Globals::lastCmd = *cmd;
	uintptr_t stackTop;

	localPlayer = (C_BasePlayer*)ClientEntityList->GetClientEntity(EngineClient->GetLocalPlayer());
	*Globals::bSendpacket = true;

	if (localPlayer && localPlayer->IsAlive() && !Settings::currentlyInFreeCam && cmd->tick_count != 0)
	{

		Globals::lastRealCmd = *cmd;
		DoMisc(cmd);
		if (cmd->tick_count != 0xFFFFF)
		{

			if (Settings::Misc::autoStrafeStyle == 2)
				PrePredOptimizer(cmd);
			PrePredEdgeJump(cmd);
			StartPrediction(cmd);
			BackupCMD(cmd, false);
			if (Settings::Misc::autoStrafeStyle == 2)
				PostPredOptimizer(cmd);
			PostPredEdgeJump(cmd);

			int flags = localPlayer->getFlags();

			C_BaseCombatWeapon* currWeapon = localPlayer->GetActiveWeapon();

			bool inCombat = false;
			if (currWeapon && !currWeapon->UsesLua() && Settings::Misc::edgeJump) // if edgejump is enabled, prediction is, and basically that only works with pred
			{
				if ((cmd->buttons & IN_ATTACK) &&
					(currWeapon->NextPrimaryAttack() <= GlobalVars->curtime) &&
					(currWeapon->PrimaryAmmoCount() > 0))
					inCombat = true;
				else inCombat = false;
			}
			else inCombat = (cmd->buttons & IN_ATTACK);


			if (Settings::AntiAim::enableAntiAim && !inCombat) {
				bool antiAimKeyDown;
				getKeyState(Settings::AntiAim::antiAimKey, Settings::AntiAim::antiAimKeyStyle, &antiAimKeyDown, henlo1, henlo2, henlo3);
				if (antiAimKeyDown)
				{
					AntiAimPitch(cmd, Settings::AntiAim::currentAntiAimPitch);
					AntiAimYaw(cmd, Settings::AntiAim::currentAntiAimYaw);
					if (!Globals::Untrusted)
						cmd->viewangles.FixAngles();
				}
			}

			DoLegitAimbot(cmd);

			TriggerBot(cmd);
			GunHacks(cmd, currWeapon);

			if (currWeapon && currWeapon->SecondaryAmmoCount() > 0 && currWeapon->PrimaryAmmoCount() == 0)
			{
				cmd->buttons |= IN_RELOAD;
				cmd->buttons &= ~(IN_ATTACK | IN_ATTACK2);
			}
			EndPrediction(cmd);
			BackupCMD(cmd, true);
		}
	}
	if (Settings::currentlyInFreeCam)
	{
		cmd->buttons = NULL;
		cmd->forwardmove = cmd->sidemove = cmd->upmove = 0.f;
		cmd->viewangles = Globals::lastRealCmd.viewangles;
	}
	auto thisCmd = *cmd;
	oCreateMove(ClientMode, flInputSampleTime, cmd);
	if (Settings::Misc::fakeLag)
	{
		static int m_nChokedPackets = 0;
		bool fakeLagKeyDown = false;
		getKeyState(Settings::Misc::fakeLagKey, Settings::Misc::fakeLagKeyStyle, &fakeLagKeyDown, henlo1, henlo2, henlo3);
		if (fakeLagKeyDown)
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
	if (*Globals::bSendpacket && cmd->tick_count != 0)
	{
		Globals::lastNetworkedCmd = thisCmd;
	}
	Globals::lastEndCmd = *cmd;
	return false;
}