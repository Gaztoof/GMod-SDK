//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef GAMETRACE_H
#define GAMETRACE_H
#ifdef _WIN32
#pragma once
#endif

#include "trace.h"
#include "../tier0/Vector.h"

#if defined( CLIENT_DLL )
class C_BaseEntity;
#else
class CBaseEntity;
#endif


//-----------------------------------------------------------------------------
// Purpose: A trace is returned when a box is swept through the world
// NOTE: eventually more of this class should be moved up into the base class!!
//-----------------------------------------------------------------------------
struct csurface_t
{
	const char* name;
	short		surfaceProps;
	unsigned short	flags;		// BUGBUG: These are declared per surface, not per material, but this database is per-material now
};
class CGameTrace : public CBaseTrace
{
public:
	float		fractionleftsolid;		// time we left a solid, only valid if we started in solid
	csurface_t	surface;				// surface hit (impact surface)

	int			hitgroup;				// 0 == generic, non-zero is specific body part
	short		physicsbone;			// physics bone hit by trace in studio

#if defined( CLIENT_DLL )
	C_BaseEntity* m_pEnt;
#else
	C_BasePlayer* m_pEnt;
#endif

	// NOTE: this member is overloaded.
	// If hEnt points at the world entity, then this is the static prop index.
	// Otherwise, this is the hitbox index.
	int			hitbox;					// box hit by trace in studio

	CGameTrace() {}

private:
	// No copy constructors allowed
	//CGameTrace(const CGameTrace& vOther);
};




typedef CGameTrace trace_t;

//=============================================================================

#define TLD_DEF_LEAF_MAX	256
#define TLD_DEF_ENTITY_MAX	1024


#endif // GAMETRACE_H
