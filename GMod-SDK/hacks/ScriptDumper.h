#pragma once
#include "../globals.hpp"
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include <string>
#include <iostream>
namespace fs = std::filesystem;
fs::path SanitizePath(fs::path in)
{
	fs::path retPath;
	for (const auto& part : in)
		if (part != ".." && part != "\\" && part != "/" )
		{
			std::string outPartName;
			for (auto ch : part.string())
			{
				if ((ch == '\\' || ch == '/' || ch == ':' || ch == '?' || ch == '"' || ch == '<' || ch == '>' || ch == '|') && part != in.root_name()) // hm that's bad
					outPartName += '.';
				else if (ch >= ' ' && ch <= '~')
					outPartName += ch;
			}

			retPath += outPartName;
			if(outPartName != in.filename())
			retPath += "\\";
		}

	return retPath;
}
void CreateRecurringDir(fs::path in)
{
	fs::path out;
	for (const auto& part : in)
	{
		if (part != "\\" && part != "/")
		{
			out += part;
			out += "\\";
		}

		if(out != out.root_path())
			fs::create_directory(out);
	}
}

void SaveScript(std::string fileName, std::string fileContent)
{
	try
	{
		if (fileName == "RunString(Ex)")fileName = "runString.lua";
		fs::path scripthookPath = "C:\\GaztoofScriptHook\\";
		CLuaInterface* Lua = LuaShared->GetLuaInterface((unsigned char)LuaSomething::LUA_CLIENT);
		if (!Lua)return;

		if (EngineClient->GetNetChannelInfo() && EngineClient->GetNetChannelInfo()->GetAddress())
		{
			// That's pretty bad...

			Lua->PushSpecial(0); // https://github.com/Facepunch/gmod-module-base/blob/master/include/GarrysMod/Lua/LuaBase.h
			Lua->GetField(-1, "GetHostName");
			Lua->Push(-2);
			Lua->Call(1, 1);
			auto hostName = Lua->GetString(-1, NULL);
			Lua->Pop(2);

			if (hostName)
				scripthookPath += hostName;
			scripthookPath += " - ";
			scripthookPath += EngineClient->GetNetChannelInfo()->GetAddress();
		}
		else scripthookPath += "No Server";

		scripthookPath += "\\";

		scripthookPath += fs::path(fileName);

		fs::path targetDir = SanitizePath(scripthookPath);
		CreateRecurringDir(targetDir.parent_path());

		std::ofstream outFile;
		outFile.open(targetDir.string());
		if (outFile.good())
		{
			outFile << fileContent;
			outFile.close();
		}
	}
	catch (...) {}
}