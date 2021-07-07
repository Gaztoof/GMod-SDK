#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include "../../ImGui/imgui.h"
#include "../../ImGui/imgui_impl_dx9.h"
#include "../../ImGui/imgui_impl_win32.h"
#include "../../globals.hpp"
#include "MenuControls.h"
#include "../../hacks/ConfigSystem.h"
#include "../../hacks/Executor.h"

const char* items[] = {
    ("Players"),
    ("Ragdolls"),
    ("Weapons"),
    ("NPCs"),
};
const char* chamsMaterials[] =
{
    "Normal",
    "Textured",
    "Flat",
};
const char* antiAimPitch[] =
{
    "None",
    "Fake Down",
    "Fake Up",
    "Jitter",
};
const char* antiAimYaw[] =
{
    "None",
    "Fast Spin",
    "Slow Spin",
    "Back Jitter",
    "Inverse",
	"Fake Sideways",
};

const char* targetSelection[] =
{
	"Distance",
	"Health",
	"FOV",
};
const char* aimbotHitboxText[] =
{
	"Head",
	"Chest",
	"Stomach",
};
const char* espShape[] = {

	"2D",
	"3D",
};
const char* plyInfoEmplacement[] = {

	"Above",
	"Below",
	"Right",
	"Left",
};
const char* configsNames[]{
	"Default",
	"HvH",
	"Legit"
	"Config1",
	"Config2",
	"Config3",
};
const char* hitmarkerSound[]{
	"Metal",
	"Skeet",
	"Bell",	
};
const char* autostrafeStyle[]{
	"Normal",
	"Silent strafe",
	"Rage"
};


