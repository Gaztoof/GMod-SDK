#pragma once
#include "../tier0/shareddefs.h"

// Auto reconstructed from vtable block @ 0x0000A118
// from "inputsystem.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class CInputSystem
{
public:
	/*0*/	virtual void Connect(void* (*)(char const*, int*)) = 0;
	/*1*/	virtual void Disconnect(void) = 0;
	/*2*/	virtual void QueryInterface(char const*) = 0;
	/*3*/	virtual void Init(void) = 0;
	/*4*/	virtual void Shutdown(void) = 0;
						
	/*5*/	virtual void Undocumented1(void) = 0; // All of those 4 functions are unimplemented. Probably disabled by the devs or the compiler.
	/*5*/	virtual void Undocumented2(void) = 0;
	/*5*/	virtual void Undocumented3(void) = 0;
	/*5*/	virtual void Undocumented4(void) = 0;
						
	/*5*/	virtual void AttachToWindow(void*) = 0;
	/*6*/	virtual void DetachFromWindow(void) = 0;
	/*7*/	virtual void EnableInput(bool) = 0;
	/*8*/	virtual void EnableMessagePump(bool) = 0;
	/*9*/	virtual void PollInputState(void) = 0;
	/*10*/	virtual int GetPollTick(void)const = 0;
	/*11*/	virtual bool IsButtonDown(ButtonCode_t)const = 0;
	/*12*/	virtual int GetButtonPressedTick(ButtonCode_t)const = 0;
	/*13*/	virtual int GetButtonReleasedTick(ButtonCode_t)const = 0;
	/*14*/	virtual int GetAnalogValue(void*)const = 0;
	/*15*/	virtual int GetAnalogDelta(void*)const = 0;
	/*16*/	virtual int GetEventCount(void)const = 0;
	/*17*/	virtual int GetEventData(void)const = 0;
	/*18*/	virtual void PostUserEvent(void const*) = 0;
	/*19*/	virtual int GetJoystickCount(void)const = 0;
	/*20*/	virtual void EnableJoystickInput(int, bool) = 0;
	/*21*/	virtual void EnableJoystickDiagonalPOV(int, bool) = 0;
	/*22*/	virtual void SampleDevices(void) = 0;
	/*23*/	virtual void SetRumble(float, float, int) = 0;
	/*24*/	virtual void StopRumble(void) = 0;

	/*25*/	virtual void Undocumented5(void) = 0;
	/*26*/	virtual void Undocumented6(void) = 0;
	/*27*/	virtual void Undocumented7(void) = 0;
	/*28*/	virtual void Undocumented8(void) = 0;
	/*29*/	virtual void Undocumented9(void) = 0;
	/*30*/	virtual void Undocumented10(void) = 0;
	/*31*/	virtual void Undocumented11(void) = 0;
	/*32*/	virtual void Undocumented12(void) = 0;
	/*33*/	virtual void Undocumented13(void) = 0;
	/*34*/	virtual void Undocumented14(void) = 0;
	/*35*/	virtual void Undocumented15(void) = 0;

	/*36*/	virtual const char* ButtonCodeToString(ButtonCode_t code) const = 0;
	/*37*/	virtual const char* AnalogCodeToString(void* code) const = 0; // AnalogCode_t
	/*38*/	virtual ButtonCode_t StringToButtonCode(const char* pString) const = 0;
	/*39*/	virtual void* StringToAnalogCode(const char* pString) const = 0;

	/*40*/	virtual void SleepUntilInput(int nMaxSleepTimeMS = -1) = 0;

	/*41*/	virtual ButtonCode_t VirtualKeyToButtonCode(int nVirtualKey) const = 0;
	/*42*/	virtual int ButtonCodeToVirtualKey(ButtonCode_t code) const = 0;

	/*
	* Every following function was a real pain to reverse. For some reasons, the MacOS inputsystem is totally different from the Windows one.
	* There's a lot of functions I named "undocumented" as I was lazy to find out what they were doing.
	*/

};