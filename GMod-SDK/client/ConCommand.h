#pragma once

// Auto reconstructed from vtable block @ 0x00082BCC
// from "lua_shared.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class ConCommand
{
public:

	/*1*/	virtual void* destr() = 0;
	/*2*/	virtual bool IsCommand(void)const = 0;
	/*3*/	virtual bool IsFlagSet(int)const = 0;
	/*4*/	virtual void* AddFlags(int) = 0;
	/*5*/	virtual void* GetName(void)const = 0;
	/*6*/	virtual void* GetHelpText(void)const = 0;
	/*7*/	virtual bool IsRegistered(void)const = 0;
	/*8*/	virtual void* GetDLLIdentifier(void)const = 0;
	/*9*/	virtual void* CreateBase(char const*, char const*, int) = 0;
	/*10*/	virtual void* Init(void) = 0;
	/*11*/	virtual void* AutoCompleteSuggest(char const*, void *) = 0;
	/*12*/	virtual void* CanAutoComplete(void) = 0;
	/*13*/	virtual void* Dispatch(void const*) = 0;
};