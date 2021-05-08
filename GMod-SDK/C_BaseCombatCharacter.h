#pragma once

#include "c_basecombatweapon.h"
#include "IClientNetworkable.h"
#include "C_BaseFlex.h"

class C_BaseCombatCharacter : public C_BaseFlex
{
public:
	virtual void	OnPreDataChanged(DataUpdateType_t updateType);
	virtual void	OnDataChanged(DataUpdateType_t updateType);

	virtual bool	IsBaseCombatCharacter(void) { return true; };
	virtual C_BaseCombatCharacter* MyCombatCharacterPointer(void) { return this; }

	// -----------------------
	// Vision
	// -----------------------
	enum FieldOfViewCheckType { USE_FOV, DISREGARD_FOV };
	bool IsAbleToSee(const CBaseEntity* entity, FieldOfViewCheckType checkFOV);	// Visible starts with line of sight, and adds all the extra game checks like fog, smoke, camo...
	bool IsAbleToSee(C_BaseCombatCharacter* pBCC, FieldOfViewCheckType checkFOV);	// Visible starts with line of sight, and adds all the extra game checks like fog, smoke, camo...

	virtual bool IsLookingTowards(const CBaseEntity* target, float cosTolerance ) const;	// return true if our view direction is pointing at the given target, within the cosine of the angular tolerance. LINE OF SIGHT IS NOT CHECKED.
	virtual bool IsLookingTowards(const Vector& target, float cosTolerance) const;	// return true if our view direction is pointing at the given target, within the cosine of the angular tolerance. LINE OF SIGHT IS NOT CHECKED.

	virtual bool IsInFieldOfView(CBaseEntity* entity) const;	// Calls IsLookingAt with the current field of view.  
	virtual bool IsInFieldOfView(const Vector& pos) const;

	enum LineOfSightCheckType
	{
		IGNORE_NOTHING,
		IGNORE_ACTORS
	};
	virtual bool IsLineOfSightClear(CBaseEntity* entity, LineOfSightCheckType checkType = IGNORE_NOTHING) const;// strictly LOS check with no other considerations
	virtual bool IsLineOfSightClear(const Vector& pos, LineOfSightCheckType checkType = IGNORE_NOTHING, CBaseEntity* entityToIgnore = NULL) const;


	// -----------------------
	// Ammo
	// -----------------------
	void				RemoveAmmo(int iCount, int iAmmoIndex);
	void				RemoveAmmo(int iCount, const char* szName);
	void				RemoveAllAmmo();
	int					GetAmmoCount(int iAmmoIndex) const;
	int					GetAmmoCount(char* szName) const;

	C_BaseCombatWeapon* Weapon_OwnsThisType(const char* pszWeapon, int iSubType = 0) const;  // True if already owns a weapon of this class
	virtual	bool		Weapon_Switch(C_BaseCombatWeapon* pWeapon, int viewmodelindex = 0);
	virtual bool		Weapon_CanSwitchTo(C_BaseCombatWeapon* pWeapon);

	virtual C_BaseCombatWeapon* GetActiveWeapon(void) const;

	virtual int			BloodColor();
	virtual void		DoMuzzleFlash();


};
