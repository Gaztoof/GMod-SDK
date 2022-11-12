#pragma once

#include "../globals.hpp"
#include <fstream>
#include "../json.h"
#include <iomanip>
#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )

using nlohmann::json;
namespace ConfigSystem
{
	json to_jsonfcol(const Color color) {
		json j;
		j["r"] = color.fCol[0];
		j["g"] = color.fCol[1];
		j["b"] = color.fCol[2];
		j["a"] = color.fCol[3];
		j["c"] = color.rainbow;
		return j;
	}
	void from_jsonfcol(const json j, Color& color) {
		color.fCol[0] = j["r"];
		color.fCol[1] = j["g"];
		color.fCol[2] = j["b"];
		color.fCol[3] = j["a"];
		color.rainbow = j["c"];
	}

	json to_jsonchams(const chamsSetting& setting) {
		json j;
		j["hiddenColor"] = to_jsonfcol(setting.hiddenColor);
		j["visibleColor"] = to_jsonfcol(setting.visibleColor);
		j["hiddenMaterial"] = setting.hiddenMaterial;
		j["visibleMaterial"] = setting.visibleMaterial;
		return j;
	}
	chamsSetting from_jsonchams(const json& j) {
		chamsSetting setting(Color(255, 255, 255), Color(255, 255, 255), 0, 0);
		from_jsonfcol(j["hiddenColor"], setting.hiddenColor);
		from_jsonfcol(j["visibleColor"], setting.visibleColor);
		setting.hiddenMaterial = j["hiddenMaterial"];
		setting.visibleMaterial = j["visibleMaterial"];
		return setting;
	}

