#pragma once

#include "globals.h"
#include "Utils.h"

void GunHacks(C_BaseCombatWeapon* _this) {
	if (!_this || !_this->UsesLua())
		return;

	CLuaInterface* Lua = LuaShared->GetLuaInterface(0);
	
	_this->PushEntity();

	/* Basically what this does is:
	* Get the gun's base name.
	* If it is M9K, or CW, or FAS, modify it's exact fields.
	* If it is another base, just apply every other base's fields to it too.
	* Universal norecoil :-)
	*/
	if (!strcmp(GetLuaEntBase(_this), "bobs_gun_base")) // if the gun's base == m9k
	{
		Lua->GetField(-1, "Primary");
		if (Lua->IsType(-1, LuaObjectType::TABLE)) // if SWEP.Primary is a table
		{
			Lua->PushNumber(0);
			Lua->SetField(-2, "IronAccuracy"); // SWEP.Primary.IronAccuracy = 0
			if (Settings::Misc::noSpread)
			{
				Lua->PushNumber(0);
				Lua->SetField(-2, "Spread"); // SWEP.Primary.Spread = 0
			}
			if (Settings::Misc::noRecoil)
			{
				Lua->PushNumber(0);
				Lua->SetField(-2, "KickHorizontal"); // SWEP.Primary.KickHorizontal = 0
				Lua->PushNumber(0);
				Lua->SetField(-2, "KickUp"); // SWEP.Primary.KickUp = 0
				Lua->PushNumber(0);
				Lua->SetField(-2, "KickDown"); // SWEP.Primary.KickDown = 0
			}
			Lua->Pop(2);
			return;
		}
		else Lua->Pop(2);
	}	
	else if (!strcmp(GetLuaEntBase(_this), "cw_base")) // if the gun's base == cw2
	{
		if (Settings::Misc::noSpread)
		{
			Lua->PushNumber(0);
			Lua->SetField(-2, "HipSpread"); // SWEP.HipSpread = 0
			Lua->PushNumber(0);
			Lua->SetField(-2, "AimSpread"); // SWEP.AimSpread = 0
			Lua->PushNumber(0);
			Lua->SetField(-2, "SpreadPerShot"); // SWEP.SpreadPerShot = 0
			Lua->PushBool(true);
			Lua->SetField(-2, "NoFreeAim"); // <-- That is the secret :)
		}
		if (Settings::Misc::noRecoil)
		{
			Lua->PushNumber(0);
			Lua->SetField(-2, "Recoil");
		}
		Lua->Pop(1);
		return;
	}
	else if (!strcmp(GetLuaEntBase(_this), "fas2_base")) // if the gun's base == fas2
	{
		if (Settings::Misc::noSpread)
		{
			Lua->PushNumber(0);
			Lua->SetField(-2, "HipCone"); // SWEP.HipCone = 0
			Lua->PushNumber(0);
			Lua->SetField(-2, "AimCone"); // SWEP.AimCone = 0
			Lua->PushNumber(0);
			Lua->SetField(-2, "SpreadPerShot"); // SWEP.SpreadPerShot = 0
			Lua->PushNumber(0);
			Lua->SetField(-2, "MaxSpreadInc"); // SWEP.MaxSpreadInc = 0
		}
		if (Settings::Misc::noRecoil)
		{
			Lua->PushNumber(0);
			Lua->SetField(-2, "Recoil"); // SWEP.Recoil = 0
			Lua->PushNumber(0);
			Lua->SetField(-2, "ViewKick"); // SWEP.ViewKick = 0
		}
		Lua->Pop(1);
		return;
	}
	else {
		int topop = 2;
		Lua->GetField(-1, "Primary");
		if (!Lua->IsType(-1, LuaObjectType::TABLE))
		{
			topop = 1;
			Lua->Pop(1);
		}
		if (Settings::Misc::noSpread)
		{
			Lua->PushNumber(0);
			Lua->SetField(-2, "IronAccuracy");
			Lua->PushNumber(0);
			Lua->SetField(-2, "Cone");
			Lua->PushNumber(0);
			Lua->SetField(-2, "HipCone");
			Lua->PushNumber(0);
			Lua->SetField(-2, "AimCone");
			Lua->PushNumber(0);
			Lua->SetField(-2, "SpreadPerShot");
			Lua->PushNumber(0);
			Lua->SetField(-2, "MaxSpreadInc");
			Lua->PushNumber(0);
			Lua->SetField(-2, "HipCone");
			Lua->PushNumber(0);
			Lua->SetField(-2, "Spread");
		}
		if (Settings::Misc::noRecoil)
		{
			Lua->PushNumber(0);
			Lua->SetField(-2, "Recoil");
			Lua->PushNumber(0);
			Lua->SetField(-2, "ViewKick");
			Lua->PushNumber(0);
			Lua->SetField(-2, "KickHorizontal");
			Lua->PushNumber(0);
			Lua->SetField(-2, "KickUp");
			Lua->PushNumber(0);
			Lua->SetField(-2, "KickDown");
		}
		Lua->Pop(topop);
		return;
	}
}