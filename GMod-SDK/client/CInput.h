#pragma once
#include "../tier0/Vector.h"

// Created with ReClass.NET 1.2 by KN4CK3R
class CInput
{
public:
	void* N0000004F; //0x0000
	char pad_0008[136]; //0x0008
	void* m_pKeys; //0x0090
	bool m_fCameraInterceptingMouse; //0x0098
	bool m_fCameraInThirdPerson; //0x0099
	bool m_fCameraMovingWithMouse; //0x009A
	char pad_009B[21]; //0x009B
	QAngle m_angPreviousViewAngles; //0x00B0
	float m_flLastForwardMove; //0x00BC
	uint32_t m_nClearInputState; //0x00C0
	char pad_00C4[892]; //0x00C4
}; //Size: 0x0448