	void SaveConfig(const char* configName)
	{
		CreateDirectory(L"C:\\GMOD-SDK-Settings", NULL);

		json j;

		j["Globals"]["menuKey"] = Settings::menuKey;
		j["Globals"]["menuKeyStyle"] = Settings::menuKeyStyle;
		j["Globals"]["menuColor"] = to_jsonfcol(Settings::menuColor);
		j["Globals"]["untrusted"] = Globals::Untrusted;
		j["Globals"]["supportMulticore"] = Settings::supportMulticore;

		j["Chams"]["playerChams"] = to_jsonchams(Settings::Chams::playerChamsSettings);
		j["Chams"]["teamMate"] = to_jsonchams(Settings::Chams::teamMateSettings);
		j["Chams"]["ragdollChams"] = to_jsonchams(Settings::Chams::ragdollChamsSettings);
		j["Chams"]["weaponChams"] = to_jsonchams(Settings::Chams::weaponChamsSettings);
		j["Chams"]["npcChams"] = to_jsonchams(Settings::Chams::npcChamsSettings);
		j["Chams"]["armChams"] = to_jsonchams(Settings::Chams::armChamsSettings);
		j["Chams"]["localPlayerChams"] = to_jsonchams(Settings::Chams::localPlayerChamsSettings);

		j["ESP"]["infosEmplacement"] = Settings::ESP::infosEmplacement;
		j["ESP"]["espDormant"] = Settings::ESP::espDormant;
		j["ESP"]["espBoundingBox"] = Settings::ESP::espBoundingBox;
		j["ESP"]["espBoundingBoxColor"] = to_jsonfcol(Settings::ESP::espBoundingBoxColor);
		j["ESP"]["espHealthBar"] = Settings::ESP::espHealthBar;
		j["ESP"]["espName"] = Settings::ESP::espName;
		j["ESP"]["weaponText"] = Settings::ESP::weaponText;
		j["ESP"]["weaponAmmo"] = Settings::ESP::weaponAmmo;
		j["ESP"]["espDistance"] = Settings::ESP::espDistance;
		j["ESP"]["skeletonEsp"] = Settings::ESP::skeletonEsp;
		j["ESP"]["skeletonDetails"] = Settings::ESP::skeletonDetails;
		j["ESP"]["skeletonEspColor"] = to_jsonfcol(Settings::ESP::skeletonEspColor);
		j["ESP"]["espShapeInt"] = Settings::ESP::espShapeInt;
		j["ESP"]["entEsp"] = Settings::ESP::entEsp;
		j["ESP"]["onlyFriends"] = Settings::ESP::onlyFriends;
		j["ESP"]["espDistanceColor"] = to_jsonfcol(Settings::ESP::espDistanceColor);
		j["ESP"]["espAmmoColor"] = to_jsonfcol(Settings::ESP::espAmmoColor);
		j["ESP"]["espWeaponColor"] = to_jsonfcol(Settings::ESP::espWeaponColor);
		j["ESP"]["espNameColor"] = to_jsonfcol(Settings::ESP::espNameColor);
		j["ESP"]["espHealthColor"] = to_jsonfcol(Settings::ESP::espHealthColor);

		j["Visuals"]["fovEnabled"] = Settings::Visuals::fovEnabled;
		j["Visuals"]["fov"] = Settings::Visuals::fov;
		j["Visuals"]["viewModelFOV"] = Settings::Visuals::viewModelFOV;
		j["Visuals"]["noVisualRecoil"] = Settings::Visuals::noVisualRecoil;
		j["Visuals"]["worldColor"] = to_jsonfcol(Settings::Visuals::worldColor);
		j["Visuals"]["changeWorldColor"] = Settings::Visuals::changeWorldColor;
		j["Visuals"]["disableSkyBox"] = Settings::Visuals::disableSkyBox;
		j["Visuals"]["fullBright"] = Settings::Visuals::fullBright;

		j["AntiAim"]["currentAntiAimPitch"] = Settings::AntiAim::currentAntiAimPitch;
		j["AntiAim"]["currentAntiAimYaw"] = Settings::AntiAim::currentAntiAimYaw;
		j["AntiAim"]["enableAntiAim"] = Settings::AntiAim::enableAntiAim;
		j["AntiAim"]["antiAimKey"] = Settings::AntiAim::antiAimKey;
		j["AntiAim"]["antiAimKeyStyle"] = Settings::AntiAim::antiAimKeyStyle;
		j["AntiAim"]["fakePitch"] = Settings::AntiAim::fakePitch;

		j["Aimbot"]["aimbotFOV"] = Settings::Aimbot::aimbotFOV;
		j["Aimbot"]["silentAim"] = Settings::Aimbot::silentAim;
		j["Aimbot"]["lockOnTarget"] = Settings::Aimbot::lockOnTarget;
		j["Aimbot"]["aimbotKey"] = Settings::Aimbot::aimbotKey;
		j["Aimbot"]["aimbotKeyStyle"] = Settings::Aimbot::aimbotKeyStyle;
		j["Aimbot"]["enableAimbot"] = Settings::Aimbot::enableAimbot;
		j["Aimbot"]["aimbotHitbox"] = Settings::Aimbot::aimbotHitbox;
		j["Aimbot"]["aimbotAutoWall"] = Settings::Aimbot::aimbotAutoWall;
		j["Aimbot"]["aimbotAutoFire"] = Settings::Aimbot::aimbotAutoFire;
		j["Aimbot"]["aimbotMinDmg"] = Settings::Aimbot::aimbotMinDmg;
		j["Aimbot"]["aimbotFovEnabled"] = Settings::Aimbot::aimbotFovEnabled;
		j["Aimbot"]["drawAimbotFov"] = Settings::Aimbot::drawAimbotFov;
		j["Aimbot"]["aimbotSelection"] = Settings::Aimbot::aimbotSelection;
		j["Aimbot"]["drawAimbotHeadlines"] = Settings::Aimbot::drawAimbotHeadlines;
		j["Aimbot"]["aimAtTeammates"] = Settings::Aimbot::aimAtTeammates;
		j["Aimbot"]["aimAtFriends"] = Settings::Aimbot::aimAtFriends;
		j["Aimbot"]["onlyAimAtFriends"] = Settings::Aimbot::onlyAimAtFriends;
		j["Aimbot"]["pistolFastShoot"] = Settings::Aimbot::pistolFastShoot;
		j["Aimbot"]["smoothing"] = Settings::Aimbot::smoothing;
		j["Aimbot"]["smoothSteps"] = Settings::Aimbot::smoothSteps;
		j["Aimbot"]["fovColor"] = to_jsonfcol(Settings::Aimbot::fovColor);

		j["Misc"]["drawSpectators"] = Settings::Misc::drawSpectators;
		j["Misc"]["drawCrosshair"] = Settings::Misc::drawCrosshair;
		j["Misc"]["quickStop"] = Settings::Misc::quickStop;
		j["Misc"]["killMessage"] = Settings::Misc::killMessage;
		j["Misc"]["killMessageOOC"] = Settings::Misc::killMessageOOC;
		j["Misc"]["bunnyHop"] = Settings::Misc::bunnyHop;
		j["Misc"]["autoStrafe"] = Settings::Misc::autoStrafe;
		j["Misc"]["autoStrafeStyle"] = Settings::Misc::autoStrafeStyle;
		j["Misc"]["fastWalk"] = Settings::Misc::fastWalk;
		j["Misc"]["edgeJump"] = Settings::Misc::edgeJump;
		j["Misc"]["optiClamp"] = Settings::Misc::optiClamp;
		j["Misc"]["optiStrength"] = Settings::Misc::optiStrength;
		j["Misc"]["optiStyle"] = Settings::Misc::optiStyle;
		j["Misc"]["optiRandomization"] = Settings::Misc::optiRandomization;
		j["Misc"]["optiAutoStrafe"] = Settings::Misc::optiAutoStrafe;
		j["Misc"]["crosshairSize"] = Settings::Misc::crosshairSize;
		j["Misc"]["thirdperson"] = Settings::Misc::thirdperson;
		j["Misc"]["thirdpersonKey"] = Settings::Misc::thirdpersonKey;
		j["Misc"]["thirdpersonKeyStyle"] = Settings::Misc::thirdpersonKeyStyle;
		j["Misc"]["thirdpersonDistance"] = Settings::Misc::thirdpersonDistance;
		j["Misc"]["removeHands"] = Settings::Misc::removeHands;
		j["Misc"]["flashlightSpam"] = Settings::Misc::flashlightSpam;
		j["Misc"]["useSpam"] = Settings::Misc::useSpam;
		j["Misc"]["noRecoil"] = Settings::Misc::noRecoil;
		j["Misc"]["noSpread"] = Settings::Misc::noSpread;
		j["Misc"]["freeCam"] = Settings::Misc::freeCam;
		j["Misc"]["freeCamKey"] = Settings::Misc::freeCamKey;
		j["Misc"]["freeCamKeyStyle"] = Settings::Misc::freeCamKeyStyle;
		j["Misc"]["freeCamSpeed"] = Settings::Misc::freeCamSpeed;
		j["Misc"]["hitmarkerSoundEnabled"] = Settings::Misc::hitmarkerSoundEnabled;
		j["Misc"]["hitmarkerSound"] = Settings::Misc::hitmarkerSound;
		j["Misc"]["hitmarker"] = Settings::Misc::hitmarker;
		j["Misc"]["hitmarkerSize"] = Settings::Misc::hitmarkerSize;
		j["Misc"]["fakeLag"] = Settings::Misc::fakeLag;
		j["Misc"]["fakeLagTicks"] = Settings::Misc::fakeLagTicks;
		j["Misc"]["fakeLagKey"] = Settings::Misc::fakeLagKey;
		j["Misc"]["fakeLagKeyStyle"] = Settings::Misc::fakeLagKeyStyle;
		j["Misc"]["zoom"] = Settings::Misc::zoom;
		j["Misc"]["zoomKey"] = Settings::Misc::zoomKey;
		j["Misc"]["zoomKeyStyle"] = Settings::Misc::zoomKeyStyle;
		j["Misc"]["zoomFOV"] = Settings::Misc::zoomFOV;
		j["Misc"]["svAllowCsLua"] = Settings::Misc::svAllowCsLua;
		j["Misc"]["svCheats"] = Settings::Misc::svCheats;
		j["Misc"]["rainbowSpeed"] = Settings::Misc::rainbowSpeed;
		j["Misc"]["scriptDumper"] = Settings::Misc::scriptDumper;

		j["Misc"]["crossHairColor"] = to_jsonfcol(Settings::Misc::crossHairColor);

		j["Triggerbot"]["triggerBot"] = Settings::Triggerbot::triggerBot;
		j["Triggerbot"]["triggerBotHead"] = Settings::Triggerbot::triggerBotHead;
		j["Triggerbot"]["triggerBotChest"] = Settings::Triggerbot::triggerBotChest;
		j["Triggerbot"]["triggerBotStomach"] = Settings::Triggerbot::triggerBotStomach;
		j["Triggerbot"]["triggerbotFastShoot"] = Settings::Triggerbot::triggerbotFastShoot;
		std::ofstream o(std::string("C:\\GMOD-SDK-Settings\\") + configName);
		if (o.bad())return;
		o << std::setw(4) << j << std::endl;

	}

