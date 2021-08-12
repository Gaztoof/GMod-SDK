//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//

#ifndef ENGINE_IENGINETRACE_H
#define ENGINE_IENGINETRACE_H
#ifdef _WIN32
#pragma once
#endif

#include "../tier0/Vector.h"
#include "vmatrix.h"
#include "../mathlib/mathlib.h"

#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	0x80

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200	

// unused 
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
#define CONTENTS_UNUSED6		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions 
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

#define	SURF_LIGHT		0x0001		// value will hold the light strength
#define	SURF_SKY2D		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define	SURF_SKY		0x0004		// don't draw, but add to skybox
#define	SURF_WARP		0x0008		// turbulent water warp
#define	SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	// the surface can not have a portal placed on it
#define	SURF_TRIGGER	0x0040	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define	SURF_NODRAW		0x0080	// don't bother referencing the texture

#define	SURF_HINT		0x0100	// make a primary bsp splitter

#define	SURF_SKIP		0x0200	// completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT	0x0400	// Don't calculate light
#define SURF_BUMPLIGHT	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS	0x1000	// Don't receive shadows
#define SURF_NODECALS	0x2000	// Don't receive decals
#define SURF_NOCHOP		0x4000	// Don't subdivide patches on this surface 
#define SURF_HITBOX		0x8000	// surface is part of a hitbox

#define	MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// water physics in these contents
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

class Vector;
class IHandleEntity;
struct Ray_t {
public:
	VectorAligned m_start;
	VectorAligned m_delta;
	VectorAligned m_start_offset;
	VectorAligned m_extents;
	const matrix3x4_t* m_world_axis_transform;
	bool m_is_ray;
	bool m_is_swept;

	Ray_t() : m_world_axis_transform(nullptr), m_is_ray{ false }, m_is_swept{ false } { }

	Ray_t(Vector const& start, Vector const& end) {
		Init(start, end);
	}

	Ray_t(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs) {
		m_delta = end - start;

		m_world_axis_transform = nullptr;
		m_is_swept = m_delta.Length() != 0;

		m_extents = maxs - mins;
		m_extents *= 0.5f;
		m_is_ray = m_extents.LengthSqr() < 1e-6;

		m_start_offset = maxs + mins;
		m_start_offset *= 0.5f;
		m_start = start + m_start_offset;
		m_start_offset *= -1.0f;
	}

	void Init(Vector const& start, Vector const& end) {
		m_delta = end - start;

		m_is_swept = m_delta.LengthSqr() != 0;

		m_extents.Init(0.f, 0.f, 0.f);

		m_world_axis_transform = nullptr;
		m_is_ray = true;

		m_start_offset.Init(0.f, 0.f, 0.f);
		m_start = start;
	}

	void init(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs) {
		m_delta = end - start;

		m_world_axis_transform = nullptr;
		m_is_swept = m_delta.Length() != 0;

		m_extents = maxs - mins;
		m_extents *= 0.5f;
		m_is_ray = m_extents.LengthSqr() < 1e-6;

		m_start_offset = maxs + mins;
		m_start_offset *= 0.5f;
		m_start = start + m_start_offset;
		m_start_offset *= -1.0f;
	}
};
class CGameTrace;
typedef CGameTrace trace_t;
class ICollideable;
class QAngle;
class CTraceListData;
class CPhysCollide;

//-----------------------------------------------------------------------------
// The standard trace filter... NOTE: Most normal traces inherit from CTraceFilter!!!
//-----------------------------------------------------------------------------
enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

class ITraceFilter
{
public:
	virtual bool			ShouldHitEntity(void* pEntity, int mask) = 0;
	virtual TraceType_t            GetTraceType() const = 0;
};


//-----------------------------------------------------------------------------
// Classes are expected to inherit these + implement the ShouldHitEntity method
//-----------------------------------------------------------------------------

// This is the one most normal traces will inherit from
class CTraceFilter : public ITraceFilter
{
public:
	bool ShouldHitEntity(void* pEntityHandle, int contentsMask)
	{
		return pEntityHandle != pSkip;
	}
	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
	void* pSkip;
};
class CTraceFilterEntitiesOnly : public ITraceFilter
{
public:
	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_ENTITIES_ONLY;
	}
};


//-----------------------------------------------------------------------------
// Classes need not inherit from these
//-----------------------------------------------------------------------------
class CTraceFilterWorldOnly : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int contentsMask)
	{
		return false;
	}
	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_WORLD_ONLY;
	}
};

class CTraceFilterWorldAndPropsOnly : public ITraceFilter
{
public:
	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
};

class CTraceFilterHitAll : public CTraceFilter
{
public:
	virtual bool ShouldHitEntity(IHandleEntity* pServerEntity, int contentsMask)
	{
		return true;
	}
};


//-----------------------------------------------------------------------------
// Enumeration interface for EnumerateLinkEntities
//-----------------------------------------------------------------------------
class IEntityEnumerator
{
public:
	// This gets called with each handle
	virtual bool EnumEntity(IHandleEntity * pHandleEntity) = 0;
};


//-----------------------------------------------------------------------------
// Interface the engine exposes to the game DLL
//-----------------------------------------------------------------------------


class IEngineTrace
{
public:
	virtual int		GetPointContents(const Vector & vecAbsPosition, IHandleEntity * *ppEntity = NULL) = 0;
	virtual int		GetPointContents_Collideable(ICollideable* pCollide, const Vector& vecAbsPosition) = 0;
	virtual void	ClipRayToEntity(const Ray_t& ray, unsigned int fMask, IHandleEntity* pEnt, trace_t* pTrace) = 0;
	virtual void	ClipRayToCollideable(const Ray_t& ray, unsigned int fMask, ICollideable* pCollide, trace_t* pTrace) = 0;
	virtual void	TraceRay(const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;
	virtual void	SetupLeafAndEntityListRay(const Ray_t& ray, CTraceListData& traceData) = 0;
	virtual void    SetupLeafAndEntityListBox(const Vector& vecBoxMin, const Vector& vecBoxMax, CTraceListData& traceData) = 0;
	virtual void	TraceRayAgainstLeafAndEntityList(const Ray_t& ray, CTraceListData& traceData, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;
	virtual void	SweepCollideable(ICollideable* pCollide, const Vector& vecAbsStart, const Vector& vecAbsEnd, const QAngle& vecAngles, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;
	virtual void	EnumerateEntities(const Ray_t& ray, bool triggers, IEntityEnumerator* pEnumerator) = 0;
	virtual void	EnumerateEntities(const Vector& vecAbsMins, const Vector& vecAbsMaxs, IEntityEnumerator* pEnumerator) = 0;
	virtual ICollideable* GetCollideable(IHandleEntity* pEntity) = 0;
	virtual int GetStatByIndex(int index, bool bClear) = 0;
	virtual void GetBrushesInAABB(const Vector& vMins, const Vector& vMaxs, void* pOutput, int iContentsMask = 0xFFFFFFFF) = 0;
	virtual CPhysCollide* GetCollidableFromDisplacementsInAABB(const Vector& vMins, const Vector& vMaxs) = 0;
	virtual bool GetBrushInfo(int iBrush, void* pPlanesOut, int* pContentsOut) = 0;
	virtual bool PointOutsideWorld(const Vector& ptTest) = 0; //Tests a point to see if it's outside any playable area
	virtual int GetLeafContainingPoint(const Vector& ptTest) = 0;
};



#endif // ENGINE_IENGINETRACE_H