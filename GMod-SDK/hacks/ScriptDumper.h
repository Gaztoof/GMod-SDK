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

std::string SaveScript(std::string fileName, std::string fileContent)
{
	try
	{
		if (fileName == "RunString(Ex)")fileName = "runString.lua";
		fs::path scripthookPath = "C:\\GaztoofScriptHook\\Original\\";
		fs::path detourPath = "C:\\GaztoofScriptHook\\Detour\\";
		CLuaInterface* Lua = LuaShared->GetLuaInterface((unsigned char)LuaSomething::LUA_CLIENT);
		if (!Lua)return fileContent;

		if (EngineClient->GetNetChannelInfo() && EngineClient->GetNetChannelInfo()->GetAddress())
		{
			// That's pretty bad...

			Lua->PushSpecial(0); // https://github.com/Facepunch/gmod-module-base/blob/master/include/GarrysMod/Lua/LuaBase.h
			Lua->GetField(-1, "GetHostName");
			Lua->Push(-2);
			Lua->Call(1, 1);
			auto hostName = Lua->GetString(-1, NULL);
			Lua->Pop(2);

			if (hostName) {
				scripthookPath += hostName;
				detourPath += hostName;
			}
			scripthookPath += " - ";
			detourPath += " - ";
			scripthookPath += EngineClient->GetNetChannelInfo()->GetAddress();
			detourPath += EngineClient->GetNetChannelInfo()->GetAddress();
		}
		else {
			scripthookPath += "No Server";
			detourPath += "No Server";
		}

		scripthookPath += "\\";
		detourPath += "\\";

		scripthookPath += fs::path(fileName);
		detourPath += fs::path(fileName);

		fs::path targetDir = SanitizePath(scripthookPath);
		fs::path detourDir = SanitizePath(detourPath);

		CreateRecurringDir(targetDir.parent_path());
		CreateRecurringDir(detourDir.parent_path());

		

		std::ofstream outFile;
		outFile.open(targetDir.string());
		if (outFile.good())
		{
			outFile << fileContent;
			outFile.close();
		}

		std::ifstream inFile;
		inFile.open(detourDir.string());
		if (inFile.good()) {

			std::string content((std::istreambuf_iterator<char>(inFile)),
				(std::istreambuf_iterator<char>()));
			fileContent = content;

			std::cout << "Hooked file: "+detourDir.string() << std::endl;
		}
	}
	catch (...) {}

	return fileContent;
}