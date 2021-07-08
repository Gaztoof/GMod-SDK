#pragma once


#include <Windows.h>
#include "../client/ConVar.h"
#include "../Memory.h"
// i prefer doing that than including globals.hpp ...
extern CCvar* CVar;

class SpoofedConVar {
	// Inspired of https://gist.github.com/markhc/c975ce63c8714709e410f1be43e4048f
public:
	SpoofedConVar(ConVar* pCVar) {
		m_pOriginalCVar = pCVar;
		Spoof();
	}
	~SpoofedConVar() {

		CVar->UnregisterConCommand(m_pDummyCVar);
		free(m_pDummyCVar);

		DWORD dwOld;
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);
		strcpy(m_pOriginalCVar->pszName, m_szOriginalName);
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);
		VirtualProtect((LPVOID)m_pOriginalCVar->pszValueStr, 128, PAGE_READWRITE, &dwOld);
		strcpy(m_pOriginalCVar->pszValueStr, m_szOriginalValue);
		VirtualProtect((LPVOID)m_pOriginalCVar->pszValueStr, 128, dwOld, &dwOld);
	}

	void Spoof() {
		if (m_pOriginalCVar) {
			m_iOriginalFlags = m_pOriginalCVar->nflags;
			strcpy(m_szOriginalName, m_pOriginalCVar->pszName);
			strcpy(m_szOriginalValue, m_pOriginalCVar->pszValueStr);

			std::string dummyName = "XD_" + std::string(m_pOriginalCVar->pszName);

			m_pDummyCVar = (ConVar*)malloc(sizeof(ConVar));
			if (!m_pDummyCVar) return;
			memcpy(m_pDummyCVar, m_pOriginalCVar, sizeof(ConVar));			
			DWORD dwOld;
			VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);

			strcpy(m_pOriginalCVar->pszName, dummyName.c_str());
			m_pDummyCVar->Create(m_szOriginalName, m_pOriginalCVar->pszDefaultValue, m_pOriginalCVar->nflags, m_pOriginalCVar->pszHelpString, m_pOriginalCVar->bHasMin, m_pOriginalCVar->fMinVal, m_pOriginalCVar->bHasMax, m_pOriginalCVar->fMaxVal, NULL);

			CVar->RegisterConCommand(m_pDummyCVar);
			VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);

			
		}
	}

public:
    ConVar* m_pOriginalCVar = nullptr;
private:
    ConVar* m_pDummyCVar = nullptr;

    char m_szOriginalName[128];
    char m_szOriginalValue[128];
    int m_iOriginalFlags;

};