void DrawVisuals()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Player ESP", 331.f); {

			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			// to do : activation hotkey

			InsertCheckbox("Bounding box", Settings::ESP::espBoundingBox);
			InsertColorPicker("##Bounding box color", Settings::ESP::espBoundingBoxColor.fCol, false);

			InsertCombo("Bouding Box Shape", Settings::ESP::espShapeInt, espShape);
			InsertCheckbox("Dormant", Settings::ESP::espDormant);
			InsertCheckbox("Health", Settings::ESP::espHealthBar);

			InsertCheckbox("Name", Settings::ESP::espName);

			InsertCheckbox("Weapon name", Settings::ESP::weaponText);

			InsertCheckbox("Ammo", Settings::ESP::weaponAmmo);

			InsertCheckbox("Distance", Settings::ESP::espDistance);

			InsertCombo("Infos emplacement", Settings::ESP::infosEmplacement, plyInfoEmplacement);

			InsertCheckbox("Skeleton (can crash at roundstart)", Settings::ESP::skeletonEsp);
			InsertColorPicker("##Skeleton color", Settings::ESP::skeletonEspColor.fCol, false);
			InsertCheckbox("Detail skeleton", Settings::ESP::skeletonDetails);

			InsertCheckbox("Entity ESP", Settings::ESP::entEsp);

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxLeft("Player ESP Cover", "Player ESP");

		InsertSpacer("Player ESP - Chams");

		InsertGroupBoxLeft("Chams", 157.f); {

			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);

			InsertComboColor("Visible Enemy Material", Settings::Chams::playerChamsSettings.visibleMaterial, chamsMaterials, Settings::Chams::playerChamsSettings.visibleColor.fCol, false);
			InsertComboColor("Hidden Enemy Material", Settings::Chams::playerChamsSettings.hiddenMaterial, chamsMaterials, Settings::Chams::playerChamsSettings.hiddenColor.fCol, false);
			InsertComboColor("Visible Teammate Material", Settings::Chams::teamMateSettings.visibleMaterial, chamsMaterials, Settings::Chams::teamMateSettings.visibleColor.fCol, false);
			InsertComboColor("Hidden Teammate Material", Settings::Chams::teamMateSettings.hiddenMaterial, chamsMaterials, Settings::Chams::teamMateSettings.hiddenColor.fCol, false);

			InsertComboColor("Local player Material", Settings::Chams::localPlayerChamsSettings.visibleMaterial, chamsMaterials, Settings::Chams::localPlayerChamsSettings.visibleColor.fCol, false);

			InsertComboColor("Ragdoll Material", Settings::Chams::ragdollChamsSettings.visibleMaterial, chamsMaterials, Settings::Chams::ragdollChamsSettings.visibleColor.fCol, false);
			InsertComboColor("NPC Material", Settings::Chams::npcChamsSettings.visibleMaterial, chamsMaterials, Settings::Chams::npcChamsSettings.visibleColor.fCol, false);
			InsertComboColor("Weapon Material", Settings::Chams::weaponChamsSettings.visibleMaterial, chamsMaterials, Settings::Chams::weaponChamsSettings.visibleColor.fCol, false);
			

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxLeft("Chams Cover", "Chams");
	}
	ImGui::NextColumn(); {

		InsertGroupBoxRight("Other ESP", 289.f); {

			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			InsertCheckbox("Crosshair", Settings::Misc::drawCrosshair);
			InsertSlider("Crosshair Size", Settings::Misc::crosshairSize, 1, 20);
			InsertCheckbox("Spectators", Settings::Misc::drawSpectators);

			InsertSlider("FOV", Settings::Visuals::fov, 30, 150);
			InsertSlider("ViewModel FOV", Settings::Visuals::viewModelFOV, 30, 150);

			InsertCheckbox("Zoom", Settings::Misc::zoom);
			ImGui::Keybind("zoomkey", (int*)&Settings::Misc::zoomKey, &Settings::Misc::zoomKeyStyle);
			InsertSlider("Zoom FOV", Settings::Misc::zoomFOV, 10.f, 90.f);

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Other ESP Cover", "Other ESP");

		InsertSpacer("Other ESP - Effects Spacer");

		InsertGroupBoxRight("Effects", 199.f); {

			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			InsertCheckbox("Remove skybox", Settings::Visuals::disableSkyBox);

			InsertCheckbox("Change world color", Settings::Visuals::changeWorldColor);
			InsertColorPicker("##World Color", Settings::Visuals::worldColor.fCol, true);

			InsertCheckbox("Remove visual recoil", Settings::Visuals::noVisualRecoil);
			InsertCheckbox("Remove hands", Settings::Misc::removeHands);

			InsertCheckbox("Third person", Settings::Misc::thirdperson);
			ImGui::Keybind("thirdpersonkey", (int*)&Settings::Misc::thirdpersonKey, &Settings::Misc::thirdpersonKeyStyle);
			InsertSlider("Third person distance", Settings::Misc::thirdpersonDistance, 20, 1000);

			InsertCheckbox("Full Bright", Settings::Visuals::fullBright);

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Effects Cover", "Effects");
	}

}

void DrawAimbot() {
	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Aimbot", 331.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			InsertCheckbox("Enabled", Settings::Aimbot::enableAimbot);
			ImGui::Keybind("aimbotkey", (int*)&Settings::Aimbot::aimbotKey, &Settings::Aimbot::aimbotKeyStyle);

			InsertCombo("Target selection", Settings::Aimbot::aimbotSelection, targetSelection);

			InsertCombo("Hitbox", Settings::Aimbot::aimbotHitbox, aimbotHitboxText);

			InsertCheckbox("Auto fire", Settings::Aimbot::aimbotAutoFire);
			InsertCheckbox("Auto wall", Settings::Aimbot::aimbotAutoWall);
			InsertCheckbox("Silent aim", Settings::Aimbot::silentAim);
			InsertCheckbox("Aim lock", Settings::Aimbot::lockOnTarget);
			InsertCheckbox("Target teammates", Settings::Aimbot::aimAtTeammates);
			InsertCheckbox("Target friends", Settings::Aimbot::aimAtFriends);
			InsertCheckbox("Only target friends", Settings::Aimbot::onlyAimAtFriends);

			InsertSlider("Minimum damage", Settings::Aimbot::aimbotMinDmg, 1, 100);

			InsertCheckbox("Check FOV", Settings::Aimbot::aimbotFovEnabled);
			InsertSlider("FOV", Settings::Aimbot::aimbotFOV, 5, 720);
			InsertCheckbox("Draw FOV Circle", Settings::Aimbot::drawAimbotFov);
			InsertCheckbox("Draw FOV Headlines (can crash at roundstart)", Settings::Aimbot::drawAimbotHeadlines);

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxLeft("Aimbot Cover", "Aimbot");

		InsertSpacer("Aimbot - Triggerbot");

		InsertGroupBoxLeft("Triggerbot", 157.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			InsertCheckbox("Triggerbot", Settings::Triggerbot::triggerBot);
			InsertCheckbox("Head", Settings::Triggerbot::triggerBotHead);
			InsertCheckbox("Chest", Settings::Triggerbot::triggerBotChest);
			InsertCheckbox("Stomach", Settings::Triggerbot::triggerBotStomach);
			InsertCheckbox("Fast Shoot", Settings::Triggerbot::triggerbotFastShoot);

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Triggerbot Cover", "Triggerbot");

		ImGui::NextColumn();

		InsertGroupBoxRight("Other", 289.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			InsertCheckbox("Remove spread", Settings::Misc::noSpread);
			InsertCheckbox("Remove recoil", Settings::Misc::noRecoil);
			InsertCheckbox("Fake-Lag", Settings::Misc::fakeLag);
			ImGui::Keybind("fakelagkey", (int*)&Settings::Misc::fakeLagKey, &Settings::Misc::fakeLagKeyStyle);

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Other Cover", "Other");

		InsertSpacer("Aimbot - Anti-Aim");

		InsertGroupBoxRight("Anti-Aim", 199.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			InsertCheckbox("Enabled", Settings::AntiAim::enableAntiAim);
			ImGui::Keybind("antiaimkey", (int*)&Settings::AntiAim::antiAimKey, &Settings::AntiAim::antiAimKeyStyle);

			InsertCombo("Pitch", Settings::AntiAim::currentAntiAimPitch, antiAimPitch);
			InsertCombo("Yaw", Settings::AntiAim::currentAntiAimYaw, antiAimYaw);


			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Anti-Aim Cover", "Anti-Aim");


	}
}
#include <map>

void DrawFilters() {

	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {
		InsertGroupBoxLeft("Players", 506.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::SameLine(6.f);

			ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine();
			ImGui::SameLine(19.f); 
			ImGui::Text("Friends");
			ImGui::PushItemWidth(158.f);
			ImGui::SameLine(19.f);
			if(ImGui::BeginGroupBox("Friends", ImVec2(258.f-40.f, 415.f)))
			{
				if (ClientEntityList && EngineClient->IsInGame())
				{
					Settings::friendListMutex.lock();
					std::map<C_BasePlayer*, std::pair<bool, int>> tempFriendList;
					for (int i = 0; i < ClientEntityList->GetHighestEntityIndex(); i++)
					{
						C_BasePlayer* entity = (C_BasePlayer*)ClientEntityList->GetClientEntity(i);
						if (entity == nullptr || !entity->IsPlayer() || entity == localPlayer )
							continue;
						tempFriendList.emplace(entity, std::pair(false, i));
						auto found = Settings::friendList.find(entity);
						if (found == Settings::friendList.end())
							Settings::friendList.emplace(entity, std::pair(false, i));

					}
					for (std::map<C_BasePlayer*, std::pair<bool, int>>::iterator it = Settings::friendList.begin(); it != Settings::friendList.end();)
					{
						if (tempFriendList.find(it->first) == tempFriendList.end())
						{
							Settings::friendList.erase(it++);
						}
						else
						{
							player_info_s info;
							EngineClient->GetPlayerInfo(it->second.second, &info);
							std::string name = "";
							name += info.name;
							name += " | " ;
							name += info.guid;
							ImGui::Selectable(name.c_str(), &it->second.first);
							it++;
						}
					}
					Settings::friendListMutex.unlock();
				}
				ImGui::EndGroupBox();
			}
			ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);

			bool resetAll = false;
			InsertButtonMiddleV("Reset all", resetAll);
			if (resetAll)
			{
				for (std::map<C_BasePlayer*, std::pair<bool, int>>::iterator it = Settings::friendList.begin(); it != Settings::friendList.end();)
				{
					it->second.first = false;
					it++;
				}
			}
		}InsertEndGroupBoxLeft("Players Cover", "Players");
		ImGui::NextColumn();

		InsertGroupBoxRight("Entities", 506.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);

			ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine();
			ImGui::SameLine(19.f); 
			ImGui::Text("Entities");
			ImGui::PushItemWidth(158.f);
			ImGui::SameLine(19.f);
			if (ImGui::BeginGroupBox("Entities", ImVec2(258.f - 40.f, 415.f)))
			{
				if (ClientEntityList && EngineClient->IsInGame())
				{
					Settings::luaEntListMutex.lock();
					std::map<const char*, bool> tempEntList;
					for (int i = 0; i < ClientEntityList->GetHighestEntityIndex(); i++)
					{
						C_BasePlayer* entity = (C_BasePlayer*)ClientEntityList->GetClientEntity(i);
						if (entity == nullptr || entity->IsPlayer() || entity->IsWeapon() || !entity->UsesLua() || entity == localPlayer)
							continue;

						const char* entName = GetClassName(entity);
						if (!strlen(entName))continue;
						
						bool found = false;
						for (auto var : Settings::luaEntList)
							if (var.first && !strcmp(var.first, entName))
								found = true;
						if (!found)
							Settings::luaEntList.emplace(entName, false);
					}
					for (std::map<const char*, bool>::iterator it = Settings::luaEntList.begin(); it != Settings::luaEntList.end();)
					{
						bool found = false;
						for (auto var : Settings::luaEntList)
							if (var.first && !strcmp(var.first, it->first))
								found = true;

						if (!found)
						{
							Settings::luaEntList.erase(it++);
						}
						else
						{
							ImGui::Selectable(it->first, &it->second);
							it++;
						}
					}
					Settings::luaEntListMutex.unlock();
				}
				ImGui::EndGroupBox();
			}
			ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);

			bool resetAll = false;
			InsertButtonMiddleV("Reset all", resetAll);
			if (resetAll)
			{
				for (std::map<const char*, bool>::iterator it = Settings::luaEntList.begin(); it != Settings::luaEntList.end();)
				{
					it->second = false;
					it++;
				}
			}
		}InsertEndGroupBoxRight("Entities Cover", "Entities");
	}
}
void DrawMisc() {
	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {
		InsertGroupBoxLeft("Miscellaneous", 506.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			InsertCheckbox("Hitmarker", Settings::Misc::hitmarker);
			InsertSlider("Hitmarker size", Settings::Misc::hitmarkerSize, 3.f, 20.f);
			InsertCheckbox("Hitmarker sound enabled", Settings::Misc::hitmarkerSoundEnabled);
			InsertCombo("Hitmarker sound", Settings::Misc::hitmarkerSound, hitmarkerSound);

			InsertCheckbox("Quick stop", Settings::Misc::quickStop);

			InsertCheckbox("BunnyHop", Settings::Misc::bunnyHop);
			InsertCheckbox("Autostrafe", Settings::Misc::autoStrafe);
			InsertCombo("Autostrafe style", Settings::Misc::autoStrafeStyle, autostrafeStyle);

			InsertCheckbox("Message on death", Settings::Misc::killMessage);
			InsertCheckbox("OOC?", Settings::Misc::killMessageOOC);

			InsertCheckbox("Flashlight spam", Settings::Misc::flashlightSpam);
			InsertCheckbox("Use spam", Settings::Misc::useSpam);

			InsertCheckbox("Spectator List", Settings::Misc::drawSpectators);

			InsertCheckbox("Free-cam", Settings::Misc::freeCam);
			ImGui::Keybind("freecamkey", (int*)&Settings::Misc::freeCamKey, &Settings::Misc::freeCamKeyStyle);
			InsertSlider("Free-cam speed", Settings::Misc::freeCamSpeed, 1.f, 5.f);


			InsertCheckbox("sv_cheats ", Settings::Misc::svCheats);
			InsertCheckbox("sv_allowcslua ", Settings::Misc::svAllowCsLua);

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxLeft("Misc Cover", "Miscellaneous");

		ImGui::NextColumn();

		InsertGroupBoxRight("Settings", 150.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			InsertText("Menu key");
			ImGui::Keybind("menukey", (int*)&Settings::menuKey, &Settings::menuKeyStyle);
			InsertText("Menu color");
			InsertColorPicker("Menu color", Settings::menuColor.fCol, false);
			ImGui::GetStyle().Colors[ImGuiCol_MenuTheme].x = Settings::menuColor.fCol[0];
			ImGui::GetStyle().Colors[ImGuiCol_MenuTheme].y = Settings::menuColor.fCol[1];
			ImGui::GetStyle().Colors[ImGuiCol_MenuTheme].z = Settings::menuColor.fCol[2];
			InsertCheckbox("Untrusted", Settings::Untrusted);

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Settings Cover", "Settings");

		InsertSpacer("Settings - Configs");

		InsertGroupBoxRight("Configs", 200.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);
			static int selectedConfig = 0;
			InsertComboMiddle("##Preset", selectedConfig, configsNames);
			bool loadPressed = false;
			InsertButtonMiddleV("Load", loadPressed);
			if (loadPressed)
				ConfigSystem::LoadConfig(configsNames[selectedConfig]);
			bool savePressed = false;
			InsertButtonMiddleV("Save", savePressed);
			if (savePressed)
				ConfigSystem::SaveConfig(configsNames[selectedConfig]);

			bool resetPressed = false;
			InsertButtonMiddleV("Reset", resetPressed);
			if (resetPressed)
				ConfigSystem::ResetConfig();


			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Configs Cover", "Configs");
		InsertSpacer("Settings - Others");

		InsertGroupBoxRight("Others", 120.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			bool unloadPressed = false;
			InsertButtonMiddleV("Unload", unloadPressed);
			if (unloadPressed)
			{
				GameEventManager->RemoveListener((IGameEventListener2*)damageEvent);
				GameEventManager->RemoveListener((IGameEventListener2*)deathEvent);

				RestoreVMTHook((PVOID**)ClientMode, (PVOID)oCreateMove, 21);
				RestoreVMTHook((PVOID**)CHLclient, oFrameStageNotify, 35);
				RestoreVMTHook((PVOID**)ViewRender, (PVOID)oRenderView, 6);
				RestoreVMTHook((PVOID**)PanelWrapper, (PVOID)oPaintTraverse, 41);

				RestoreVMTHook((PVOID**)ModelRender, (PVOID)oDrawModelExecute, 20);
				*bSendpacket = true;

				extern _Present oPresent;
#ifdef _WIN64
				* (char**)(present) = (char*)(oPresent);
#else
				** (char***)(present) = (char*)oPresent;
#endif
				InputSystem->EnableInput(true);
				PanelWrapper->SetKeyBoardInputEnabled(Settings::lastPanelIdentifier, false);
				PanelWrapper->SetMouseInputEnabled(Settings::lastPanelIdentifier, false);

				Settings::openMenu = false;

			}
			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Others Cover", "Others");


	}
}

void DrawLua() {
	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(1, NULL, false); {
		InsertGroupBoxLarge("Lua Executor", 506.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			ImGui::SameLine(6.f);
			ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImColor(24, 24, 24);
			InsertMultiTextInput("##Script input", Settings::ScriptInput, 487.f, 415.f);

			bool executePressed = false;
			InsertButtonLeft("Execute script", executePressed);
			if (executePressed)
			{
				std::thread(ExecuteScript, Settings::ScriptInput).detach();
			}
			bool buttonPressed = false;
			InsertButtonSameline("Load from file", buttonPressed);
			if (buttonPressed)
			{
				std::thread(LoadScriptFromFile).detach();
			}

		}InsertEndGroupBoxLarge("Lua Executor Cover", "Lua Executor");
	}
}