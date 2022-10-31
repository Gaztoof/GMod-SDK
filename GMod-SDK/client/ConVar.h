#pragma once
#include "../tier0/Color.h"

#define FCVAR_ARCHIVE 128
#define FCVAR_ARCHIVE_XBOX 16777216
#define FCVAR_CHEAT 16384
#define FCVAR_CLIENTCMD_CAN_EXECUTE 1073741824
#define FCVAR_CLIENTDLL 8
#define FCVAR_DEMO 65536
#define FCVAR_DONTRECORD 131072
#define FCVAR_GAMEDLL 4
#define FCVAR_LUA_CLIENT 262144
#define FCVAR_LUA_SERVER 524288
#define FCVAR_NEVER_AS_STRING 4096
#define FCVAR_NONE 0
#define FCVAR_NOTIFY 256
#define FCVAR_NOT_CONNECTED 4194304
#define FCVAR_PRINTABLEONLY 1024
#define FCVAR_PROTECTED 32
#define FCVAR_REPLICATED 8192
#define FCVAR_SERVER_CANNOT_QUERY 536870912
#define FCVAR_SERVER_CAN_EXECUTE 268435456
#define FCVAR_SPONLY 64
#define FCVAR_UNLOGGED 2048
#define FCVAR_UNREGISTERED 1
#define FCVAR_USERINFO 512

void dummyCallback(void* convar, const char* pOldValString) { return; }


// Auto reconstructed from vtable block @ 0x00082C0C
// from "lua_shared.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class ConVar
{
	// https://i.imgur.com/uisym0i.png
	// https://i.imgur.com/f2HoNEu.png
public:
	ConVar* pNextConvar; //0x0008
	uint32_t bRegistered; //0x0010
	char pad_0014[4]; //0x0014
	char *pszName; //0x0018
	char *pszHelpString; //0x0020
	uint32_t nflags; //0x0028
	char pad_002C[4]; //0x002C
	void *s_pConCommandBases; //0x0030
	ConVar *pParent; //0x0038
	char *pszDefaultValue; //0x0040
	char *pszValueStr; //0x0048
	uint32_t strLength; //0x0050
	float fVal; //0x0054
	int32_t intValue; //0x0058
	uint32_t bHasMin; //0x005C
	float fMinVal; //0x0060
	uint32_t bHasMax; //0x0064
	float fMaxVal; //0x0068
	char pad_006C[4]; //0x006C
	PVOID CALLBACKPTR; //0x0070


	/*0*/	virtual void* Destr() = 0;
	/*2*/	virtual bool IsCommand(void)const = 0;
	/*3*/	virtual bool IsFlagSet(int)const = 0;
	/*4*/	virtual void AddFlags(int) = 0;
	/*4*/	virtual void RemoveFlagsDoNotUse(int) = 0;

	/*4*/	virtual uint64_t GetFlagsDoNotUse() = 0;

	/*7*/	virtual const char* GetName(void)const = 0;
	/*8*/	virtual const char* GetHelpText(void)const = 0;
	/*9*/	virtual bool IsRegistered(void)const = 0;
	/*10*/	virtual void* GetDLLIdentifier(void)const = 0;
	/*11*/	virtual void CreateBase(char const*, char const*, int) = 0;
	/*11*/	virtual void Init(void) = 0;

	/*11*/	virtual void Unk1(void) = 0;
	/*11*/	virtual void Unk2(void) = 0;
	///*12*/	virtual void SetValue(char const*) = 0;
	///*13*/	virtual void SetValue(float) = 0;
	///*14*/	virtual void SetValue(int) = 0;
	/*15*/	virtual void InternalSetValue(char const*) = 0; // This doesn't works for me, for some reasons
	/*16*/	virtual void InternalSetValue(float) = 0;
	/*17*/	virtual void InternalSetValue(int) = 0;
	/*18*/	virtual void SetValue(int) = 0;
	/*19*/	virtual void* ClampValue(float&) = 0;
	/*20*/	virtual void* ChangeStringValue(char const*, float) = 0;
	/*21*/	virtual void* Create(char const* name, char const*defaultValue, int flags, char const*helperString, bool hasMin, float fMin, bool hasMax, float fMax, void *fnCallback) = 0;

public:
	void SetFlags(int flag) {
		nflags = flag;
	}
	void RemoveFlags(int flag) {
		nflags &= ~flag;
	}
	void DisableCallback() {
		if(this->CALLBACKPTR)
		*(PVOID*)(this->CALLBACKPTR) = dummyCallback;
	}
};

class CCvar
{
public:
	/*0*/	virtual void Connect(void* (*)(char const*, int*)) = 0;
	/*1*/	virtual void Disconnect(void) = 0;
	/*2*/	virtual void* QueryInterface(char const*) = 0;
	/*3*/	virtual void* Init(void) = 0;
	/*4*/	virtual void Shutdown(void) = 0;

	/*5*/	virtual void* Nothing1(void) = 0;
	/*6*/	virtual void* Nothing2(void) = 0;
	/*7*/	virtual void* Nothing3(void) = 0;
	/*8*/	virtual void* Nothing4(void) = 0;

	/*10*/	virtual void* AllocateDLLIdentifier(void) = 0;
	/*11*/	virtual void RegisterConCommand(void*) = 0;
	/*12*/	virtual void UnregisterConCommand(void*) = 0;
	/*13*/	virtual void UnregisterConCommands(int) = 0;
	/*14*/	virtual const char* GetCommandLineValue(char const*) = 0;
	/*15*/	virtual void* FindCommandBase(char const*) = 0;
	/*16*/	virtual const void* FindCommandBase(char const*)const = 0;
	/*17*/	virtual ConVar* FindVar(char const * var_name) = 0;
	/*18*/	virtual ConVar* FindVar(char const* var_name)const = 0;
	/*19*/	virtual void* FindCommand(char const*) = 0;
	/*20*/	virtual void* FindCommand(char const*)const = 0;

	/*21*/	virtual void InstallGlobalChangeCallback(void (*)(ConVar*, char const*, float)) = 0;
	/*22*/	virtual void RemoveGlobalChangeCallback(void (*)(ConVar*, char const*, float)) = 0;
	/*23*/	virtual void CallGlobalChangeCallbacks(ConVar*, char const*, float) = 0;
	/*24*/	virtual void InstallConsoleDisplayFunc(void*) = 0;
	/*25*/	virtual void RemoveConsoleDisplayFunc(void*) = 0;
	/*26*/	virtual void ConsoleColorPrintf(Color const&, char const*, ...)const = 0;
	/*27*/	virtual void ConsolePrintf(char const*, ...)const = 0;
	/*28*/	virtual void ConsoleDPrintf(char const*, ...)const = 0;
	/*29*/	virtual void RevertFlaggedConVars(int) = 0;
	/*30*/	virtual void InstallCVarQuery(void*) = 0;
	/*31*/	virtual bool IsMaterialThreadSetAllowed(void)const = 0;
	/*32*/	virtual void QueueMaterialThreadSetValue(ConVar*, char const*) = 0;
	/*33*/	virtual void QueueMaterialThreadSetValue(ConVar*, int) = 0;
	/*34*/	virtual void QueueMaterialThreadSetValue(ConVar*, float) = 0;
	/*35*/	virtual bool HasQueuedMaterialThreadConVarSets(void)const = 0;
	/*36*/	virtual void ProcessQueuedMaterialThreadConVarSets(void) = 0;
	/*37*/	virtual void FactoryInternalIterator(void) = 0;
};