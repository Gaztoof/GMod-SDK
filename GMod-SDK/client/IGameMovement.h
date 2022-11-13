#pragma once
#include "../tier0/Vector.h"

class CBasePlayer;

class CMoveData {
public:
	int padd; //0x0000
	uintptr_t m_nPlayerHandle; //0x0004
	int m_nImpulseCommand; //0x0008
	QAngle m_vecViewAngles; //0x000C
	QAngle m_vecAbsViewAngles; //0x0018
	int m_nButtons; //0x0024
	int m_nOldButtons; //0x0028
	float m_flForwardMove; //0x002C
	float m_flSideMove; //0x0030
	float m_flUpMove; //0x0034
	float m_flMaxSpeed; //0x0038
	float m_flClientMaxSpeed; //0x003C
	Vector m_vecVelocity; //0x0040
	QAngle m_vecAngles; //0x004C
	QAngle m_vecOldAngles; //0x0058
	float m_outStepHeight; //0x0064
	Vector m_outWishVel; //0x0068
	Vector m_outJumpVel; //0x0074
	Vector m_vecConstraintCenter; //0x0080
	float m_flConstraintRadius; //0x008C
	float m_flConstraintWidth; //0x0090
	float m_flConstraintSpeedFactor; //0x0094
	Vector m_vecAbsOrigin; //0x0098
	//char pad_0001[8]; //0x00A0
};

class CGameMovement
{
public:
	virtual			~CGameMovement(void) {}

	// Process the current movement command
	virtual void	ProcessMovement(C_BasePlayer* pPlayer, CMoveData * pMove) = 0;
	virtual void	StartTrackPredictionErrors(C_BasePlayer* pPlayer) = 0;
	virtual void	FinishTrackPredictionErrors(C_BasePlayer* pPlayer) = 0;
	virtual void	DiffPrint(char const* fmt, ...) = 0;

	// Allows other parts of the engine to find out the normal and ducked player bbox sizes
	virtual Vector	GetPlayerMins(bool ducked) const = 0;
	virtual Vector	GetPlayerMaxs(bool ducked) const = 0;
	virtual Vector  GetPlayerViewOffset(bool ducked) const = 0;
	virtual void	TracePlayerBBox(const Vector& start, const Vector& end, unsigned int fMask, int collisionGroup, trace_t& pm);
	virtual void	TryTouchGround(const Vector& start, const Vector& end, const Vector& mins, const Vector& maxs, unsigned int fMask, int collisionGroup, trace_t& pm);


	CMoveData* mv;
	int				m_nOldWaterLevel;
	float			m_flWaterEntryTime;
	int				m_nOnLadder;
	Vector			m_vecForward;
	Vector			m_vecRight;
	Vector			m_vecUp;

	// Does most of the player movement logic.
// Returns with origin, angles, and velocity modified in place.
// were contacted during the move.
	virtual void	UNK0(void);
	virtual void	UNK1(void);
	virtual void	UNK2(void);
	virtual void	PlayerMove(void);
	virtual float	CalcRoll(const QAngle& angles, const Vector& velocity, float rollangle, float rollspeed);

	virtual	void	DecayPunchAngle(void);

	virtual void	CheckWaterJump(void);

	virtual void	WaterMove(void);

	virtual void	AirAccelerate(Vector& wishdir, float wishspeed, float accel);

	virtual void	AirMove(void);
	virtual float	GetAirSpeedCap(void) { return 30.f; }

	virtual bool	CanAccelerate();
	virtual void	Accelerate(Vector& wishdir, float wishspeed, float accel);

	// Only used by players.  Moves along the ground when player is a MOVETYPE_WALK.
	virtual void	WalkMove(void);

	// Handle MOVETYPE_WALK.
	virtual void	FullWalkMove();


};
