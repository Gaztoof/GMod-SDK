#pragma once

// Auto reconstructed from vtable block @ 0x000823B8
// from "lua_shared.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class CLuaConVars
{
public:
	/*0*/	virtual void* Destr() = 0;
	/*2*/	virtual void* Init(void) = 0;
	/*3*/	virtual void* CreateConVar(char const*, char const*, char const*, int) = 0;
	/*4*/	virtual void* CreateConCommand(char const*, char const*, int, void (*)(void const*), int (*)(char const*, char(*)[128])) = 0;
	/*5*/	virtual void* DestroyManaged(void) = 0;
	/*6*/	virtual void* Cache(char const*, char const*) = 0;
	/*7*/	virtual void* ClearCache(void) = 0;
};