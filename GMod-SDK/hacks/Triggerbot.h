#pragma once

#include "../globals.hpp"
#include "Utils.h"
#include "AutoWall.h"

// That's bad, honestly needs a little improve
void TriggerBot(CUserCmd* cmd)
{
	if (!Settings::Triggerbot::triggerbot) return;

	QAngle viewAng;
	viewAng.z = 0;
	EngineClient->GetViewAngles(viewAng);
	trace_t trace;
	CTraceFilter filter;
	filter.pSkip = localPlayer;
	Ray_t ray;

	ray.Init(localPlayer->EyePosition(), localPlayer->EyePosition() + cmd->viewangles.toVector() * 69696.f);
	EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);

	C_BasePlayer* entity = (C_BasePlayer*)trace.m_pEnt;

	if (!entity || !entity->IsAlive() || !entity->IsPlayer() || entity == localPlayer || entity->IsDormant())
		return;

	if (!Settings::Aimbot::aimAtTeammates && entity->InLocalTeam())
		return;
	
	if ((Settings::Triggerbot::triggerbotHead && trace.hitgroup == HITGROUP_HEAD) || (Settings::Triggerbot::triggerbotChest == 1 && trace.hitgroup == HITGROUP_CHEST) || (Settings::Triggerbot::triggerbotStomach == 2 && trace.hitgroup == HITGROUP_STOMACH))
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
