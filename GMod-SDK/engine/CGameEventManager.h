#pragma once

#include <Windows.h>
#include <stdint.h>

class IGameEvent
{
public:
	virtual ~IGameEvent() {};
	virtual const char* GetName() const = 0;

	virtual bool IsReliable() const = 0;
	virtual bool IsLocal() const = 0;
	virtual bool IsEmpty(const char* keyname = NULL) = 0;

	virtual bool GetBool(const char* keyname = NULL, bool default_value = false) = 0;
	virtual int GetInt(const char* keyname = NULL, int default_value = 0) = 0;
	virtual uint64_t GetUint64(const char* keyname = NULL, uint64_t default_value = 0) = 0;
	virtual float GetFloat(const char* keyname = NULL, float default_value = 0.0f) = 0;
	virtual const char* GetString(const char* keyname = NULL, const char* default_value = "") = 0;
	virtual const wchar_t* GetWString(const char* keyname = NULL, const wchar_t* default_value = L"") = 0;
	virtual const void* GetPtr(const char* keyname = NULL, const void* default_values = NULL) = 0;

	virtual void SetBool(const char* keyname, bool value) = 0;
	virtual void SetInt(const char* keyname, int value) = 0;
	virtual void SetUint64(const char* keyname, uint64_t value) = 0;
	virtual void SetFloat(const char* keyname, float value) = 0;
	virtual void SetString(const char* keyname, const char* value) = 0;
	virtual void SetWString(const char* keyname, const wchar_t* value) = 0;
	virtual void SetPtr(const char* keyname, const void* value) = 0;
};
class IGameEventListener2
{
public:
	virtual	~IGameEventListener2(void) {};

	// FireEvent is called by EventManager if event just occured
	// KeyValue memory will be freed by manager if not needed anymore
	virtual void FireGameEvent(IGameEvent* event) = 0;
};

// Auto reconstructed from vtable block @ 0x004F3AD8
// from "engine.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class CGameEventManager
{
public:
	/*0*/	virtual void* Destr1() = 0;
	/*1*/	virtual void* LoadEventsFromFile(char const*) = 0;
	/*2*/	virtual void* Reset(void) = 0;
	/*3*/	virtual void* AddListener(IGameEventListener2*, char const*, bool) = 0;
	/*4*/	virtual void* FindListener(IGameEventListener2*, char const*) = 0;
	/*5*/	virtual void* RemoveListener(IGameEventListener2*) = 0;
	/*6*/	virtual void* CreateEventt(char const*, bool) = 0;
	/*7*/	virtual void* FireEvent(IGameEvent*, bool) = 0;
	/*8*/	virtual void* FireEventClientSide(IGameEvent*) = 0;
	/*9*/	virtual void* DuplicateEvent(IGameEvent*) = 0;
	/*10*/	virtual void* FreeEvent(IGameEvent*) = 0;
	/*11*/	virtual void* SerializeEvent(IGameEvent*, void*) = 0;
	/*12*/	virtual void* UnserializeEvent(void*) = 0;
};