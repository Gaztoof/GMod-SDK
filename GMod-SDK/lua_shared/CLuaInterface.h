#pragma once
#include "../tier0/Color.h"
#include "../tier0/Vector.h"
#include <string>

// Auto reconstructed from vtable block @ 0x000823F0
// from "lua_shared.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class ILuaCallback
{
public:

	/*0*/	virtual void* CreateLuaObject() = 0;
	/*1*/	virtual void DestroyLuaObject(void* pObject) = 0;

	/*2*/	virtual void ErrorPrint(const char* strError) = 0;
	/*3*/	virtual void Msg(const char* strMsg) = 0;

	/*4*/	virtual bool CanRunScript(const char* strFilename, unsigned long CRC) = 0;
	/*5*/	virtual void onRunScript(const char* strFilename, bool bRun, const char* strScriptContents) = 0;
};
enum class LuaObjectType
{

	INVALID = -1,
	NIL,
	BOOL,
	LIGHTUSERDATA,
	NUMBER,
	STRING,
	TABLE,
	FUNCTION,
	USERDATA,
	THREAD,

	ENTITY, // 9
	VECTOR,
	ANGLE,
	PHYSOBJ,
	SAVE,
	RESTORE,
	DAMAGEINFO,
	EFFECTDATA,
	MOVEDATA,
	RECIPIENTFILTER,
	USERCMD,
	SCRIPTEDVEHICLE,

	MATERIAL,
	PANEL,
	PARTICLE,
	PARTICLEEMITTER,
	TEXTURE,
	USERMSG,

	CONVAR,
	IMESH,
	MATRIX,
	SOUND,
	PIXELVISHANDLE,
	DLIGHT,
	VIDEO,
	FILE,

