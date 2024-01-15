#pragma once

#include "../globals.hpp"
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

		// WTF IS THIS IF ELSE SHIT LMAO? instead do a runtime/compiletime string hashing switch case
		if (!strcmp(GetLuaEntBase(gun), "tfa_gun_base"))
		{
			--topop;
			Lua->GetField(-1, "CalculateConeRecoil");
			Lua->Push(-2);
			Lua->Call(1, 1);

			spread = Lua->GetNumber(-1);
		}
		// god that's annoying, i got it to work a few minutes ago, did some code cleaning, and suddenly it stopped working... even the backups...
		else if (!strcmp(GetLuaEntBase(gun), "fas2_base"))
		{
			Lua->GetField(-1, "MaxSpreadInc");
			double curCone = 0.09f + Lua->GetNumber(-1);
			Lua->Pop(2);
			// 	self.CurCone = math.Clamp(cone + self.AddSpread * (self.dt.Bipod and 0.5 or 1) + (vel / 10000 * self.VelocitySensitivity) * (self.dt.Status == FAS_STAT_ADS and 0.25 or 1) + self.Owner.ViewAff, 0, 0.09 + self.MaxSpreadInc)

			QAngle spreadAng;

			LuaMathSetSeed(LuaCurTime());
			spreadAng.x = LuaMathRand(-curCone, curCone);
			spreadAng.y = LuaMathRand(-curCone, curCone);
			spreadAng.z = 0;

			cmd->viewangles -= (spreadAng * 25.f);
			cmd->viewangles -= localPlayer->GetViewPunch();

			// Basically, reversing the previous usercmd's angles will simply max out the Recoil
			if (cmd->command_number)
			{
				CUserCmd* prevCmd = Input->GetUserCmd(cmd->command_number - 1);
				prevCmd->viewangles.x = -cmd->viewangles.x;
				prevCmd->viewangles.y = cmd->viewangles.y - 180.f;
				prevCmd->viewangles.FixAngles();

				Input->m_pVerifiedCommands[prevCmd->command_number % 90].m_cmd = *prevCmd;
				Input->m_pVerifiedCommands[prevCmd->command_number % 90].m_crc = prevCmd->GetChecksum();
			}
			// 		Dir = (self.Owner:EyeAngles() + self.Owner:GetViewPunchAngles() + Angle(math.Rand(-cone, cone), math.Rand(-cone, cone), 0) * 25):Forward()

			return;
			/* This is wip.
			* This is almost identical to CW2's spread.
			*
			* Source spread isn't being used at all, because before it calls FireBullets, it sets bul.Spread to 0
			*/

		}
		else if (!strcmp(GetLuaEntBase(gun), "cw_base"))
		{
			Lua->GetField(-1, "MaxSpreadInc");
			double curCone = 0.09f + Lua->GetNumber(-1);
			Lua->Pop(2);
			// 	self.CurCone = math.Clamp(cone + self.AddSpread * (self.dt.Bipod and 0.5 or 1) + (vel / 10000 * self.VelocitySensitivity) * (self.dt.Status == FAS_STAT_ADS and 0.25 or 1) + self.Owner.ViewAff, 0, 0.09 + self.MaxSpreadInc)

			//if self.Owner:Crouching() then cone = cone * 0.85 end
			if (cmd->buttons & IN_DUCK)
				curCone *= 0.85f;

			// 	math.randomseed(commandNumber)
			QAngle spreadAng;
			LuaMathSetSeed((double)cmd->command_number);
			spreadAng.x = LuaMathRand(-curCone, curCone);
			spreadAng.y = LuaMathRand(-curCone, curCone);
			spreadAng.z = 0;

			cmd->viewangles -= (spreadAng * 25.f);
			cmd->viewangles -= localPlayer->GetViewPunch();

			// Basically, reversing the previous usercmd's angles will simply max out the Recoil
			if (cmd->command_number)
			{
				CUserCmd* prevcmd = cmd;
				for (int i = 0; i < 3; i++)
				{
					CUserCmd* cmd = Input->GetUserCmd(prevcmd->command_number - 1);
					cmd->viewangles.y = prevcmd->viewangles.y - 180.f;
					cmd->viewangles.x = -prevcmd->viewangles.x;
					cmd->viewangles.FixAngles();

					Input->m_pVerifiedCommands[cmd->command_number % 90].m_cmd = *cmd;
					Input->m_pVerifiedCommands[cmd->command_number % 90].m_crc = cmd->GetChecksum();

					prevcmd = cmd;
				}
			}
			// 		Dir = (self.Owner:EyeAngles() + self.Owner:GetViewPunchAngles() + Angle(math.Rand(-cone, cone), math.Rand(-cone, cone), 0) * 25):Forward()

			return;
			/* This is wip.
			* This is almost identical to FAS2's spread.
			*
			* Source spread isn't being used at all, because before it calls FireBullets, it sets bul.Spread to 0
			*/

		}
		else {

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
			else {
				Lua->Pop(1);
				Lua->GetField(-1, "Cone");
				if (Lua->IsType(-1, LuaObjectType::NUMBER))
				{
					spread = Lua->GetNumber(-1);
				}
			}
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
	if (!_this || !Lua)
		return;
	if(Settings::Misc::noSpread)
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
	else if (!strcmp(GetLuaEntBase(_this), "tfa_gun_base"))
	{
		if (Settings::Misc::noRecoil)
		{
			/*Lua->PushNumber(0);
			Lua->SetField(-2, "Recoil"); // SWEP.Recoil = 0
			Lua->PushNumber(0);
			Lua->SetField(-2, "ViewKick"); // SWEP.ViewKick = 0*/
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
