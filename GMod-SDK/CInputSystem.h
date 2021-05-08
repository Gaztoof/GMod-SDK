#pragma once
#include "shareddefs.h"

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

	/*
	* Every following function was a real pain to reverse. For some reasons, the MacOS inputsystem is totally different from the Windows one.
	*/

};