#pragma once

#include "trace.h"
#include "gametrace.h"
#include "globals.h"

float ScaleDamage(int hitGroup)
{
	switch (hitGroup)
	{
	case HITGROUP_GENERIC:
		return 1.f;
	case HITGROUP_HEAD:
		return 4.f;
	case HITGROUP_CHEST:
		return 1.f;
	case HITGROUP_STOMACH:
		return 1.25f;
	case HITGROUP_LEFTARM:
		return 1.f;
	case HITGROUP_RIGHTARM:
		return 1.f;
	case HITGROUP_LEFTLEG:
		return 0.75f;
	case HITGROUP_RIGHTLEG:
		return 0.75f;
	case HITGROUP_GEAR:
		return 1.f;
	default:
		return 1.f;
		break;
	}
} // https://www.gamersdecide.com/articles/csgo-weapons-damage-chart

// This is WIP, i'm releasing to UC before I finish making it.
bool CanHit(C_BasePlayer* target, Vector from, Vector to)
{
	float gunDamage = 50.f;
	trace_t Trace;
	CTraceFilter filter;
	filter.pSkip = localPlayer;
	Ray_t Ray;

	Ray.Init(from, to);
	EngineTrace->TraceRay(Ray, MASK_SHOT, &filter, &Trace);
	//engineTrace->ClipRayToEntity(Ray, MASK_SHOT_HULL | CONTENTS_HITBOX, (IHandleEntity*)target, &Trace);
	//m_PhysicsSurface->surface_data( Trace.surface.surfaceProps) = surfacedata_t*, get game.penetrationmodifier inside it

	if (Trace.m_pEnt == target || Trace.fraction >= 0.98f)
	{
		gunDamage *= ScaleDamage(Trace.hitgroup);
		return true;
	}

	return false;
}