	void LoadConfig(const char* configName)
	{
		CreateDirectory(L"C:\\GMOD-SDK-Settings", NULL);

		json j;
		std::ifstream i((std::string("C:\\GMOD-SDK-Settings\\") + configName));
		if (!i.good()) {
			SaveConfig(configName);
			return LoadConfig(configName);
		}
		i >> j;

		try {
			Settings::menuKey = j["Globals"]["menuKey"];
			Settings::menuKeyStyle = j["Globals"]["menuKeyStyle"];
			from_jsonfcol(j["Globals"]["menuColor"], Settings::menuColor);
			Globals::Untrusted = j["Globals"]["untrusted"];
			Settings::supportMulticore = j["Globals"]["supportMulticore"];

			Settings::Chams::playerChamsSettings = from_jsonchams(j["Chams"]["playerChams"]);
			Settings::Chams::teamMateSettings = from_jsonchams(j["Chams"]["teamMate"]);
			Settings::Chams::ragdollChamsSettings = from_jsonchams(j["Chams"]["ragdollChams"]);
			Settings::Chams::weaponChamsSettings = from_jsonchams(j["Chams"]["weaponChams"]);
			Settings::Chams::npcChamsSettings = from_jsonchams(j["Chams"]["npcChams"]);
			Settings::Chams::armChamsSettings = from_jsonchams(j["Chams"]["armChams"]);
			Settings::Chams::localPlayerChamsSettings = from_jsonchams(j["Chams"]["localPlayerChams"]);

			Settings::ESP::infosEmplacement = j["ESP"]["infosEmplacement"];
			Settings::ESP::espDormant = j["ESP"]["espDormant"];
			Settings::ESP::espBoundingBox = j["ESP"]["espBoundingBox"];
			from_jsonfcol(j["ESP"]["espBoundingBoxColor"], Settings::ESP::espBoundingBoxColor);
			Settings::ESP::espHealthBar = j["ESP"]["espHealthBar"];
			Settings::ESP::espName = j["ESP"]["espName"];
			Settings::ESP::weaponText = j["ESP"]["weaponText"];
			Settings::ESP::weaponAmmo = j["ESP"]["weaponAmmo"];
			Settings::ESP::espDistance = j["ESP"]["espDistance"];
			Settings::ESP::skeletonEsp = j["ESP"]["skeletonEsp"];
			Settings::ESP::skeletonDetails = j["ESP"]["skeletonDetails"];
			from_jsonfcol(j["ESP"]["skeletonEspColor"], Settings::ESP::skeletonEspColor);
			from_jsonfcol(j["ESP"]["espDistanceColor"], Settings::ESP::espDistanceColor);
			from_jsonfcol(j["ESP"]["espAmmoColor"], Settings::ESP::espAmmoColor);
			from_jsonfcol(j["ESP"]["espWeaponColor"], Settings::ESP::espWeaponColor);
			from_jsonfcol(j["ESP"]["espNameColor"], Settings::ESP::espNameColor);
			from_jsonfcol(j["ESP"]["espHealthColor"], Settings::ESP::espHealthColor);
			Settings::ESP::espShapeInt = j["ESP"]["espShapeInt"];
			Settings::ESP::entEsp = j["ESP"]["entEsp"];
			Settings::ESP::onlyFriends = j["ESP"]["onlyFriends"];

			Settings::Visuals::fovEnabled = j["Visuals"]["fovEnabled"];
			Settings::Visuals::fov = j["Visuals"]["fov"];
			Settings::Visuals::viewModelFOV = j["Visuals"]["viewModelFOV"];
			Settings::Visuals::noVisualRecoil = j["Visuals"]["noVisualRecoil"];
			from_jsonfcol(j["Visuals"]["worldColor"], Settings::Visuals::worldColor);
			Settings::Visuals::changeWorldColor = j["Visuals"]["changeWorldColor"];
			Settings::Visuals::disableSkyBox = j["Visuals"]["disableSkyBox"];
			Settings::Visuals::fullBright = j["Visuals"]["fullBright"];
			Settings::AntiAim::currentAntiAimPitch = j["AntiAim"]["currentAntiAimPitch"];
			Settings::AntiAim::currentAntiAimYaw = j["AntiAim"]["currentAntiAimYaw"];
			Settings::AntiAim::enableAntiAim = j["AntiAim"]["enableAntiAim"];
			Settings::AntiAim::antiAimKey = j["AntiAim"]["antiAimKey"];
			Settings::AntiAim::antiAimKeyStyle = j["AntiAim"]["antiAimKeyStyle"];
			Settings::AntiAim::fakePitch = j["AntiAim"]["fakePitch"];
			 
			Settings::Aimbot::aimbotFOV = j["Aimbot"]["aimbotFOV"];
			Settings::Aimbot::silentAim = j["Aimbot"]["silentAim"];
			Settings::Aimbot::lockOnTarget = j["Aimbot"]["lockOnTarget"];
			Settings::Aimbot::aimbotKey = j["Aimbot"]["aimbotKey"];
			Settings::Aimbot::aimbotKeyStyle = j["Aimbot"]["aimbotKeyStyle"];
			Settings::Aimbot::enableAimbot = j["Aimbot"]["enableAimbot"];
			Settings::Aimbot::aimbotHitbox = j["Aimbot"]["aimbotHitbox"];
			Settings::Aimbot::aimbotAutoWall = j["Aimbot"]["aimbotAutoWall"];
			Settings::Aimbot::aimbotAutoFire = j["Aimbot"]["aimbotAutoFire"];
			Settings::Aimbot::aimbotMinDmg = j["Aimbot"]["aimbotMinDmg"];
			Settings::Aimbot::aimbotFovEnabled = j["Aimbot"]["aimbotFovEnabled"];
			Settings::Aimbot::drawAimbotFov = j["Aimbot"]["drawAimbotFov"];
			Settings::Aimbot::aimbotSelection = j["Aimbot"]["aimbotSelection"];
			Settings::Aimbot::drawAimbotHeadlines = j["Aimbot"]["drawAimbotHeadlines"];
			Settings::Aimbot::aimAtTeammates = j["Aimbot"]["aimAtTeammates"];
			Settings::Aimbot::aimAtFriends = j["Aimbot"]["aimAtFriends"];
			Settings::Aimbot::onlyAimAtFriends = j["Aimbot"]["onlyAimAtFriends"];
			Settings::Aimbot::pistolFastShoot = j["Aimbot"]["pistolFastShoot"];
			Settings::Aimbot::smoothing = j["Aimbot"]["smoothing"];
			Settings::Aimbot::smoothSteps = j["Aimbot"]["smoothSteps"];
			from_jsonfcol( j["Aimbot"]["fovColor"], Settings::Aimbot::fovColor);

			Settings::Misc::drawSpectators = j["Misc"]["drawSpectators"];
			Settings::Misc::drawCrosshair = j["Misc"]["drawCrosshair"];
			Settings::Misc::quickStop = j["Misc"]["quickStop"];
			Settings::Misc::killMessage = j["Misc"]["killMessage"];
			Settings::Misc::killMessageOOC = j["Misc"]["killMessageOOC"];
			Settings::Misc::bunnyHop = j["Misc"]["bunnyHop"];
			Settings::Misc::autoStrafe = j["Misc"]["autoStrafe"];
			Settings::Misc::autoStrafeStyle = j["Misc"]["autoStrafeStyle"];
			Settings::Misc::fastWalk = j["Misc"]["fastWalk"];
			Settings::Misc::edgeJump = j["Misc"]["edgeJump"];
			Settings::Misc::optiClamp = j["Misc"]["optiClamp"];
			Settings::Misc::optiStrength = j["Misc"]["optiStrength"];
			Settings::Misc::optiStyle = j["Misc"]["optiStyle"];
			Settings::Misc::optiRandomization = j["Misc"]["optiRandomization"];
			Settings::Misc::optiAutoStrafe = j["Misc"]["optiAutoStrafe"];
			Settings::Misc::crosshairSize = j["Misc"]["crosshairSize"];
			Settings::Misc::thirdperson = j["Misc"]["thirdperson"];
			Settings::Misc::thirdpersonKey = j["Misc"]["thirdpersonKey"];
			Settings::Misc::thirdpersonKeyStyle = j["Misc"]["thirdpersonKeyStyle"];
			Settings::Misc::thirdpersonDistance = j["Misc"]["thirdpersonDistance"];
			Settings::Misc::removeHands = j["Misc"]["removeHands"];
			Settings::Misc::flashlightSpam = j["Misc"]["flashlightSpam"];
			Settings::Misc::useSpam = j["Misc"]["useSpam"];
			Settings::Misc::noRecoil = j["Misc"]["noRecoil"];
			Settings::Misc::noSpread = j["Misc"]["noSpread"];
			Settings::Misc::freeCam = j["Misc"]["freeCam"];
			Settings::Misc::freeCamKey = j["Misc"]["freeCamKey"];
			Settings::Misc::freeCamKeyStyle = j["Misc"]["freeCamKeyStyle"];
			Settings::Misc::freeCamSpeed = j["Misc"]["freeCamSpeed"];
			Settings::Misc::hitmarkerSoundEnabled = j["Misc"]["hitmarkerSoundEnabled"];
			Settings::Misc::hitmarkerSound = j["Misc"]["hitmarkerSound"];
			Settings::Misc::hitmarker = j["Misc"]["hitmarker"];
			Settings::Misc::hitmarkerSize = j["Misc"]["hitmarkerSize"];
			Settings::Misc::fakeLag = j["Misc"]["fakeLag"];
			Settings::Misc::fakeLagTicks = j["Misc"]["fakeLagTicks"];
			Settings::Misc::fakeLagKey = j["Misc"]["fakeLagKey"];
			Settings::Misc::fakeLagKeyStyle = j["Misc"]["fakeLagKeyStyle"];
			Settings::Misc::zoom = j["Misc"]["zoom"];
			Settings::Misc::zoomKey = j["Misc"]["zoomKey"];
			Settings::Misc::zoomKeyStyle = j["Misc"]["zoomKeyStyle"];
			Settings::Misc::zoomFOV = j["Misc"]["zoomFOV"];
			Settings::Misc::svAllowCsLua = j["Misc"]["svAllowCsLua"];
			Settings::Misc::svCheats = j["Misc"]["svCheats"];
			Settings::Misc::rainbowSpeed = j["Misc"]["rainbowSpeed"];
			Settings::Misc::scriptDumper = j["Misc"]["scriptDumper"];
			from_jsonfcol(j["Misc"]["crossHairColor"], Settings::Misc::crossHairColor);

			Settings::Triggerbot::triggerBot = j["Triggerbot"]["triggerBot"];
			Settings::Triggerbot::triggerBotHead = j["Triggerbot"]["triggerBotHead"];
			Settings::Triggerbot::triggerBotChest = j["Triggerbot"]["triggerBotChest"];
			Settings::Triggerbot::triggerBotStomach = j["Triggerbot"]["triggerBotStomach"];
			Settings::Triggerbot::triggerbotFastShoot = j["Triggerbot"]["triggerbotFastShoot"];
		}
		catch(...)
		{
			SaveConfig(configName);
			return LoadConfig(configName);
		}
		std::ofstream o(std::string("settings\\") + configName);
		if (o.bad())return;
		o << std::setw(4) << j << std::endl;

	}
	void ResetConfig()
	{
		// I use NULL because it's 0, and can be a bool at the same time.
		Settings::menuKey = KEY_INSERT;
		Settings::menuKeyStyle = 1;
		Settings::menuColor = Color(0,255,0);
		Globals::Untrusted = NULL;
		Settings::supportMulticore = true;

		Settings::Chams::playerChamsSettings = chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0);
		Settings::Chams::teamMateSettings = chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0);
		Settings::Chams::ragdollChamsSettings = chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0);
		Settings::Chams::weaponChamsSettings = chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0);
		Settings::Chams::npcChamsSettings = chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0);
		Settings::Chams::armChamsSettings = chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0);
		Settings::Chams::localPlayerChamsSettings = chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0);

		Settings::ESP::infosEmplacement = NULL;
		Settings::ESP::espDormant = NULL;
		Settings::ESP::espBoundingBox = NULL;
		Settings::ESP::espBoundingBoxColor = Color(255, 255, 255);
		Settings::ESP::espHealthBar = NULL;
		Settings::ESP::espName = NULL;
		Settings::ESP::weaponText = NULL;
		Settings::ESP::weaponAmmo = NULL;
		Settings::ESP::espDistance = NULL;
		Settings::ESP::skeletonEsp = NULL;
		Settings::ESP::skeletonDetails = NULL;
		Settings::ESP::skeletonEspColor = Color(255, 255, 255);
		Settings::ESP::espDistanceColor = Color(255, 255, 255);
		Settings::ESP::espAmmoColor = Color(255, 255, 255);
		Settings::ESP::espWeaponColor = Color(255, 255, 255);
		Settings::ESP::espNameColor = Color(255, 255, 255);
		Settings::ESP::espHealthColor = Color(255, 255, 255);
		Settings::ESP::espShapeInt = NULL;
		Settings::ESP::entEsp = NULL;
		Settings::ESP::onlyFriends = NULL;

		Settings::Visuals::fovEnabled = false;
		Settings::Visuals::fov = 90.f;
		Settings::Visuals::viewModelFOV = 90.f;
		Settings::Visuals::noVisualRecoil = NULL;
		Settings::Visuals::worldColor = Color(255, 255, 255);
		Settings::Visuals::changeWorldColor = NULL;
		Settings::Visuals::disableSkyBox = NULL;
		Settings::Visuals::fullBright = NULL;

		Settings::AntiAim::currentAntiAimPitch = NULL;
		Settings::AntiAim::currentAntiAimYaw = NULL;
		Settings::AntiAim::enableAntiAim = NULL;
		Settings::AntiAim::antiAimKey = KEY_NONE;
		Settings::AntiAim::antiAimKeyStyle = 1;
		Settings::AntiAim::fakePitch = NULL;

		Settings::Aimbot::aimbotFOV = 5.f;
		Settings::Aimbot::silentAim = NULL;
		Settings::Aimbot::lockOnTarget = NULL;
		Settings::Aimbot::aimbotKeyStyle = KEY_NONE;
		Settings::Aimbot::aimbotKeyStyle = NULL;
		Settings::Aimbot::enableAimbot = NULL;
		Settings::Aimbot::aimbotHitbox = NULL;
		Settings::Aimbot::aimbotAutoWall = NULL;
		Settings::Aimbot::aimbotAutoFire = NULL;
		Settings::Aimbot::aimbotMinDmg = 1.f;
		Settings::Aimbot::aimbotFovEnabled = NULL;
		Settings::Aimbot::drawAimbotFov = NULL;
		Settings::Aimbot::aimbotSelection = NULL;
		Settings::Aimbot::drawAimbotHeadlines = NULL;
		Settings::Aimbot::aimAtTeammates = NULL;
		Settings::Aimbot::aimAtFriends = NULL;
		Settings::Aimbot::onlyAimAtFriends = NULL;
		Settings::Aimbot::pistolFastShoot = NULL;
		Settings::Aimbot::smoothing = NULL;
		Settings::Aimbot::smoothSteps = 1;
		Settings::Aimbot::fovColor = Color(255,255,255);

		Settings::Misc::drawSpectators = NULL;
		Settings::Misc::drawCrosshair = NULL;
		Settings::Misc::quickStop = NULL;
		Settings::Misc::killMessage = NULL;
		Settings::Misc::killMessageOOC = NULL;
		Settings::Misc::bunnyHop = NULL;
		Settings::Misc::autoStrafe = NULL;
		Settings::Misc::autoStrafeStyle = NULL;
		Settings::Misc::fastWalk = NULL;
		Settings::Misc::edgeJump = NULL;
		Settings::Misc::optiClamp = NULL;
		Settings::Misc::optiStrength = 100.f;
		Settings::Misc::optiStyle = NULL;
		Settings::Misc::optiRandomization = NULL;
		Settings::Misc::optiAutoStrafe = NULL;
		Settings::Misc::crosshairSize = 1.f;
		Settings::Misc::thirdperson = NULL;
		Settings::Misc::thirdpersonKey = KEY_NONE;
		Settings::Misc::thirdpersonKeyStyle = 1;
		Settings::Misc::thirdpersonDistance = 20.f;
		Settings::Misc::removeHands = NULL;
		Settings::Misc::flashlightSpam = NULL;
		Settings::Misc::useSpam = NULL;
		Settings::Misc::noRecoil = NULL;
		Settings::Misc::noSpread = NULL;
		Settings::Misc::freeCam = NULL;
		Settings::Misc::freeCamKey = KEY_NONE;
		Settings::Misc::freeCamKeyStyle = 1;
		Settings::Misc::freeCamSpeed = 1.f;
		Settings::Misc::hitmarkerSoundEnabled = NULL;
		Settings::Misc::hitmarkerSound = NULL;
		Settings::Misc::hitmarker = NULL;
		Settings::Misc::hitmarkerSize = 10.f;
		Settings::Misc::fakeLag = NULL;
		Settings::Misc::fakeLagTicks = 1;
		Settings::Misc::fakeLagKey = KEY_NONE;
		Settings::Misc::fakeLagKeyStyle = 1;
		Settings::Misc::zoom = NULL;
		Settings::Misc::zoomKey = KEY_NONE;
		Settings::Misc::zoomKeyStyle = 1;
		Settings::Misc::zoomFOV = 90.f;
		Settings::Misc::svCheats = NULL;
		Settings::Misc::svAllowCsLua = NULL;
		Settings::Misc::rainbowSpeed = 1.f;
		Settings::Misc::scriptDumper = NULL;
		Settings::Misc::crossHairColor = Color(255, 255, 255);

		Settings::Triggerbot::triggerBot = NULL;
		Settings::Triggerbot::triggerBotHead = NULL;
		Settings::Triggerbot::triggerBotChest = NULL;
		Settings::Triggerbot::triggerBotStomach = NULL;
		Settings::Triggerbot::triggerbotFastShoot = NULL;
	}
}