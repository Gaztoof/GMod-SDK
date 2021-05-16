#pragma once
#include "math_pfns.h"
#include "Color.h"
#include "globals.h"
#include "vmatrix.h"
#include "Vector.h"
#include "C_BaseCombatWeapon.h"

#include <math.h>
Color rainbowColor(float speed) noexcept
{
        return Color(std::sin(speed * GlobalVars->realtime) * 0.5f + 0.5f,
        std::sin(speed * GlobalVars->realtime + 2 * PI / 3) * 0.5f + 0.5f,
        std::sin(speed * GlobalVars->realtime + 4 * PI / 3) * 0.5f + 0.5f);
}
bool WorldToScreen(Vector in, Vector& out)
{
	return !IVDebugOverlay->ScreenPosition(in, out);
}

const char* GetLuaEntBase(C_BaseCombatWeapon* _this)
{
	CLuaInterface* Lua = LuaShared->GetLuaInterface(0); // ent.Base
	if (!_this->UsesLua())
		return "";
	_this->PushEntity();
	Lua->GetField(-1, "Base");
	const char* out = "";
	if (Lua->IsType(-1, LuaObjectType::STRING))
		out = Lua->GetString(-1, NULL);
	Lua->Pop(2);
	return out;
}

const char* GetLuaEntName(C_BaseCombatWeapon* _this)
{
	CLuaInterface* Lua = LuaShared->GetLuaInterface(0); // ent.PrintName
	if (!_this->UsesLua())
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

#define getKeyState(key, style, out, hi, hi2, hi3)\
{\
	static bool hi = false; \
	static bool hi2 = false;\
	bool hi3 = false;\
		\
	switch (style)\
	{\
		case 0:\
			*out = true;\
			break;\
		case 1:\
			*out = InputSystem->IsButtonDown(key);\
			break;\
		case 2:\
			hi3 = InputSystem->IsButtonDown(key);\
			if (hi3 != hi2 && hi3)\
				hi = !hi;\
			hi2 = hi3;\
			*out = hi;\
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

typedef const char*(__thiscall* _GetClassName)(C_BasePlayer*);
#include "Memory.h"

const char* GetClassName(C_BasePlayer* _this)
{
	// I had to pattern this as the game simply decided not to put it in C_BasePlayer.
	const char* out = "";
#ifdef _WIN64
	static _GetClassName getClassName = (_GetClassName)(GetRealFromRelative((char*)findPattern("client", "\xE8????\x4D\x8B\x47\x10"),1));
#else
	static _GetClassName getClassName = (_GetClassName)(GetRealFromRelative((char*)findPattern("client", "\xE8????\x50\x8B\x43\x08"), 1));
#endif

	return getClassName(_this);

}
