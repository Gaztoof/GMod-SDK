#pragma once
#include "../globals.hpp"
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include <string>
#include <iostream>
#include <optional>

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

// Idk why, but thinking that the server can just spam runstrings to you will just eventually overload your disk / lag you sucks.
// And at the same time, they could be loading all of their scripts through net/runstrings :/
std::optional<std::string> SaveScript(std::string fileName, std::string fileContent)
{
	try
	{
		if (fileName == "RunString(Ex)" || fileName.find('.') == std::string::npos)fileName = "runString.lua";

		fs::path scripthookPath = "C:\\GaztoofScriptHook\\Original\\";
		fs::path detourPath = "C:\\GaztoofScriptHook\\Detour\\";

		if (EngineClient->GetNetChannelInfo() && EngineClient->GetNetChannelInfo()->GetAddress())
		{
			std::string hostName = Globals::hostName;

			if (hostName.length()) {
				std::replace(hostName.begin(), hostName.end(), '/', ' ');
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

		if (fileName != "runString.lua")
		{
			std::string strToPrint = "Successfully dumped script \"" + fileName + "\" !";
			ConPrint(strToPrint.c_str(), Color(204, 51, 255));
		}

		std::ofstream outFile;
		outFile.open(targetDir.string());
		if (outFile.good())
		{
			outFile << fileContent;
			outFile.close();
		}

		std::ifstream inFile;
		inFile.open(detourDir.string());
		if (inFile.good() && fileName != "runString.lua") {

			std::string content((std::istreambuf_iterator<char>(inFile)),
				(std::istreambuf_iterator<char>()));
			if (!strcmp(content.c_str(), fileContent.c_str()))return {};

			std::string strToPrint = "Successfully detoured script \"" + fileName + "\" !";
			ConPrint(strToPrint.c_str(), Color(255, 51, 113));

			fileContent = content;
			return fileContent;
		}
		/*else {
			std::ofstream outDetourFile;
			outDetourFile.open(detourDir.string());
			if (outDetourFile.good())
			{
				outDetourFile << fileContent;
				outDetourFile.close();
			}
		}*/
	}
	catch (...) {}

	return {};
}