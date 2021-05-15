#pragma once

#include "globals.h"
#include "Utils.h"

void GunHacks(C_BaseCombatWeapon* _this) {
	if (!_this || !_this->UsesLua())
		return;

	CLuaInterface* Lua = LuaShared->GetLuaInterface(0);
	
	_this->PushEntity();
	if (!strcmp(GetLuaEntBase(_this), "bobs_gun_base")) // m9k
	{
		Lua->GetField(-1, "Primary");
		if (Lua->IsType(-1, LuaObjectType::TABLE))
		{
			Lua->PushNumber(0);
			Lua->SetField(-2, "IronAccuracy");
			if (Settings::Misc::noSpread)
			{
				Lua->PushNumber(0);
				Lua->SetField(-2, "Spread");
			}
			if (Settings::Misc::noRecoil)
			{
				Lua->PushNumber(0);
				Lua->SetField(-2, "KickHorizontal");
				Lua->PushNumber(0);
				Lua->SetField(-2, "KickUp");
				Lua->PushNumber(0);
				Lua->SetField(-2, "KickDown");
			}
			Lua->Pop(2);
			return;
		}
		else Lua->Pop(2);
	}	
	else if (!strcmp(GetLuaEntBase(_this), "cw_base")) // cw2
	{
		if (Settings::Misc::noSpread)
		{
			Lua->PushNumber(0);
			Lua->SetField(-2, "HipSpread");
			Lua->PushNumber(0);
			Lua->SetField(-2, "AimSpread");
			Lua->PushNumber(0);
			Lua->SetField(-2, "SpreadPerShot");
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
	else if (!strcmp(GetLuaEntBase(_this), "fas2_base")) // fas2
	{
		if (Settings::Misc::noSpread)
		{
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
		}
		if (Settings::Misc::noRecoil)
		{
			Lua->PushNumber(0);
			Lua->SetField(-2, "Recoil");
			Lua->PushNumber(0);
			Lua->SetField(-2, "ViewKick");
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


	/*Lua->GetField(-1, "Cone");
	if (!Lua->IsType(-1, LuaObjectType::NUMBER))
	{
		Lua->Pop(3);
		return;
	}
	double out = Lua->GetNumber(-1);
	Lua->Pop(3);*/

}