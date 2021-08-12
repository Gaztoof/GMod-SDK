#pragma once

#include <iostream>
#include "../engine/inetmessage.h"

typedef void(__thiscall* _ProcessGMOD_ServerToClient)(void*, CGModNetMessage*);
_ProcessGMOD_ServerToClient oProcessGMOD_ServerToClient;



void __fastcall hkProcessGMOD_ServerToClient(void* _this,
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif 
	CGModNetMessage* netMsg)
{
	//std::cout << netMsg->m_pBuf->GetNumBitsLeft() << " : "  << std::endl;
	return oProcessGMOD_ServerToClient(_this, netMsg);
}