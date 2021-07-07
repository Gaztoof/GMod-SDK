/*#include "KeyValues.h"
#include <windows.h>		// for widechartomultibyte and multibytetowidechar

#include "../tier0/Color.h"
#include <stdlib.h>
#include <ctype.h>
#include "../client/ConVar.h"
#include "../tier0/Vector.h"
#include "../tier0/shareddefs.h"
#include <vector>
*/
/*const char* StringAfterPrefix(const char* str, const char* prefix)
{
	do
	{
		if (!*prefix)
			return str;
	} 	while (tolower(*str++) == tolower(*prefix++));
	return NULL;
}
static char const* ParseStringToken(char const* szStringVal, char const** ppEndOfParse)
{
	// Eat whitespace
	while (isspace(*szStringVal))
		++szStringVal;

	char const* pszResult = szStringVal;

	while (*szStringVal && !isspace(*szStringVal))
		++szStringVal;

	if (ppEndOfParse)
	{
		*ppEndOfParse = szStringVal;
	}

	return pszResult;
}
void KeyValues::SetStringValue(char const* strValue)
{
	// delete the old value
	delete[] m_sValue;
	// make sure we're not storing the WSTRING  - as we're converting over to STRING
	delete[] m_wsValue;
	m_wsValue = NULL;

	if (!strValue)
	{
		// ensure a valid value
		strValue = "";
	}

	// allocate memory for the new value and copy it in
	int len = strlen(strValue);
	m_sValue = new char[len + 1];
	memcpy(m_sValue, strValue, len + 1);

	m_iDataType = TYPE_STRING;
}

//-----------------------------------------------------------------------------
// Purpose: Set the string value of a keyName. 
//-----------------------------------------------------------------------------
void KeyValues::SetString(const char* keyName, const char* value)
{
	if (KeyValues* dat = FindKey(keyName, true))
	{
		dat->SetStringValue(value);
	}
}

//-----------------------------------------------------------------------------
// Purpose: Set the string value of a keyName. 
//-----------------------------------------------------------------------------
void KeyValues::SetWString(const char* keyName, const wchar_t* value)
{
	KeyValues* dat = FindKey(keyName, true);
	if (dat)
	{
		// delete the old value
		delete[] dat->m_wsValue;
		// make sure we're not storing the STRING  - as we're converting over to WSTRING
		delete[] dat->m_sValue;
		dat->m_sValue = NULL;

		if (!value)
		{
			// ensure a valid value
			value = L"";
		}

		// allocate memory for the new value and copy it in
		int len = wcslen(value);
		dat->m_wsValue = new wchar_t[len + 1];
		memcpy(dat->m_wsValue, value, (len + 1) * sizeof(wchar_t));

		dat->m_iDataType = TYPE_WSTRING;
	}
}

void KeyValues::SetInt(const char* keyName, int value)
{
	KeyValues* dat = FindKey(keyName, true);

	if (dat)
	{
		dat->m_iValue = value;
		dat->m_iDataType = TYPE_INT;
	}
}

KeyValues* KeyValues::FindKey(int keySymbol) const
{
	for (KeyValues* dat = this ? m_pSub : NULL; dat != NULL; dat = dat->m_pPeer)
	{
		if (dat->m_iKeyName == (uint32_t)keySymbol)
			return dat;
	}

	return NULL;
}
void KeyValues::SetNextKey(KeyValues* pDat)
{
	m_pPeer = pDat;
}
*/
//-----------------------------------------------------------------------------
// Purpose: Find a keyValue, create it if it is not found.
//			Set bCreate to true to create the key if it doesn't already exist 
//			(which ensures a valid pointer will be returned)
//-----------------------------------------------------------------------------
/*KeyValues* KeyValues::FindKey(const char* keyName, bool bCreate)
{
	// Validate NULL == this early out
	if (!this)
	{
		Assert(!bCreate);
		return NULL;
	}

	// return the current key if a NULL subkey is asked for
	if (!keyName || !keyName[0])
		return this;

	// look for '/' characters deliminating sub fields
	std::vector< char > szBuf;
	const char* subStr = strchr(keyName, '/');
	const char* searchStr = keyName;

	// pull out the substring if it exists
	if (subStr)
	{
		int size = subStr - keyName;
		Assert(size >= 0);
		Assert(size < 1024 * 1024);
		szBuf.resize(size + 1);
		memcpy(szBuf.data(), keyName, size);
		szBuf[size] = 0;
		if (strlen(keyName) > 1)
		{
			// If the key name is just '/', we don't treat is as a key with subfields, but use the '/' as a key name directly
			searchStr = szBuf.data();
		}
	}


	// lookup the symbol for the search string,
	// we do not need the case-sensitive symbol at this time
	// because if the key is found, then it will be found by case-insensitive lookup
	// if the key is not found and needs to be created we will pass the actual searchStr
	// and have the new KeyValues constructor get/create the case-sensitive symbol
	typedef HKeySymbol(__thiscall* _GetSymbolForString)(void*, const char*, bool);
	typedef void*(__thiscall* _KeyValuesSystem)();

	uintptr_t vstdlibBase = (uintptr_t)GetModuleHandleA("vstdlib.dll");
	_KeyValuesSystem keyValSystemConstr = (_KeyValuesSystem)GetProcAddress((HMODULE)vstdlibBase, "KeyValuesSystem");

	HKeySymbol iSearchStr = ((_GetSymbolForString)((vstdlibBase) + 0xBE00))(keyValSystemConstr(), searchStr, bCreate); // that was just for testing purposes, i know i shouldn't hardcode especially since it's just an interface but was lazy, disabled anyway
	if (iSearchStr == INVALID_KEY_SYMBOL)
	{
		// not found, couldn't possibly be in key value list
		return NULL;
	}

	KeyValues* lastItem = NULL;
	KeyValues* dat;
	// find the searchStr in the current peer list
	for (dat = m_pSub; dat != NULL; dat = dat->m_pPeer)
	{
		lastItem = dat;	// record the last item looked at (for if we need to append to the end of the list)

		// symbol compare
		if (dat->m_iKeyName == (uint32_t)iSearchStr)
		{
			break;
		}
	}

	if (!dat && m_pChain)
	{
		dat = m_pChain->FindKey(keyName, false);
	}

	// make sure a key was found
	if (!dat)
	{
		if (bCreate)
		{
			// we need to create a new key
			dat = new KeyValues(searchStr);
			//			Assert(dat != NULL);

			// insert new key at end of list
			if (lastItem)
			{
				lastItem->m_pPeer = dat;
			}
			else
			{
				m_pSub = dat;
			}
			dat->m_pPeer = NULL;

			// a key graduates to be a submsg as soon as it's m_pSub is set
			// this should be the only place m_pSub is set
			m_iDataType = TYPE_NONE;
		}
		else
		{
			return NULL;
		}
	}

	// if we've still got a subStr we need to keep looking deeper in the tree
	if (subStr)
	{
		// recursively chain down through the paths in the string
		return dat->FindKey(subStr + 1, bCreate);
	}

	return dat;
}*/
/*
void KeyValues::AddSubKey(KeyValues* pSubkey)
{
	// Make sure the subkey isn't a child of some other keyvalues
	Assert(pSubkey != NULL);
	Assert(pSubkey->m_pPeer == NULL);

	// add into subkey list
	if (m_pSub == NULL)
	{
		m_pSub = pSubkey;
	}
	else
	{
		KeyValues* pTempDat = m_pSub;
		while (pTempDat->GetNextKey() != NULL)
		{
			pTempDat = pTempDat->GetNextKey();
		}

		pTempDat->SetNextKey(pSubkey);
	}
}

KeyValues* KeyValues::FromString(char const* szName, char const* szStringVal, char const** ppEndOfParse)
{
	if (!szName)
		szName = "";

	if (!szStringVal)
		szStringVal = "";

	KeyValues* kv = new KeyValues(szName);
	if (!kv)
		return NULL;

	char chName[256] = { 0 };
	char chValue[1024] = { 0 };

	for (; ; )
	{
		char const* szEnd;

		char const* szVarValue = NULL;
		char const* szVarName = ParseStringToken(szStringVal, &szEnd);
		if (!*szVarName)
			break;
		if (*szVarName == '}')
		{
			szStringVal = szVarName + 1;
			break;
		}
		strncpy(chName, szVarName, (int)MIN(sizeof(chName), szEnd - szVarName + 1));
		szVarName = chName;
		szStringVal = szEnd;

		if (*szVarName == '{')
		{
			szVarName = "";
			goto do_sub_key;
		}

		szVarValue = ParseStringToken(szStringVal, &szEnd);
		if (*szVarValue == '}')
		{
			szStringVal = szVarValue + 1;
			kv->SetString(szVarName, "");
			break;
		}
		strncpy(chValue, szVarValue, (int)MIN(sizeof(chValue), szEnd - szVarValue + 1));
		szVarValue = chValue;
		szStringVal = szEnd;

		if (*szVarValue == '{')
		{
			goto do_sub_key;
		}

		// Try to recognize some known types
		if (char const* szInt = StringAfterPrefix(szVarValue, "#int#"))
		{
			kv->SetInt(szVarName, atoi(szInt));
		}
		else if (!_stricmp(szVarValue, "#empty#"))
		{
			kv->SetString(szVarName, "");
		}
		else
		{
			kv->SetString(szVarName, szVarValue);
		}
		continue;

	do_sub_key:
		{
			KeyValues* pSubKey = KeyValues::FromString(szVarName, szStringVal, &szEnd);
			if (pSubKey)
			{
				kv->AddSubKey(pSubKey);
			}
			szStringVal = szEnd;
			continue;
		}
	}

	if (ppEndOfParse)
	{
		*ppEndOfParse = szStringVal;
	}

	return kv;
}*/