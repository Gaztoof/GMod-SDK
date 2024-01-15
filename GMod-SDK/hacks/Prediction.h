#pragma once

#include "../globals.hpp"
#include "../client/usercmd.h"
#include "Utils.h"
#include "../tier1/checksum_md5.h"
#include "../client/IGameMovement.h"
float m_flOldCurtime;
float m_flOldFrametime;
CMoveData moveData;

void StartPrediction(CUserCmd* cmd)
{
	if (!Settings::Misc::edgeJump || false) return; // Temporarily making prediction "disabled" cause far from being perfect...
	*Globals::predictionRandomSeed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;
	//*Globals::predictionRandomSeed = cmd->random_seed;

	m_flOldCurtime = GlobalVars->curtime;
	m_flOldFrametime = GlobalVars->frametime;

	GlobalVars->curtime = localPlayer->getTickBase() * GlobalVars->interval_per_tick;
	GlobalVars->frametime = GlobalVars->interval_per_tick;

	//localPlayer->PreThink();
	//localPlayer->Think();

	GameMovement->StartTrackPredictionErrors(localPlayer);
	memset((void*)&moveData, 0, sizeof(moveData));

	if (cmd->weaponselect; auto wp=(C_BaseCombatWeapon*)ClientEntityList->GetClientEntity(cmd->weaponselect))
	{
		localPlayer->SelectItem(wp->GetName(), cmd->weaponsubtype);
	}
	Prediction->SetupMove(localPlayer, cmd, MoveHelper, &moveData);
	GameMovement->ProcessMovement(localPlayer, &moveData);
	//GameMovement->FullWalkMove();
	Prediction->FinishMove(localPlayer, cmd, &moveData);	
}
void EndPrediction(CUserCmd* cmd)
{
	if (!Settings::Misc::edgeJump || false) return; // Temporarily making prediction "disabled" cause far from being perfect...
	//localPlayer->PostThink();
	GlobalVars->curtime = m_flOldCurtime;
	GlobalVars->frametime = m_flOldFrametime;

	GameMovement->FinishTrackPredictionErrors(localPlayer);
	*Globals::predictionRandomSeed = -1;
};