	COUNT
};
// https://github.com/Facepunch/gmod-module-base/blob/master/include/GarrysMod/Lua/LuaBase.h
class CLuaInterface
{
public:
	/*0*/	virtual void* Top(void) = 0;
	/*1*/	virtual void* Push(int iStackPos) = 0;
	/*2*/	virtual void* Pop(int iStackPos) = 0;
	/*3*/	virtual void* GetTable(int iStackPos) = 0;
	/*4*/	virtual void* const GetField(int iStackPos, char const*) = 0;
	/*5*/	virtual void SetField(int iStackPos, char const*) = 0;
	/*6*/	virtual void* CreateTable(void) = 0;
	/*7*/	virtual void* SetTable(int) = 0;
	/*8*/	virtual void* SetMetaTable(int) = 0;
	/*9*/	virtual void* GetMetaTable(int) = 0;
	/*10*/	virtual void* Call(int iArgs, int iRets) = 0;
	/*11*/	virtual void* PCall(int, int, int) = 0;
	/*12*/	virtual void* Equal(int, int) = 0;
	/*13*/	virtual void* RawEqual(int, int) = 0;
	/*14*/	virtual void* Insert(int) = 0;
	/*15*/	virtual void* Remove(int) = 0;
	/*16*/	virtual void* Next(int) = 0;
	/*17*/	virtual void* NewUserdata(unsigned int) = 0;
	/*18*/	virtual void* ThrowError(char const*) = 0;
	/*19*/	virtual void* CheckType(int, int) = 0;
	/*20*/	virtual void* ArgError(int, char const*) = 0;
	/*21*/	virtual void* RawGet(int iStackPos) = 0;
	/*22*/	virtual void* RawSet(int iStackPost) = 0;
	/*23*/	virtual const char* GetString(int, unsigned int*) = 0;
	/*24*/	virtual double GetNumber(int) = 0;
	/*25*/	virtual bool GetBool(int) = 0;
	/*26*/	virtual void* GetCFunction(int) = 0;
	/*27*/	virtual void* GetUserdata(int) = 0;
	/*28*/	virtual void PushNil(void) = 0;
	/*29*/	virtual void PushString(char const*, unsigned int) = 0;
	/*30*/	virtual void PushNumber(double) = 0;
	/*31*/	virtual void PushBool(bool) = 0;
	/*32*/	virtual void PushCFunction(int (*)(void*)) = 0;
	/*33*/	virtual void PushCClosure(int (*)(void*), int) = 0;
	/*34*/	virtual void PushUserdata(void*) = 0;
	/*35*/	virtual void* ReferenceCreate(void) = 0;
	/*36*/	virtual void* ReferenceFree(int) = 0;
	/*37*/	virtual void* ReferencePush(int) = 0;
	/*38*/	virtual void* PushSpecial(int) = 0;
	/*39*/	virtual bool IsType(int, LuaObjectType) = 0;
	/*40*/	virtual LuaObjectType GetType(int) = 0;
	/*41*/	virtual void* GetTypeName(int) = 0;
	/*42*/	virtual void* CreateMetaTableType(char const*, int) = 0;
	/*43*/	virtual void* CheckString(int) = 0;
	/*44*/	virtual void* CheckNumber(int) = 0;
	/*45*/	virtual void* ObjLen(int) = 0;
	/*46*/	virtual void* GetAngle(int) = 0;
	/*47*/	virtual void* GetVector(int) = 0;
	/*48*/	virtual void* PushAngle(QAngle const&) = 0;
	/*49*/	virtual void* PushVector(Vector const&) = 0;
	/*50*/	virtual void* SetState(void*) = 0;
	/*51*/	virtual void* CreateMetaTable(char const*) = 0;
	/*52*/	virtual void* PushMetaTable(int) = 0;
	/*53*/	virtual void* PushUserType(void*, int) = 0;
	/*54*/	virtual void* SetUserType(int, void*) = 0;
	/*55*/	virtual void* Init(ILuaCallback*, bool) = 0;
	/*56*/	virtual void* Shutdown(void) = 0;
	/*57*/	virtual void* Cycle(void) = 0;
	/*58*/	virtual void* Global(void) = 0;
	/*59*/	virtual void* GetObjectt(int) = 0;
	/*60*/	virtual void* PushLuaObject(void*) = 0;
	/*61*/	virtual void* PushLuaFunction(int (*)(void*)) = 0;
	/*62*/	virtual void* LuaError(char const*, int) = 0;
	/*63*/	virtual void* TypeError(char const*, int) = 0;
	/*64*/	virtual void* CallInternal(int, int) = 0;
	/*65*/	virtual void* CallInternalNoReturns(int) = 0;
	/*66*/	virtual void* CallInternalGetBool(int) = 0;
	/*67*/	virtual void* CallInternalGetString(int) = 0;
	/*68*/	virtual void* CallInternalGet(int, void*) = 0;
	/*69*/	virtual void* NewGlobalTable(char const*) = 0;
	/*70*/	virtual void* NewTemporaryObject(void) = 0;
	/*71*/	virtual bool isUserData(int) = 0;
	/*72*/	virtual void* GetMetaTableObject(char const*, int) = 0;
	/*73*/	virtual void* GetMetaTableObject(int) = 0;
	/*74*/	virtual void* GetReturn(int) = 0;
	/*75*/	virtual bool IsServer(void) = 0;
	/*76*/	virtual bool IsClient(void) = 0;
	/*77*/	virtual bool IsMenu(void) = 0;
	/*78*/	virtual void* DestroyObject(void*) = 0;
	/*79*/	virtual void* CreateObject(void) = 0;
	/*80*/	virtual void* SetMember(void*, void*, void*) = 0;
	/*81*/	virtual void* GetNewTable(void) = 0;
	/*82*/	virtual void* SetMember(void*, float) = 0;
	/*83*/	virtual void* SetMember(void*, float, void*) = 0; // ILuaObject
	/*84*/	virtual void* SetMember(void*, char const*) = 0;
	/*85*/	virtual void* SetMember(void*, char const*, void*) = 0; // ILuaObject* key, ILuaObject* value
	/*86*/	virtual void* SetType(unsigned char) = 0;
	/*87*/	virtual void* PushLong(long) = 0;
	/*88*/	virtual void* GetFlags(int) = 0;
	/*89*/	virtual void* FindOnObjectsMetaTable(int, int) = 0;
	/*90*/	virtual void* FindObjectOnTable(int, int) = 0;
	/*91*/	virtual void* SetMemberFast(void*, int, int) = 0;
	/*92*/	virtual void* RunString(char const*, char const*, char const*, bool, bool) = 0;
	/*93*/	virtual bool IsEqual(void*, void*) = 0;
	/*94*/	virtual void* Error(char const*) = 0;
	/*95*/	virtual void* GetStringOrError(int) = 0;
	/*96*/	virtual void* RunLuaModule(char const*) = 0;
	/*97*/	virtual void* FindAndRunScript(char const*, bool, bool, char const*, bool) = 0;
	/*98*/	virtual void* SetPathID(char const*) = 0;
	/*99*/	virtual const char* GetPathID(void) = 0;
	/*100*/	virtual void* ErrorNoHalt(char const*, ...) = 0;
	/*101*/	virtual void* Msg(char const*, ...) = 0;
	/*102*/	virtual void* PushPath(char const*) = 0;
	/*103*/	virtual void* PopPath(void) = 0;
	/*104*/	virtual const char* GetPath(void) = 0;
	/*105*/	virtual void* GetColor(int) = 0;
	/*106*/	virtual void* PushColor(Color) = 0;
	/*107*/	virtual void* GetStack(int, void*) = 0;
	/*108*/	virtual void* GetInfo(char const*, void*) = 0;
	/*109*/	virtual void* GetLocal(void*, int) = 0;
	/*110*/	virtual void* GetUpvalue(int, int) = 0;
	/*111*/	virtual void* RunStringEx(char const*, char const*, char const*, bool, bool, bool, bool) = 0;
	/*112*/	virtual void* GetDataString(int, void**) = 0;
	/*113*/	virtual void* ErrorFromLua(char const*, ...) = 0;
	/*114*/	virtual void* GetCurrentLocation(void) = 0;
	/*115*/	virtual void* MsgColour(Color const&, char const*, ...) = 0;
	/*116*/	virtual void* GetCurrentFile(std::string, std::string) = 0;
	/*117*/	virtual void* CompileString(void*, std::string const&) = 0;
	/*118*/	virtual void* CallFunctionProtected(int, int, bool) = 0;
	/*119*/	virtual void* Require(char const*) = 0;
	/*120*/	virtual void* GetActualTypeName(int) = 0;
	/*121*/	virtual void* PreCreateTable(int, int) = 0;
	/*122*/	virtual void* PushPooledString(int) = 0;
	/*123*/	virtual void* GetPooledString(int) = 0;
	/*124*/	virtual void* AddThreadedCall(void*) = 0;
	/*125*/	virtual void* AppendStackTrace(char*, unsigned long) = 0;
	/*126*/	virtual void* CreateConVar(char const*, char const*, char const*, int) = 0;
	/*127*/	virtual void* CreateConCommand(char const*, char const*, int, void (*)(void const*), int (*)(char const*, char(*)[128])) = 0;
};