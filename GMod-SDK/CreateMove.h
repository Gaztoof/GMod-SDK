#pragma once

#include "globals.h"
#include "usercmd.h"
#include "ClientModeShared.h"
#include "Vector.h"

typedef bool(__thiscall* _CreateMove)(ClientModeShared*, float, CUserCmd*);
_CreateMove oCreateMove;

bool __fastcall hkCreateMove(ClientModeShared* ClientMode, void*, float flInputSampleTime, CUserCmd* cmd)
{
	uintptr_t stackTop;
	_asm mov stackTop, ebp;
	bool& bSendpacket = *(***(bool****)(stackTop)-1);

	localPlayer = (C_BasePlayer*)ClientEntityList->GetClientEntity(EngineClient->GetLocalPlayer());

	if (localPlayer && localPlayer->IsAlive())
	{
		int flags = localPlayer->getFlags();

		C_BaseCombatWeapon *currWeapon = localPlayer->GetActiveWeapon();
		currWeapon && currWeapon->nextPrimaryAttack() <= GlobalVars->curtime && currWeapon->PrimaryAmmoCount() > 0;
		//if ((cmd->buttons & IN_ATTACK) && (currWeapon && currWeapon->nextPrimaryAttack() <= GlobalVars->curtime) && (currWeapon->PrimaryAmmoCount() > 0))
				
		
		if (InputSystem->IsButtonDown(MOUSE_4)) {
			static bool toggle = false;
			QAngle viewAngles = EngineClient->getViewAngles();
			
			if (toggle)
			{
				toggle = false;
			}
			else toggle = true;


			// i planned on implementing an antiaim

			EngineClient->SetViewAngles(viewAngles);
		}
		if (InputSystem->IsButtonDown(KEY_SPACE)) {
			if (!(flags & FL_ONGROUND))
				cmd->buttons &= ~IN_JUMP;
			else
				cmd->buttons |= IN_JUMP;

			/*if (!(flags & FL_ONGROUND)) {
				if (cmd->mousedx < 0)
					cmd->sidemove = -450.0f;
				else if (cmd->mousedx > 0)
					cmd->sidemove = 450.0f;
			}*/


		}

		
		// implement localplayer->movetype() and make sure it's not ladder or noclip before bhopping

		if (currWeapon && currWeapon->SecondaryAmmoCount() > 0 && currWeapon->PrimaryAmmoCount() == 0)
		{
			cmd->buttons |= IN_RELOAD;
			cmd->buttons &= ~(IN_ATTACK | IN_ATTACK2);
		}
	}
	return oCreateMove(ClientMode, flInputSampleTime, cmd);
}