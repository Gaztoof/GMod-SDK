#pragma once
#include "Color.h"

// Auto reconstructed from vtable block @ 0x00082C0C
// from "lua_shared.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class ConVar
{
public:
	//Don't forget the constructor.
	/*0*/	virtual void* Destr() = 0;
	/*1*/	virtual void* Destr2() = 0;
	/*2*/	virtual bool IsCommand(void)const = 0;
	/*3*/	virtual bool IsFlagSet(int)const = 0;
	/*4*/	virtual void* AddFlags(int) = 0;

	/*5*/	virtual void* Unknown1(int) = 0;
	/*6*/	virtual void* Unknown2(int) = 0;

	/*7*/	virtual void* GetName(void)const = 0;
	/*8*/	virtual void* GetHelpText(void)const = 0;
	/*9*/	virtual bool IsRegistered(void)const = 0;
	/*10*/	virtual void* GetDLLIdentifier(void)const = 0;
	/*11*/	virtual void* CreateBase(char const*, char const*, int) = 0;
	/*11/	virtual void* Init(void) = 0;
	/*12*/	virtual void* SetValue(char const*) = 0;
	/*13*/	virtual void* SetValue(float) = 0;
	/*14*/	virtual void* SetValue(int) = 0;
	/*15*/	virtual void* InternalSetValue(char const*) = 0;
	/*16*/	virtual void* InternalSetFloatValue(float) = 0;
	/*17*/	virtual void* InternalSetIntValue(int) = 0;
	/*18*/	virtual int Unknown(int) = 0;
	/*19*/	virtual void* ClampValue(float&) = 0;
	/*20*/	virtual void* ChangeStringValue(char const*, float) = 0;
	/*21*/	virtual void* Create(char const*, char const*, int, char const*, bool, float, bool, float, void (*)(void*, char const*, float)) = 0;
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
	/*9*/	virtual void* Nothing5(void) = 0;

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