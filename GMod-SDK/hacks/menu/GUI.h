#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <map>
#include <algorithm>

#include "../../ImGui/imgui.h"
#include "../../ImGui/imgui_impl_dx9.h"
#include "../../ImGui/imgui_impl_win32.h"
#include "../../globals.hpp"
#include "MenuControls.h"
#include "../../hacks/ConfigSystem.h"
#include "../../hacks/Executor.h"
#include "../../hooks/RunStringEx.h"
#include "../../hooks/ProcessGMODServerToClient.h"
#include "../../hooks/RunCommand.h"
#include "../../hooks/Paint.h"

extern _Present oPresent;
#ifdef _DEBUG
extern ImFont* executorFont;
#endif

namespace GUI
{
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
		"Legit",
		"Config1",
		"Config2",
		"Config3",
		"Config4",
		"Config5",
	};
	const char* hitmarkerSound[]{
		"Metal",
		"Skeet",
		"Bell",
	};
	const char* autostrafeStyle[]{
		"Normal",
		"Silent strafe",
		"Optimizer(WIP)",
	};
	const char* executorLuaState[]{
		"Client",
		"Menu",
	};


	void DrawVisuals()
	{
		ImGuiStyle* style = &ImGui::GetStyle();
		Menu::InsertSpacer("Top Spacer");

		ImGui::Columns(2, NULL, false);
		{
			Menu::InsertGroupBoxLeft("Player ESP", 331.f);
			{
				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::CustomSpacing(9.f);

				// to do : activation hotkey

				Menu::InsertCheckbox("Bounding box", &Settings::ESP::espBoundingBox);
				Menu::InsertColorPicker("##Bounding box color", &Settings::ESP::espBoundingBoxColor, false);

				Menu::InsertCombo("Bounding Box Shape", &Settings::ESP::espShapeInt, espShape, IM_ARRAYSIZE(espShape));
				Menu::InsertCheckbox("Dormant", &Settings::ESP::espDormant);
				Menu::InsertCheckbox("Health", &Settings::ESP::espHealthBar);
				Menu::InsertColorPicker("##Health color", &Settings::ESP::espHealthColor, false);

				Menu::InsertCheckbox("Name", &Settings::ESP::espName);
				Menu::InsertColorPicker("##Name color", &Settings::ESP::espNameColor, false);

				Menu::InsertCheckbox("Weapon name", &Settings::ESP::weaponText);
				Menu::InsertColorPicker("##Weaponname color", &Settings::ESP::espWeaponColor, false);

				Menu::InsertCheckbox("Ammo", &Settings::ESP::weaponAmmo);
				Menu::InsertColorPicker("##Ammo color", &Settings::ESP::espAmmoColor, false);

				Menu::InsertCheckbox("Distance", &Settings::ESP::espDistance);
				Menu::InsertColorPicker("##Distance color", &Settings::ESP::espDistanceColor, false);

				Menu::InsertCombo("Infos emplacement", &Settings::ESP::infosEmplacement, plyInfoEmplacement, IM_ARRAYSIZE(plyInfoEmplacement));

				Menu::InsertCheckbox("Skeleton (can crash at roundstart)", &Settings::ESP::skeletonEsp);
				Menu::InsertColorPicker("##Skeleton color", &Settings::ESP::skeletonEspColor, false);
				Menu::InsertCheckbox("Detail skeleton", &Settings::ESP::skeletonDetails);

				Menu::InsertCheckbox("Entity ESP", &Settings::ESP::entEsp);

				Menu::InsertCheckbox("Only Friends", &Settings::ESP::onlyFriends);

				style->ItemSpacing = ImVec2(0, 0);
				style->WindowPadding = ImVec2(6, 6);

			} Menu::InsertEndGroupBoxLeft("Player ESP Cover", "Player ESP");

			Menu::InsertSpacer("Player ESP - Chams");

			Menu::InsertGroupBoxLeft("Chams", 157.f); {

				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);

				Menu::InsertComboColor("Visible Enemy Material", &Settings::Chams::playerChamsSettings.visibleMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials) ,&Settings::Chams::playerChamsSettings.visibleColor, false);
				Menu::InsertComboColor("Hidden Enemy Material", &Settings::Chams::playerChamsSettings.hiddenMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials) ,&Settings::Chams::playerChamsSettings.hiddenColor, false);
				Menu::InsertComboColor("Visible Teammate Material", &Settings::Chams::teamMateSettings.visibleMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials), &Settings::Chams::teamMateSettings.visibleColor, false);
				Menu::InsertComboColor("Hidden Teammate Material", &Settings::Chams::teamMateSettings.hiddenMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials) ,&Settings::Chams::teamMateSettings.hiddenColor, false);

				Menu::InsertComboColor("Local player Material", &Settings::Chams::localPlayerChamsSettings.visibleMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials) ,&Settings::Chams::localPlayerChamsSettings.visibleColor, false);

				Menu::InsertComboColor("Ragdoll Material", &Settings::Chams::ragdollChamsSettings.visibleMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials) ,&Settings::Chams::ragdollChamsSettings.visibleColor, false);
				Menu::InsertComboColor("NPC Material", &Settings::Chams::npcChamsSettings.visibleMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials) , &Settings::Chams::npcChamsSettings.visibleColor, false);
				Menu::InsertComboColor("Weapon Material", &Settings::Chams::weaponChamsSettings.visibleMaterial, chamsMaterials, IM_ARRAYSIZE(chamsMaterials), &Settings::Chams::weaponChamsSettings.visibleColor, false);


				style->ItemSpacing = ImVec2(0, 0);
				style->WindowPadding = ImVec2(6, 6);

			} Menu::InsertEndGroupBoxLeft("Chams Cover", "Chams");
		}
		ImGui::NextColumn();
		{
			Menu::InsertGroupBoxRight("Other ESP", 289.f); {

				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::CustomSpacing(9.f);

				Menu::InsertCheckbox("Crosshair", &Settings::Misc::drawCrosshair);
				Menu::InsertColorPicker("##Crosshair color", &Settings::Misc::crossHairColor, false);

				Menu::InsertSlider("Crosshair Size", &Settings::Misc::crosshairSize, 1, 20);
				Menu::InsertCheckbox("Spectators", &Settings::Misc::drawSpectators);

				Menu::InsertCheckbox("Enabled FOV", &Settings::Visuals::fovEnabled);
				Menu::InsertSlider("FOV", &Settings::Visuals::fov, 30, 150);
				Menu::InsertSlider("ViewModel FOV", &Settings::Visuals::viewModelFOV, 30, 150);

				Menu::InsertCheckbox("Zoom", &Settings::Misc::zoom);
				ImGui::Keybind("zoomkey", (int*)&Settings::Misc::zoomKey, &Settings::Misc::zoomKeyStyle);
				Menu::InsertSlider("Zoom FOV", &Settings::Misc::zoomFOV, 10.f, 90.f);

				style->ItemSpacing = ImVec2(0, 0);
				style->WindowPadding = ImVec2(6, 6);

			} Menu::InsertEndGroupBoxRight("Other ESP Cover", "Other ESP");

			Menu::InsertSpacer("Other ESP - Effects Spacer");

			Menu::InsertGroupBoxRight("Effects", 199.f); {

				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::CustomSpacing(9.f);

				Menu::InsertCheckbox("Remove skybox", &Settings::Visuals::disableSkyBox);

				Menu::InsertCheckbox("Change world color", &Settings::Visuals::changeWorldColor);
				Menu::InsertColorPicker("##World Color", &Settings::Visuals::worldColor, true);

				Menu::InsertCheckbox("Remove visual recoil", &Settings::Visuals::noVisualRecoil);
				Menu::InsertCheckbox("Remove hands", &Settings::Misc::removeHands);

				Menu::InsertCheckbox("Third person", &Settings::Misc::thirdperson);
				ImGui::Keybind("thirdpersonkey", (int*)&Settings::Misc::thirdpersonKey, &Settings::Misc::thirdpersonKeyStyle);
				Menu::InsertSlider("Third person distance", &Settings::Misc::thirdpersonDistance, 20, 1000);

				Menu::InsertCheckbox("Full Bright", &Settings::Visuals::fullBright);

				style->ItemSpacing = ImVec2(0, 0);
				style->WindowPadding = ImVec2(6, 6);

			} Menu::InsertEndGroupBoxRight("Effects Cover", "Effects");
		}
	}

	void DrawAimbot() {
		ImGuiStyle* style = &ImGui::GetStyle();
		Menu::InsertSpacer("Top Spacer");

		ImGui::Columns(2, NULL, false);
		{
			Menu::InsertGroupBoxLeft("Aimbot", 331.f);
			{
				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::CustomSpacing(9.f);

				Menu::InsertCheckbox("Enabled", &Settings::Aimbot::enableAimbot);
				ImGui::Keybind("aimbotkey", (int*)&Settings::Aimbot::aimbotKey, &Settings::Aimbot::aimbotKeyStyle);

				Menu::InsertCombo("Target selection", &Settings::Aimbot::aimbotSelection, targetSelection, IM_ARRAYSIZE(targetSelection));

				Menu::InsertCombo("Hitbox", &Settings::Aimbot::aimbotHitbox, aimbotHitboxText, IM_ARRAYSIZE(aimbotHitboxText));

				Menu::InsertCheckbox("Auto fire", &Settings::Aimbot::aimbotAutoFire);
				Menu::InsertCheckbox("Auto wall", &Settings::Aimbot::aimbotAutoWall);
				Menu::InsertCheckbox("Silent aim", &Settings::Aimbot::silentAim);
				Menu::InsertCheckbox("Smoothing", &Settings::Aimbot::smoothing);
				Menu::InsertSlider("Smoothing Steps", &Settings::Aimbot::smoothSteps, 10, 50);

				Menu::InsertCheckbox("Aim lock", &Settings::Aimbot::lockOnTarget);
				Menu::InsertCheckbox("Target teammates", &Settings::Aimbot::aimAtTeammates);
				Menu::InsertCheckbox("Target friends", &Settings::Aimbot::aimAtFriends);
				Menu::InsertCheckbox("Only target friends", &Settings::Aimbot::onlyAimAtFriends);
				Menu::InsertCheckbox("Fast shoot", &Settings::Aimbot::pistolFastShoot);

				Menu::InsertSlider("Minimum damage", &Settings::Aimbot::aimbotMinDmg, 1, 100);

				Menu::InsertCheckbox("Check FOV", &Settings::Aimbot::aimbotFovEnabled);
				Menu::InsertSlider("Aimbot FOV", &Settings::Aimbot::aimbotFOV, 5, 720);
				Menu::InsertCheckbox("Draw FOV Circle", &Settings::Aimbot::drawAimbotFov);
				Menu::InsertColorPicker("##FOV Circle Color", &Settings::Aimbot::fovColor, false);
				Menu::InsertCheckbox("Draw FOV Headlines (can crash at roundstart)", &Settings::Aimbot::drawAimbotHeadlines);

				style->ItemSpacing = ImVec2(0, 0);
				style->WindowPadding = ImVec2(6, 6);

			} Menu::InsertEndGroupBoxLeft("Aimbot Cover", "Aimbot");

			Menu::InsertSpacer("Aimbot - Triggerbot");

			Menu::InsertGroupBoxLeft("Triggerbot", 157.f);
			{
				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::CustomSpacing(9.f);

				Menu::InsertCheckbox("Triggerbot", &Settings::Triggerbot::triggerBot);
				Menu::InsertCheckbox("Head", &Settings::Triggerbot::triggerBotHead);
				Menu::InsertCheckbox("Chest", &Settings::Triggerbot::triggerBotChest);
				Menu::InsertCheckbox("Stomach", &Settings::Triggerbot::triggerBotStomach);
				Menu::InsertCheckbox("Fast Shoot", &Settings::Triggerbot::triggerbotFastShoot);

				style->ItemSpacing = ImVec2(0, 0);
				style->WindowPadding = ImVec2(6, 6);

			} Menu::InsertEndGroupBoxRight("Triggerbot Cover", "Triggerbot");

			ImGui::NextColumn();

			Menu::InsertGroupBoxRight("Other", 289.f);
			{
				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::CustomSpacing(9.f);

				Menu::InsertCheckbox("Remove spread", &Settings::Misc::noSpread);
				Menu::InsertCheckbox("Remove recoil", &Settings::Misc::noRecoil);
				Menu::InsertCheckbox("Fake-Lag", &Settings::Misc::fakeLag);
				ImGui::Keybind("fakelagkey", (int*)&Settings::Misc::fakeLagKey, &Settings::Misc::fakeLagKeyStyle);
				Menu::InsertSlider("Fake-Lag ticks", &Settings::Misc::fakeLagTicks, 1, 16);

				style->ItemSpacing = ImVec2(0, 0);
				style->WindowPadding = ImVec2(6, 6);

			} Menu::InsertEndGroupBoxRight("Other Cover", "Other");

			Menu::InsertSpacer("Aimbot - Anti-Aim");

			Menu::InsertGroupBoxRight("Anti-Aim", 199.f);
			{
				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::CustomSpacing(9.f);

				Menu::InsertCheckbox("Enabled", &Settings::AntiAim::enableAntiAim);
				ImGui::Keybind("antiaimkey", (int*)&Settings::AntiAim::antiAimKey, &Settings::AntiAim::antiAimKeyStyle);

				Menu::InsertCombo("Pitch", &Settings::AntiAim::currentAntiAimPitch, antiAimPitch, IM_ARRAYSIZE(antiAimPitch));
				Menu::InsertCombo("Yaw", &Settings::AntiAim::currentAntiAimYaw, antiAimYaw, IM_ARRAYSIZE(antiAimYaw));


				style->ItemSpacing = ImVec2(0, 0);
				style->WindowPadding = ImVec2(6, 6);

			} Menu::InsertEndGroupBoxRight("Anti-Aim Cover", "Anti-Aim");


		}
	}

	void DrawFilters() {

		ImGuiStyle* style = &ImGui::GetStyle();
		Menu::InsertSpacer("Top Spacer");

		ImGui::Columns(2, NULL, false); {
			Menu::InsertGroupBoxLeft("Players", 506.f);
			{
				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::SameLine(6.f);

				ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine();
				ImGui::SameLine(19.f);
				ImGui::Text("Friends");
				ImGui::PushItemWidth(158.f);
				ImGui::SameLine(19.f);
				if (ImGui::BeginGroupBox("Friends", ImVec2(258.f - 40.f, 415.f)))
				{
					if (ClientEntityList && EngineClient->IsInGame())
					{
						Settings::friendListMutex.lock();
						std::map<C_BasePlayer*, std::pair<bool, int>> tempFriendList;
						for (int i = 0; i < ClientEntityList->GetHighestEntityIndex(); i++)
						{
							C_BasePlayer* entity = (C_BasePlayer*)ClientEntityList->GetClientEntity(i);
							if (entity == nullptr || !entity->IsPlayer() || entity == localPlayer)
								continue;
							tempFriendList.emplace(entity, std::pair(false, i));
							auto found = Settings::friendList.find(entity);
							if (found == Settings::friendList.end())
								Settings::friendList.emplace(entity, std::pair(false, i));

						}

						std::vector<C_BasePlayer*> toRemoveMap;
						for (auto it = Settings::friendList.begin(); it != Settings::friendList.end(); it++)
						{
							bool toDelete = tempFriendList.find(it->first) == tempFriendList.end();
							if (!toDelete)
							{
								player_info_s info;
								EngineClient->GetPlayerInfo(it->second.second, &info);
								std::string name = "";
								name += info.name;
								name += " | ";
								name += info.guid;
								ImGui::Selectable(name.c_str(), &it->second.first);
							}
							bool listHas = std::find(Settings::selectedFriendList.begin(), Settings::selectedFriendList.end(), it->first) != Settings::selectedFriendList.end();
							if (!listHas && it->second.first)
							{
								Settings::selectedFriendList.push_back(it->first);
							}
							else if (listHas && !it->second.first)
							{
								std::remove(Settings::selectedFriendList.begin(), Settings::selectedFriendList.end(), it->first);
							}
							if (toDelete)
								toRemoveMap.push_back(it->first);
						}
						for (auto it = toRemoveMap.begin(); it != toRemoveMap.end(); it++)
						{
							Settings::friendList.erase(*it);
						}
						Settings::friendListMutex.unlock();
					}
					ImGui::EndGroupBox();
				}
				ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);

				bool resetAll = false;
				Menu::InsertButtonMiddle("Reset all", resetAll);
				if (resetAll)
				{
					Settings::friendListMutex.lock();
					for (std::map<C_BasePlayer*, std::pair<bool, int>>::iterator it = Settings::friendList.begin(); it != Settings::friendList.end();)
					{
						it->second.first = false;
						it++;
					}
					Settings::selectedFriendList.clear();
					Settings::friendListMutex.unlock();
				}
			}Menu::InsertEndGroupBoxLeft("Players Cover", "Players");
			ImGui::NextColumn();

			Menu::InsertGroupBoxRight("Entities", 506.f);
			{
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

						for (int i = 0; i < ClientEntityList->GetHighestEntityIndex(); i++)
						{
							C_BasePlayer* entity = (C_BasePlayer*)ClientEntityList->GetClientEntity(i);
							if (entity == nullptr || entity->IsPlayer() || !entity->UsesLua() || entity == localPlayer || entity->IsBaseCombatWeapon())
								continue;

							std::string entName = GetClassName(entity);
							if (!entName.length())continue;

							if (Settings::luaEntList.count(entName))
								continue;
							
							Settings::luaEntList.emplace(entName, false);
						}

						for (std::map<std::string, bool>::iterator it = Settings::luaEntList.begin(); it != Settings::luaEntList.end(); it++)
						{
							bool listHas = std::find(Settings::selectedLuaEntList.begin(), Settings::selectedLuaEntList.end(), it->first) != Settings::selectedLuaEntList.end();
							if (it->second && !listHas)
							{
								Settings::selectedLuaEntList.push_back(it->first);
							}
							else if (!it->second)
							{
								std::remove(Settings::selectedLuaEntList.begin(), Settings::selectedLuaEntList.end(), it->first);
							}

								ImGui::Selectable(it->first.c_str(), &it->second);
						}

						Settings::luaEntListMutex.unlock();
					}
					ImGui::EndGroupBox();
				}
				ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);

				bool resetAll = false;
				Menu::InsertButtonMiddle("Reset all", resetAll);
				if (resetAll)
				{
					Settings::luaEntListMutex.lock();
					Settings::luaEntList.clear();
					Settings::luaEntListMutex.unlock();
				}
			}Menu::InsertEndGroupBoxRight("Entities Cover", "Entities");
		}
	}

	void DrawMisc() {
		ImGuiStyle* style = &ImGui::GetStyle();
		Menu::InsertSpacer("Top Spacer");

		ImGui::Columns(2, NULL, false);
		{
			Menu::InsertGroupBoxLeft("Miscellaneous", 506.f);
			{
				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::CustomSpacing(9.f);

				Menu::InsertCheckbox("Hitmarker", &Settings::Misc::hitmarker);
				Menu::InsertSlider("Hitmarker size", &Settings::Misc::hitmarkerSize, 3.f, 20.f);
				Menu::InsertCheckbox("Hitmarker sound enabled", &Settings::Misc::hitmarkerSoundEnabled);
				Menu::InsertCombo("Hitmarker sound", &Settings::Misc::hitmarkerSound, hitmarkerSound, IM_ARRAYSIZE(hitmarkerSound));

				Menu::InsertCheckbox("Quick stop", &Settings::Misc::quickStop);

				Menu::InsertCheckbox("BunnyHop", &Settings::Misc::bunnyHop);
				Menu::InsertCheckbox("Autostrafe", &Settings::Misc::autoStrafe);
				Menu::InsertCombo("Autostrafe style", &Settings::Misc::autoStrafeStyle, autostrafeStyle, IM_ARRAYSIZE(autostrafeStyle));
				if (Settings::Misc::autoStrafeStyle == 2)
				{
					Menu::InsertCheckbox("Opti Autostrafe", &Settings::Misc::optiAutoStrafe);
					Menu::InsertCheckbox("Randomization(for anticheats)", &Settings::Misc::optiRandomization);
					Menu::InsertCheckbox("Static optimizer", &Settings::Misc::optiStyle);
					Menu::InsertCheckbox("Clamp optimizer angle", &Settings::Misc::optiClamp);
					Menu::InsertSlider("Optimizer strength", &Settings::Misc::optiStrength, 5.f, 100.f);
				}
				Menu::InsertCheckbox("Fast-Walk", &Settings::Misc::fastWalk);
				Menu::InsertCheckbox("Edge Jump", &Settings::Misc::edgeJump);

				Menu::InsertCheckbox("Message on death", &Settings::Misc::killMessage);
				Menu::InsertCheckbox("OOC?", &Settings::Misc::killMessageOOC);

				Menu::InsertCheckbox("Flashlight spam", &Settings::Misc::flashlightSpam);
				Menu::InsertCheckbox("Use spam", &Settings::Misc::useSpam);

				Menu::InsertCheckbox("Spectator List", &Settings::Misc::drawSpectators);

				Menu::InsertCheckbox("Free-cam", &Settings::Misc::freeCam);
				ImGui::Keybind("freecamkey", (int*)&Settings::Misc::freeCamKey, &Settings::Misc::freeCamKeyStyle);
				Menu::InsertSlider("Free-cam speed", &Settings::Misc::freeCamSpeed, 1.f, 5.f);


				Menu::InsertCheckbox("sv_cheats (unstable)", &Settings::Misc::svCheats);
				Menu::InsertCheckbox("sv_allowcslua (unstable)", &Settings::Misc::svAllowCsLua);

				Menu::InsertCheckbox("Clientside scripts dumper", &Settings::Misc::scriptDumper);

				style->ItemSpacing = ImVec2(0, 0);
				style->WindowPadding = ImVec2(6, 6);

			} Menu::InsertEndGroupBoxLeft("Misc Cover", "Miscellaneous");

			ImGui::NextColumn();

			Menu::InsertGroupBoxRight("Settings", 150.f);
			{
				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::CustomSpacing(9.f);

				Menu::InsertText("Menu key");
				ImGui::Keybind("menukey", (int*)&Settings::menuKey, &Settings::menuKeyStyle);
				Menu::InsertText("Menu color");
				Menu::InsertColorPicker("Menu color", &Settings::menuColor, false);
				Menu::InsertCheckbox("Untrusted", &Globals::Untrusted);
				Menu::InsertSlider("Rainbow speed", &Settings::Misc::rainbowSpeed, 1.f, 30.f);

				style->ItemSpacing = ImVec2(0, 0);
				style->WindowPadding = ImVec2(6, 6);

			} Menu::InsertEndGroupBoxRight("Settings Cover", "Settings");

			Menu::InsertSpacer("Settings - Configs");

			Menu::InsertGroupBoxRight("Configs", 200.f);
			{
				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::CustomSpacing(9.f);
				static int selectedConfig = 0;
				Menu::InsertComboMiddle("##Preset", &selectedConfig, configsNames, IM_ARRAYSIZE(configsNames));
				bool loadPressed = false;
				Menu::InsertButtonMiddle("Load", loadPressed);
				if (loadPressed)
					ConfigSystem::LoadConfig(configsNames[selectedConfig]);
				bool savePressed = false;
				Menu::InsertButtonMiddle("Save", savePressed);
				if (savePressed)
					ConfigSystem::SaveConfig(configsNames[selectedConfig]);

				bool resetPressed = false;
				Menu::InsertButtonMiddle("Reset", resetPressed);
				if (resetPressed)
					ConfigSystem::ResetConfig();


				style->ItemSpacing = ImVec2(0, 0);
				style->WindowPadding = ImVec2(6, 6);

			} Menu::InsertEndGroupBoxRight("Configs Cover", "Configs");
			Menu::InsertSpacer("Settings - Others");

			Menu::InsertGroupBoxRight("Others", 120.f);
			{
				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::CustomSpacing(9.f);

				bool unloadPressed = false;
				Menu::InsertButtonMiddle("Unload", unloadPressed);
				if (unloadPressed)
				{
					GameEventManager->RemoveListener((IGameEventListener2*)Globals::damageEvent);
					GameEventManager->RemoveListener((IGameEventListener2*)Globals::deathEvent);

					if (spoofedAllowCsLua)
						spoofedAllowCsLua->~SpoofedConVar();
					if (spoofedCheats)
						spoofedCheats->~SpoofedConVar();

					RestoreVMTHook((PVOID**)ClientMode, (PVOID)oCreateMove, 21);
					RestoreVMTHook((PVOID**)CHLclient, oFrameStageNotify, 35);
					RestoreVMTHook((PVOID**)ViewRender, (PVOID)oRenderView, 6);
					RestoreVMTHook((PVOID**)PanelWrapper, (PVOID)oPaintTraverse, 41);

					RestoreVMTHook((PVOID**)ModelRender, (PVOID)oDrawModelExecute, 20);

					RestoreVMTHook((PVOID**)LuaShared, (PVOID)oCreateLuaInterfaceFn, 4);
					RestoreVMTHook((PVOID**)LuaShared, (PVOID)oCloseLuaInterfaceFn, 5);
					
					RestoreVMTHook((PVOID**)ClientState, (PVOID)oProcessGMOD_ServerToClient, 111);
					RestoreVMTHook((PVOID**)Prediction, (PVOID)oRunCommand, 17);
					RestoreVMTHook((PVOID**)EngineVGui, (PVOID)oPaint, 13);

					*Globals::bSendpacket = true;
					
#ifdef _WIN64
					* (char**)(present) = (char*)(oPresent);
#else
					** (char***)(present) = (char*)oPresent;
#endif
					InputSystem->EnableInput(true);
					PanelWrapper->SetKeyBoardInputEnabled(Globals::lastPanelIdentifier, false);
					PanelWrapper->SetMouseInputEnabled(Globals::lastPanelIdentifier, false);

					Globals::openMenu = false;

#if _DEBUG
					FreeConsole();
#endif
					ConPrint("Successfully unloaded!", Color(0, 255, 0));

				}
				style->ItemSpacing = ImVec2(0, 0);
				style->WindowPadding = ImVec2(6, 6);

			} Menu::InsertEndGroupBoxRight("Others Cover", "Others");


		}
	}

	void DrawLua() {
		ImGuiStyle* style = &ImGui::GetStyle();
		Menu::InsertSpacer("Top Spacer");

		ImGui::Columns(1, NULL, false);
		{
			Menu::InsertGroupBoxLarge("Lua Executor", 506.f);
			{
				style->ItemSpacing = ImVec2(4, 2);
				style->WindowPadding = ImVec2(4, 4);
				ImGui::CustomSpacing(9.f);

				ImGui::SameLine(6.f);
				ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImColor(24, 24, 24);
#ifdef _DEBUG
				ImGui::PushFont(executorFont);
#endif
				Menu::InsertMultiTextInput("##Script input", Settings::ScriptInput, IM_ARRAYSIZE(Settings::ScriptInput), 487.f, 415.f);
#ifdef _DEBUG
				ImGui::PopFont();
#endif
				bool executePressed = false;
				Menu::InsertButtonLeft("Execute script", executePressed);
				if (executePressed)
				{
					std::thread(ExecuteScript, Settings::ScriptInput).detach();
				}
				bool buttonPressed = false;
				Menu::InsertButtonSameline("Load from file", buttonPressed);
				if (buttonPressed)
				{
					std::thread(LoadScriptFromFile).detach();
				}
				ImGui::SameLine(345.f); ImGui::PushItemWidth(158.f); ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f); ImGui::Combo("Lua State", &Globals::executeState, executorLuaState, IM_ARRAYSIZE(executorLuaState)); ImGui::PopItemWidth();

			}Menu::InsertEndGroupBoxLarge("Lua Executor Cover", "Lua Executor");
		}
	}
}