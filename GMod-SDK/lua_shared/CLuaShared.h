#pragma once
#include <string>
#include <vector>
#include "CLuaInterface.h"
// Auto reconstructed from vtable block @ 0x00082B68
// from "lua_shared.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
enum LuaFindResult
{
	IHaveNoIdea
};
enum class LuaInterfaceType
{
	LUA_CLIENT = 0,
	LUA_SERVER = 1,
	LUA_MENU = 2
};

class CLuaShared
{
public:
	/*0*/	virtual void* destr1() = 0;
	/*2*/	virtual void* Init(void* (*)(char const*, int*), bool, void*, void*) = 0;
	/*3*/	virtual void* Shutdown(void) = 0;
	/*4*/	virtual void* DumpStats(void) = 0;
	/*5*/	virtual CLuaInterface* CreateLuaInterface(unsigned char, bool) = 0;
	/*6*/	virtual void* CloseLuaInterface(void*) = 0;
	/*7*/	virtual CLuaInterface* GetLuaInterface(unsigned char) = 0;
	/*8*/	virtual void LoadFile(std::string const&, std::string const&, bool, bool) = 0;
	/*9*/	virtual void* GetCache(std::string const&) = 0;
	/*10*/	virtual void* MountLua(char const*) = 0;
	/*11*/	virtual void* MountLuaAdd(char const*, char const*) = 0;
	/*12*/	virtual void* UnMountLua(char const*) = 0;
	/*13*/	virtual void* SetFileContents(char const*, char const*) = 0;
	/*14*/	virtual void* SetLuaFindHook(void*) = 0;
	/*15*/	virtual void* FindScripts(std::string const&, std::string const&, std::vector<LuaFindResult> &) = 0;
	/*16*/	virtual void* GetStackTraces(void) = 0;
	/*17*/	virtual void* InvalidateCache(std::string const&) = 0;
	/*18*/	virtual void* EmptyCache(void) = 0;
};