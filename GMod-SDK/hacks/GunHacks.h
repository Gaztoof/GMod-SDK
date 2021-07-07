#pragma once

#include "../globals.h"
#include "Utils.h"
#include "../tier1/checksum_md5.h"

/*
* How does this works?
* Basically, it calculates the spread angles the exact same way as the server does, so the prediction is simply perfect.
* You set the seed the same way the server does, and do the calculation just like the server does.
* Result? Not a single bullet will deviate.
*/
void NoSpread(CUserCmd* cmd, C_BaseCombatWeapon* gun, CLuaInterface* Lua)
{
	if (!(cmd->buttons & IN_ATTACK) || gun->PrimaryAmmoCount() < 1)
		return;
	double spread = FLT_MAX;
	if (!gun->UsesLua())
	{
		Vector gunSpread = gun->GetBulletSpread();
		spread = (gunSpread.x + gunSpread.y + gunSpread.z)/3;
	}
	else if (Lua) {
		int topop = 3;
		gun->PushEntity();
		Lua->GetField(-1, "Primary");
		if (!Lua->IsType(-1, LuaObjectType::TABLE))
		{
			--topop;
			Lua->Pop(1);
		}
		Lua->GetField(-1, "Spread");
		if (Lua->IsType(-1, LuaObjectType::NUMBER))
		{
			spread = Lua->GetNumber(-1);
		}
		Lua->Pop(topop);
	}
	else return;
	if (spread == FLT_MAX)
		return;
	BYTE seed = MD5_PseudoRandom(cmd->command_number) & 0xFF;
	UniformRandomStream->SetSeed(seed);

	QAngle engineSpread(UniformRandomStream->RandomFloat(-0.5f, 0.5f) + UniformRandomStream->RandomFloat(-0.5f, 0.5f), UniformRandomStream->RandomFloat(-0.5f, 0.5f) + UniformRandomStream->RandomFloat(-0.5f, 0.5f), 0);

	// X will not be accounted, Z is the equivalent of Y, and Y the equivalent of X
	Vector ShootDirection = Vector(1.f,1.f,1.f);
	ShootDirection.y =  (spread * engineSpread.y);
	ShootDirection.z = -(spread * engineSpread.x);

	cmd->viewangles += ShootDirection.toAngle();
}

void GunHacks(CUserCmd* cmd, C_BaseCombatWeapon* _this) {
	if (!_this)
		return;
	CLuaInterface* Lua = LuaShared->GetLuaInterface(0);
	NoSpread(cmd, _this, Lua);
	if (!_this->UsesLua())
		return;

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
		if (Settings::Misc::noRecoil)
		{
			Lua->PushNumber(0);
			Lua->SetField(-2, "Recoil");
			Lua->PushBool(true);
			Lua->SetField(-2, "NoFreeAim"); // <-- That is the secret :)
		}
		Lua->Pop(1);
		return;
	}
	else if (!strcmp(GetLuaEntBase(_this), "fas2_base")) // if the gun's base == fas2
	{
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