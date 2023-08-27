#pragma once

#include "../globals.hpp"
#include <fstream>
#include "../json.hpp"
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
	Color from_jsonfcol(const json j, Color& color) {
		color.fCol[0] = j["r"];
		color.fCol[1] = j["g"];
		color.fCol[2] = j["b"];
		color.fCol[3] = j["a"];
		color.rainbow = j["c"];
		return color;
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
	enum configHandle {
		Save,
		Load,
		Reset
	};
	template <class T>
	constexpr T HandleConfigItem(json& j, configHandle handle, T* setting, T defaultValue)
	{
		switch (handle)
		{
		case configHandle::Save:
			j = *(T*)setting;
			break;
		case configHandle::Load:
			*(T*)setting = j;
			break;
		case configHandle::Reset:
			*setting = defaultValue;
			break;

		}
		return *setting;
	}
	void HandleConfigC(json& j, configHandle handle, Color& setting, Color defaultValue)
	{
		switch (handle)
		{
		case configHandle::Save:
			j = to_jsonfcol(setting);
			break;
		case configHandle::Load:
			from_jsonfcol(j, setting);
			break;
		case configHandle::Reset:
			setting = defaultValue;
			break;
		}
	}
	void HandleConfigCS(json& j, configHandle handle, chamsSetting* setting, chamsSetting defaultValue)
	{
		switch (handle)
		{
		case configHandle::Save:
			j = to_jsonchams(*setting);
			break;
		case configHandle::Load:
			*setting = from_jsonchams(j);
			break;
		case configHandle::Reset:
			*setting = defaultValue;
			break;
		}
	}

	void _HandleConfig(const char* configName, configHandle handle)
	{
		CreateDirectory(L"C:\\GMOD-SDK-Settings", NULL);
		json j;
		if (handle == configHandle::Load)
		{
			std::ifstream i((std::string("C:\\GMOD-SDK-Settings\\") + configName));
			if (!i.good()) {
				_HandleConfig(configName, configHandle::Save);
				return _HandleConfig(configName, configHandle::Load);
			}
			i >> j;
		}

		try {
			HandleConfigItem(j["Globals"]["menuKey"], handle, &Settings::menuKey, KEY_INSERT);
			HandleConfigItem(j["Globals"]["menuKeyStyle"], handle, &Settings::menuKeyStyle, 1);
			HandleConfigC(j["Globals"]["menuColor"], handle, Settings::menuColor, Color(142, 181, 53));
			HandleConfigItem(j["Globals"]["untrusted"], handle, &Globals::Untrusted, false);

			HandleConfigCS(j["Chams"]["playerChams"], handle, &Settings::Chams::playerChamsSettings, chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0));
			HandleConfigCS(j["Chams"]["teamMateSettings"], handle, &Settings::Chams::teamMateSettings, chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0));
			HandleConfigCS(j["Chams"]["ragdollChamsSettings"], handle, &Settings::Chams::ragdollChamsSettings, chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0));
			HandleConfigCS(j["Chams"]["weaponChamsSettings"], handle, &Settings::Chams::weaponChamsSettings, chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0));
			HandleConfigCS(j["Chams"]["npcChamsSettings"], handle, &Settings::Chams::npcChamsSettings, chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0));
			HandleConfigCS(j["Chams"]["armChamsSettings"], handle, &Settings::Chams::armChamsSettings, chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0));
			HandleConfigCS(j["Chams"]["localPlayerChamsSettings"], handle, &Settings::Chams::localPlayerChamsSettings, chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0));
			HandleConfigCS(j["Chams"]["netLocalChamsSettings"], handle, &Settings::Chams::netLocalChamsSettings, chamsSetting(Color(255, 255, 255), Color(255, 255, 255), 0, 0));

			HandleConfigItem(j["ESP"]["infosEmplacement"], handle, &Settings::ESP::infosEmplacement, NULL);
			HandleConfigItem(j["ESP"]["espDormant"], handle, &Settings::ESP::espDormant, false);
			HandleConfigItem(j["ESP"]["espBoundingBox"], handle, &Settings::ESP::espBoundingBox, false);
			HandleConfigC(j["ESP"]["espBoundingBoxColor"], handle, Settings::ESP::espBoundingBoxColor, Color(255, 255, 255));
			HandleConfigItem(j["ESP"]["espHealthBar"], handle, &Settings::ESP::espHealthBar, false);
			HandleConfigItem(j["ESP"]["espName"], handle, &Settings::ESP::espName, false);
			HandleConfigItem(j["ESP"]["weaponText"], handle, &Settings::ESP::weaponText, false);
			HandleConfigItem(j["ESP"]["weaponAmmo"], handle, &Settings::ESP::weaponAmmo, false);
			HandleConfigItem(j["ESP"]["espDistance"], handle, &Settings::ESP::espDistance, false);
			HandleConfigItem(j["ESP"]["skeletonEsp"], handle, &Settings::ESP::skeletonEsp, false);
			HandleConfigItem(j["ESP"]["skeletonDetails"], handle, &Settings::ESP::skeletonDetails, false);
			HandleConfigC(j["ESP"]["skeletonEspColor"], handle, Settings::ESP::skeletonEspColor, Color(255, 255, 255));
			HandleConfigC(j["ESP"]["espDistanceColor"], handle, Settings::ESP::espDistanceColor, Color(255, 255, 255));
			HandleConfigC(j["ESP"]["espAmmoColor"], handle, Settings::ESP::espAmmoColor, Color(255, 255, 255));
			HandleConfigC(j["ESP"]["espWeaponColor"], handle, Settings::ESP::espWeaponColor, Color(255, 255, 255));
			HandleConfigC(j["ESP"]["espNameColor"], handle, Settings::ESP::espNameColor, Color(255, 255, 255));
			HandleConfigC(j["ESP"]["espHealthColor"], handle, Settings::ESP::espHealthColor, Color(255, 255, 255));
			HandleConfigItem(j["ESP"]["espShapeInt"], handle, &Settings::ESP::espShapeInt, NULL);
			HandleConfigItem(j["ESP"]["entEsp"], handle, &Settings::ESP::entEsp, false);
			HandleConfigItem(j["ESP"]["onlyFriends"], handle, &Settings::ESP::onlyFriends, false);

			HandleConfigItem(j["Visuals"]["fovEnabled"], handle, &Settings::Visuals::fovEnabled, false);
			HandleConfigItem(j["Visuals"]["fov"], handle, &Settings::Visuals::fov, 120.f);
			HandleConfigItem(j["Visuals"]["viewModelFovEnabled"], handle, &Settings::Visuals::viewModelFovEnabled, false);
			HandleConfigItem(j["Visuals"]["viewModelFov"], handle, &Settings::Visuals::viewModelFov, 90.f);
			HandleConfigItem(j["Visuals"]["noVisualRecoil"], handle, &Settings::Visuals::noVisualRecoil, false);
			HandleConfigC(j["Visuals"]["worldColor"], handle, Settings::Visuals::worldColor, Color(255, 255, 255));
			HandleConfigItem(j["Visuals"]["changeWorldColor"], handle, &Settings::Visuals::changeWorldColor, false);
			HandleConfigItem(j["Visuals"]["disableSkyBox"], handle, &Settings::Visuals::disableSkyBox, false);
			HandleConfigItem(j["Visuals"]["fullBright"], handle, &Settings::Visuals::fullBright, false);

			HandleConfigItem(j["AntiAim"]["currentAntiAimPitch"], handle, &Settings::AntiAim::currentAntiAimPitch, NULL);
			HandleConfigItem(j["AntiAim"]["currentAntiAimYaw"], handle, &Settings::AntiAim::currentAntiAimYaw, NULL);
			HandleConfigItem(j["AntiAim"]["enableAntiAim"], handle, &Settings::AntiAim::enableAntiAim, false);
			HandleConfigItem(j["AntiAim"]["antiAimKey"], handle, &Settings::AntiAim::antiAimKey, KEY_NONE);
			HandleConfigItem(j["AntiAim"]["antiAimKeyStyle"], handle, &Settings::AntiAim::antiAimKeyStyle, 1);
			HandleConfigItem(j["AntiAim"]["fakePitch"], handle, &Settings::AntiAim::fakePitch, 0.f);

			HandleConfigItem(j["Aimbot"]["aimbotFOV"], handle, &Settings::Aimbot::aimbotFOV, 5.f);
			HandleConfigItem(j["Aimbot"]["silentAim"], handle, &Settings::Aimbot::silentAim, false);
			HandleConfigItem(j["Aimbot"]["lockOnTarget"], handle, &Settings::Aimbot::lockOnTarget, false);
			HandleConfigItem(j["Aimbot"]["aimbotKey"], handle, &Settings::Aimbot::aimbotKey, KEY_NONE);
			HandleConfigItem(j["Aimbot"]["aimbotKeyStyle"], handle, &Settings::Aimbot::aimbotKeyStyle, NULL);
			HandleConfigItem(j["Aimbot"]["enableAimbot"], handle, &Settings::Aimbot::enableAimbot, false);
			HandleConfigItem(j["Aimbot"]["aimbotHitbox"], handle, &Settings::Aimbot::aimbotHitbox, NULL);
			HandleConfigItem(j["Aimbot"]["aimbotAutoWall"], handle, &Settings::Aimbot::aimbotAutoWall, false);
			HandleConfigItem(j["Aimbot"]["aimbotAutoFire"], handle, &Settings::Aimbot::aimbotAutoFire, false);
			HandleConfigItem(j["Aimbot"]["aimbotMinDmg"], handle, &Settings::Aimbot::aimbotMinDmg, 1.f);
			HandleConfigItem(j["Aimbot"]["aimbotFovEnabled"], handle, &Settings::Aimbot::aimbotFovEnabled, false);
			HandleConfigItem(j["Aimbot"]["drawAimbotFov"], handle, &Settings::Aimbot::drawAimbotFov, false);
			HandleConfigItem(j["Aimbot"]["aimbotSelection"], handle, &Settings::Aimbot::aimbotSelection, NULL);
			HandleConfigItem(j["Aimbot"]["drawAimbotHeadlines"], handle, &Settings::Aimbot::drawAimbotHeadlines, false);
			HandleConfigItem(j["Aimbot"]["aimAtTeammates"], handle, &Settings::Aimbot::aimAtTeammates, false);
			HandleConfigItem(j["Aimbot"]["aimAtFriends"], handle, &Settings::Aimbot::aimAtFriends, false);
			HandleConfigItem(j["Aimbot"]["onlyAimAtFriends"], handle, &Settings::Aimbot::onlyAimAtFriends, false);
			HandleConfigItem(j["Aimbot"]["pistolFastShoot"], handle, &Settings::Aimbot::pistolFastShoot, false);
			HandleConfigItem(j["Aimbot"]["smoothing"], handle, &Settings::Aimbot::smoothing, false);
			HandleConfigItem(j["Aimbot"]["smoothSteps"], handle, &Settings::Aimbot::smoothSteps, 1.f);
			HandleConfigC(j["Aimbot"]["fovColor"], handle, Settings::Aimbot::fovColor, Color(255, 255, 255));

			HandleConfigItem(j["Misc"]["drawSpectators"], handle, &Settings::Misc::drawSpectators, false);
			HandleConfigItem(j["Misc"]["drawCrosshair"], handle, &Settings::Misc::drawCrosshair, false);
			HandleConfigItem(j["Misc"]["quickStop"], handle, &Settings::Misc::quickStop, false);
			HandleConfigItem(j["Misc"]["killMessage"], handle, &Settings::Misc::killMessage, false);
			HandleConfigItem(j["Misc"]["killMessageOOC"], handle, &Settings::Misc::killMessageOOC, false);
			HandleConfigItem(j["Misc"]["bunnyHop"], handle, &Settings::Misc::bunnyHop, false);
			HandleConfigItem(j["Misc"]["autoStrafe"], handle, &Settings::Misc::autoStrafe, false);
			HandleConfigItem(j["Misc"]["autoStrafeStyle"], handle, &Settings::Misc::autoStrafeStyle, NULL);
			HandleConfigItem(j["Misc"]["fastWalk"], handle, &Settings::Misc::fastWalk, false);
			HandleConfigItem(j["Misc"]["edgeJump"], handle, &Settings::Misc::edgeJump, false);
			HandleConfigItem(j["Misc"]["optiClamp"], handle, &Settings::Misc::optiClamp, false);
			HandleConfigItem(j["Misc"]["optiStrength"], handle, &Settings::Misc::optiStrength, 100.f);
			HandleConfigItem(j["Misc"]["optiStyle"], handle, &Settings::Misc::optiStyle, false);
			HandleConfigItem(j["Misc"]["optiRandomization"], handle, &Settings::Misc::optiRandomization, false);
			HandleConfigItem(j["Misc"]["optiAutoStrafe"], handle, &Settings::Misc::optiAutoStrafe, false);
			HandleConfigItem(j["Misc"]["crosshairSize"], handle, &Settings::Misc::crosshairSize, 5.f);
			HandleConfigItem(j["Misc"]["thirdperson"], handle, &Settings::Misc::thirdperson, false);
			HandleConfigItem(j["Misc"]["thirdpersonKey"], handle, &Settings::Misc::thirdpersonKey, KEY_NONE);
			HandleConfigItem(j["Misc"]["thirdpersonKeyStyle"], handle, &Settings::Misc::thirdpersonKeyStyle, 1);
			HandleConfigItem(j["Misc"]["thirdpersonDistance"], handle, &Settings::Misc::thirdpersonDistance, 20.f);
			HandleConfigItem(j["Misc"]["removeHands"], handle, &Settings::Misc::removeHands, false);
			HandleConfigItem(j["Misc"]["flashlightSpam"], handle, &Settings::Misc::flashlightSpam, false);
			HandleConfigItem(j["Misc"]["useSpam"], handle, &Settings::Misc::useSpam, false);
			HandleConfigItem(j["Misc"]["noRecoil"], handle, &Settings::Misc::noRecoil, false);
			HandleConfigItem(j["Misc"]["noSpread"], handle, &Settings::Misc::noSpread, false);
			HandleConfigItem(j["Misc"]["freeCam"], handle, &Settings::Misc::freeCam, false);
			HandleConfigItem(j["Misc"]["freeCamKey"], handle, &Settings::Misc::freeCamKey, KEY_NONE);
			HandleConfigItem(j["Misc"]["freeCamKeyStyle"], handle, &Settings::Misc::freeCamKeyStyle, 1);
			HandleConfigItem(j["Misc"]["freeCamSpeed"], handle, &Settings::Misc::freeCamSpeed, 1.f);
			HandleConfigItem(j["Misc"]["hitmarkerSoundEnabled"], handle, &Settings::Misc::hitmarkerSoundEnabled, false);
			HandleConfigItem(j["Misc"]["hitmarkerSound"], handle, &Settings::Misc::hitmarkerSound, NULL);
			HandleConfigItem(j["Misc"]["hitmarker"], handle, &Settings::Misc::hitmarker, false);
			HandleConfigItem(j["Misc"]["hitmarkerSize"], handle, &Settings::Misc::hitmarkerSize, 10.f);
			HandleConfigItem(j["Misc"]["fakeLag"], handle, &Settings::Misc::fakeLag, false);
			HandleConfigItem(j["Misc"]["fakeLagTicks"], handle, &Settings::Misc::fakeLagTicks, 1.f);
			HandleConfigItem(j["Misc"]["fakeLagKey"], handle, &Settings::Misc::fakeLagKey, KEY_NONE);
			HandleConfigItem(j["Misc"]["fakeLagKeyStyle"], handle, &Settings::Misc::fakeLagKeyStyle, 1);
			HandleConfigItem(j["Misc"]["zoom"], handle, &Settings::Misc::zoom, false);
			HandleConfigItem(j["Misc"]["zoomKey"], handle, &Settings::Misc::zoomKey, KEY_NONE);
			HandleConfigItem(j["Misc"]["zoomKeyStyle"], handle, &Settings::Misc::zoomKeyStyle, 1);
			HandleConfigItem(j["Misc"]["zoomFOV"], handle, &Settings::Misc::zoomFOV, 90.f);
			HandleConfigItem(j["Misc"]["svCheats"], handle, &Settings::Misc::svCheats, false);
			HandleConfigItem(j["Misc"]["svAllowCsLua"], handle, &Settings::Misc::svAllowCsLua, false);
			HandleConfigItem(j["Misc"]["rainbowSpeed"], handle, &Settings::Misc::rainbowSpeed, 1.f);
			HandleConfigItem(j["Misc"]["scriptDumper"], handle, &Settings::Misc::scriptDumper, false);
			HandleConfigC(j["Misc"]["crossHairColor"], handle, Settings::Misc::crossHairColor, Color(255, 255, 255));

			HandleConfigItem(j["Triggerbot"]["triggerbot"], handle, &Settings::Triggerbot::triggerbot, false);
			HandleConfigItem(j["Triggerbot"]["triggerbotHead"], handle, &Settings::Triggerbot::triggerbotHead, false);
			HandleConfigItem(j["Triggerbot"]["triggerbotChest"], handle, &Settings::Triggerbot::triggerbotChest, false);
			HandleConfigItem(j["Triggerbot"]["triggerbotStomach"], handle, &Settings::Triggerbot::triggerbotStomach, false);
			HandleConfigItem(j["Triggerbot"]["triggerbotFastShoot"], handle, &Settings::Triggerbot::triggerbotFastShoot, false);
		}
		catch (...)
		{
			_HandleConfig(configName, configHandle::Save);
			return _HandleConfig(configName, configHandle::Load);
		}
		if (handle == configHandle::Save)
		{
			std::ofstream o(std::string("C:\\GMOD-SDK-Settings\\") + configName);
			if (o.bad())return;
			o << std::setw(4) << j << std::endl;
		}
	}

	// Why make this in two separate functions? Because oyu cannot use __try in functions that require object unwinding...
	void HandleConfig(const char* configName, configHandle handle) {
		__try {
			_HandleConfig(configName, handle);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			_HandleConfig(configName, configHandle::Save);
			return _HandleConfig(configName, configHandle::Load);
		}
	}
}
