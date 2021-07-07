#pragma once


#include <Windows.h>
#include "../client/ConVar.h"

// i prefer doing that than including globals.hpp ...
extern CCvar* CVar;

class SpoofedConVar {
	// https://gist.github.com/markhc/c975ce63c8714709e410f1be43e4048f
public:
	SpoofedConVar(ConVar* pCVar) {
		m_pOriginalCVar = pCVar;
		Spoof();
	}
	~SpoofedConVar() {
		DWORD dwOld;

		//Restore value
		m_pOriginalCVar->InternalSetValue(m_szOriginalValue);
		//Restore the name
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);
		strcpy((char*)m_pOriginalCVar->pszName, m_szOriginalName);
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);

		//Unregister dummy cvar
		CVar->UnregisterConCommand(m_pDummyCVar);
		free(m_pDummyCVar);
		m_pDummyCVar = nullptr;
	}

	void Spoof() {
		if (m_pOriginalCVar) {
			//Save old name value and flags so we can restore the cvar lates if needed
			m_iOriginalFlags = m_pOriginalCVar->nflags;
			strcpy(m_szOriginalName, m_pOriginalCVar->pszName);
			strcpy(m_szOriginalValue, m_pOriginalCVar->pszValueStr);

			sprintf_s(m_szDummyName, 128, "dummy_%s", m_szOriginalName);

			//Create the dummy cvar
			m_pDummyCVar = (ConVar*)malloc(sizeof(ConVar));
			if (!m_pDummyCVar) return;
			memcpy(m_pDummyCVar, m_pOriginalCVar, sizeof(ConVar));

			m_pDummyCVar->pNextConvar = nullptr;
			//Register it
			CVar->RegisterConCommand(m_pDummyCVar);

			//Fix "write access violation" bullshit
			DWORD dwOld;
			VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);

			//Rename the cvar
			strcpy((char*)m_pOriginalCVar->pszName, m_szDummyName);

			VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);

			//m_pOriginalCVar->RemoveFlags(0xFFFFFFFF); // that'll make ur game crash for some reasons ? 
		}
	}

public:
    ConVar* m_pOriginalCVar = nullptr;
private:
    ConVar* m_pDummyCVar = nullptr;

    char m_szDummyName[128];
    char m_szDummyValue[128];
    char m_szOriginalName[128];
    char m_szOriginalValue[128];
    int m_iOriginalFlags;

};