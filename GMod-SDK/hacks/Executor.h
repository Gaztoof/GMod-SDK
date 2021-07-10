#pragma once

#include "../globals.hpp"
#include "../hooks/RunStringEx.h"
#include <commdlg.h>
#include <mutex>
std::mutex executorMutex;

void ExecuteScript(const char* input)
{
	CLuaInterface* LuaInterface = LuaShared->GetLuaInterface(0);
	if (!LuaInterface) return;
    std::unique_lock lock(executorMutex);
    waitingToBeExecuted.store(std::make_pair(true, input));
}
void LoadScriptFromFile()
{
    OPENFILENAMEA openFileName = { 0 };
    char fileName[MAX_PATH] = "";

    openFileName.lStructSize = sizeof(OPENFILENAMEA);
    openFileName.lpstrDefExt = "lua";
    openFileName.lpstrFile = fileName;
    openFileName.lpstrFilter = "LUA Files (*.lua)\0*.lua\0\0";
    openFileName.hwndOwner = NULL;
    openFileName.nMaxFile = sizeof(fileName);
    openFileName.Flags = OFN_ENABLESIZING | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    if (GetOpenFileNameA(&openFileName))
    {
        if (!strlen(fileName))
            return;
        std::ifstream stream(fileName);
        if (stream.bad())
            return;
        std::string fileContent = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        strcpy(Settings::ScriptInput, fileContent.c_str());
    }
}