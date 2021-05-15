#pragma once
#include "Vector.h"
// Created with ReClass.NET 1.2 by KN4CK3R
class CInput
{
public:
	char pad_0000[140]; //0x0000
	bool m_fCameraInterceptingMouse; //0x008C
	bool m_fCameraInThirdPerson; //0x008D
	bool m_fCameraMovingWithMouse; //0x008E
	bool m_fCameraDistanceMove; //0x008F
	int32_t m_nCameraOldX; //0x0090
	int32_t m_nCameraOldY; //0x0094
	int32_t m_nCameraX; //0x0098
	int32_t m_nCameraY; //0x009C
	bool m_CameraIsOrthographic; //0x00A0
	char pad_00A1[3]; //0x00A1
	Vector m_angPreviousViewAngles; //0x00A4
	float m_flLastForwardMove; //0x00B0
	float m_flPreviousJoystickForward; //0x00B4
	float m_flPreviousJoystickSide; //0x00B8
	float m_flPreviousJoystickPitch; //0x00BC
	float m_flPreviousJoystickYaw; //0x00C0
	void* m_pCommands; //0x00C4
	void* m_pVerifiedCommands; //0x00C8
	void* m_pCameraThirdData; //0x00CC
	char pad_00D0[888]; //0x00D0
}; //Size: 0x0448