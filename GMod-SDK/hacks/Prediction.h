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
	*Globals::predictionRandomSeed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;
	//*Globals::predictionRandomSeed = cmd->random_seed;

	m_flOldCurtime = GlobalVars->curtime;
	m_flOldFrametime = GlobalVars->frametime;

	GlobalVars->curtime = localPlayer->getTickBase() * GlobalVars->interval_per_tick;
	GlobalVars->frametime = GlobalVars->interval_per_tick;


	memset((void*)&moveData, 0, sizeof(moveData));
	GameMovement->StartTrackPredictionErrors(localPlayer);

	Prediction->SetupMove(localPlayer, cmd, nullptr, &moveData);
	GameMovement->ProcessMovement(localPlayer, &moveData);
	Prediction->FinishMove(localPlayer, cmd, &moveData);
	//CMoveData
	
}
void EndPrediction(CUserCmd* cmd)
{
	GlobalVars->curtime = m_flOldCurtime;
	GlobalVars->frametime = m_flOldFrametime;

	GameMovement->FinishTrackPredictionErrors(localPlayer);
	*Globals::predictionRandomSeed = -1;
};