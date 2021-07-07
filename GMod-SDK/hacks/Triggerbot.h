#pragma once

#include "../globals.h"
#include "Utils.h"
#include "AutoWall.h"

void TriggerBot(CUserCmd* cmd)
{
	if (!Settings::Triggerbot::triggerBot)return;
	QAngle viewAng;
	viewAng.z = 0;
	EngineClient->GetViewAngles(viewAng);
	trace_t Trace;
	CTraceFilter filter;
	filter.pSkip = localPlayer;
	Ray_t Ray;

	Ray.Init(localPlayer->EyePosition(), ((cmd->viewangles + localPlayer->GetViewPunch()).toVector() * 16384.f));
	EngineTrace->TraceRay(Ray, MASK_SHOT, &filter, &Trace);

	C_BasePlayer* target = (C_BasePlayer*)Trace.m_pEnt;
	if (!target || !target->IsPlayer() || !target->IsAlive())
		return;

	if (!Settings::Aimbot::aimAtTeammates && target->InLocalTeam())
		return;
	
	if ((Settings::Triggerbot::triggerBotHead && Trace.hitgroup == HITGROUP_HEAD) || (Settings::Triggerbot::triggerBotChest && Trace.hitgroup == HITGROUP_CHEST) || (Settings::Triggerbot::triggerBotStomach && Trace.hitgroup == HITGROUP_STOMACH))
	{
		static bool toggle = false;
		toggle = !toggle;

		if (Settings::Triggerbot::triggerbotFastShoot)
		{
			if(toggle || Settings::Triggerbot::triggerbotFastShoot)
			cmd->buttons |= IN_ATTACK;
			else cmd->buttons &= ~IN_ATTACK;
		}
		else cmd->buttons |= IN_ATTACK;
	}
}