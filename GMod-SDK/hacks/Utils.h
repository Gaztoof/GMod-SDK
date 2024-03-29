#pragma once
#include "../mathlib/math_pfns.h"
#include "../tier0/Color.h"
#include "../globals.hpp"
#include "../engine/vmatrix.h"
#include "../tier0/Vector.h"
#include "../client/C_BaseCombatWeapon.h"

/*bool WorldToScreen(Vector in, Vector& out)
{
	return !IVDebugOverlay->ScreenPosition(in, out);
}*/
bool WorldToScreen(Vector in, Vector& out)
{
	auto matrix = Globals::viewMatr.load().m;

	float w = matrix[3][0] * in.x + matrix[3][1] * in.y + matrix[3][2] * in.z + matrix[3][3];
	if (w > 0.001f)
	{
		float fl1DBw = 1 / w;
		out.x = (Globals::screenWidth / 2) + (0.5f * ((matrix[0][0] * in.x + matrix[0][1] * in.y + matrix[0][2] * in.z + matrix[0][3]) * fl1DBw) * Globals::screenWidth + 0.5f);
		out.y = (Globals::screenHeight / 2) - (0.5f * ((matrix[1][0] * in.x + matrix[1][1] * in.y + matrix[1][2] * in.z + matrix[1][3]) * fl1DBw) * Globals::screenHeight + 0.5f);
		return true;
	}
	return false;
}

const char* GetLuaEntBase(C_BaseCombatWeapon* _this)
{
	if (!Lua || !_this->UsesLua())
		return "";
	_this->PushEntity();
	Lua->GetField(-1, "Base");
	const char* out = "";
	if (Lua->IsType(-1, LuaObjectType::STRING))
		out = Lua->GetString(-1, NULL);
	Lua->Pop(2);
	return out;
}

double GetLuaWeaponDamage(C_BaseCombatWeapon* _this)
{
	if (!Lua || !_this->UsesLua())
		return 0.f;
	double damage = 1.f;
	int topop = 3;
	_this->PushEntity();
	Lua->GetField(-1, "Primary");
	if (!Lua->IsType(-1, LuaObjectType::TABLE))
	{
		--topop;
		Lua->Pop(1);
	}
	Lua->GetField(-1, "Damage");
	if (Lua->IsType(-1, LuaObjectType::NUMBER))
	{
		damage = Lua->GetNumber(-1);
	}
	Lua->Pop(topop);

	return damage;
}

const char* GetLuaEntName(C_BaseCombatWeapon* _this)
{
	if (!Lua || !_this->UsesLua())
		return "";
	_this->PushEntity();
	Lua->GetField(-1, "PrintName");
	const char* out = "";
	if (Lua->IsType(-1, LuaObjectType::STRING))
		out = Lua->GetString(-1, NULL);
	Lua->Pop(2);
	return out;
}

ButtonCode_t VKToButtonCode(int input)
{
	return InputSystem->VirtualKeyToButtonCode(input);
};

#define getKeyState(key, style, out)\
{\
	static bool toggleState = false; \
	static bool lastButtonState = false;\
	bool tempButtonState = false;\
		\
	switch (style)\
	{\
		case 0:\
			*out = true;\
			break;\
		case 1:\
			*out = InputSystem->IsButtonDown(key) && !MatSystemSurface->IsCursorVisible();\
			break;\
		case 2:\
			tempButtonState = InputSystem->IsButtonDown(key) && !MatSystemSurface->IsCursorVisible();\
			if (tempButtonState != lastButtonState && tempButtonState)\
				toggleState = !toggleState;\
			lastButtonState = tempButtonState;\
			*out = toggleState;\
				break;\
		case 3:\
			*out = false;\
			break;\
	}\
}

const char* IntToBoneName(int input)
{
	// https://wiki.facepunch.com/gmod/Entity:GetBoneName
	switch (Settings::Aimbot::aimbotHitbox)
	{
	case 0:
		return "ValveBiped.Bip01_Head1";
	case 1:
		return "ValveBiped.Bip01_Spine2"; // chest
	case 2:
		return "ValveBiped.Bip01_Pelvis"; // stomach
	}
	return "";
}
std::wstring StringToWString(std::string input)
{
	return std::wstring(input.begin(), input.end()); 
}

mstudiobone_t* Studio_BoneIndexByName(studiohdr_t* pStudioHdr, char const* pName, int* outIndex = NULL)
{
	int start = 0, end = pStudioHdr->numbones - 1;
	const BYTE* pBoneTable = pStudioHdr->GetBoneTableSortedByName();
	mstudiobone_t* pbones = pStudioHdr->pBone(0);

	while (start <= end)
	{
		int mid = (start + end) >> 1;
		const char* boneName = pbones[pBoneTable[mid]].pszName();
		int cmp = strcmp(boneName, pName);

		if (cmp < 0)
		{
			start = mid + 1;
		}
		else if (cmp > 0)
		{
			end = mid - 1;
		}
		else
		{
			if(outIndex != NULL)
				*outIndex = pBoneTable[mid];

			return pStudioHdr->pBone(pBoneTable[mid]);
		}
	}
	return nullptr;
}


int GetUserId(int entListIndex) 
{
	player_info_s info;
	EngineClient->GetPlayerInfo(entListIndex, &info);
	return info.userID;
}
const char* GetSteamID(int entListIndex)
{
	player_info_s info;
	EngineClient->GetPlayerInfo(entListIndex, &info);
	return info.guid;
}

#include "../Memory.h"

const char* GetClassName(C_BasePlayer* _this)
{
	// I had to pattern this as the game simply decided not to put it in C_BasePlayer.
	const char* out = "";
	static _GetClassName getClassName = (_GetClassName)(GetRealFromRelative((char*)findPattern("client", GetClassNamePattern, "GetClassName"), 1, 5, true));

	return getClassName(_this);

}

double LuaMathRand(double min, double max){
	if (!Lua) return 0.;
	Lua->PushSpecial(0); // SPECIAL_GLOB
	Lua->GetField(-1, "math");
	Lua->GetField(-1, "Rand");
	Lua->PushNumber(min);
	Lua->PushNumber(max);
	Lua->Call(2, 1);
	double retVal = (double)Lua->GetNumber(-1);
	Lua->Pop(3);
	return retVal;
}
void LuaMathSetSeed(double seed){
	if (!Lua) return;
	Lua->PushSpecial(0); // SPECIAL_GLOB
	Lua->GetField(-1, "math");
	Lua->GetField(-1, "randomseed");
	Lua->PushNumber(seed);
	Lua->Call(1, 0);
	Lua->Pop(2);
}
double LuaCurTime()
{
	if (!Lua) return 0.;
	Lua->PushSpecial(0); // SPECIAL_GLOB
	Lua->GetField(-1, "CurTime");
	Lua->Call(0, 1);
	double curTime = Lua->GetNumber(-1);
	Lua->Pop(2);
	return curTime;
}