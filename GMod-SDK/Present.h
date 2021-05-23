#pragma once

#include <Windows.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "globals.h"
#include "GUI.h"
#include "drawing.h"
#include "ESP.h"
#include "MenuControls.h"
#include "MenuBackground.h"
#include "Fonts.h"

#ifndef GWL_WNDPROC
#define GWL_WNDPROC GWLP_WNDPROC
#endif
IMGUI_IMPL_API LRESULT  ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

_Present oPresent;
WNDPROC oWndProc;
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (Settings::openMenu) {
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

ImFont* menuFont;
ImFont* boldMenuFont;
ImFont* tabFont;
ImFont* massiveFont;

ImGuiStyle* style;
IDirect3DTexture9* menuBg;

HRESULT __stdcall hkPresent(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	static bool initialized = false;
	if (!initialized)
	{
		EngineClient->GetScreenSize(screenWidth, screenHeight);
		InitRenderer(pDevice);

		ImGui::CreateContext();

		HWND window = FindWindowA("Valve001", nullptr);
		oWndProc = (WNDPROC)SetWindowLongPtrA(window, GWL_WNDPROC, (LONG_PTR)WndProc);

		IDirect3DSwapChain9* pChain = nullptr;
		D3DPRESENT_PARAMETERS pp = {};
		D3DDEVICE_CREATION_PARAMETERS param = {};
		pDevice->GetCreationParameters(&param);
		pDevice->GetSwapChain(0, &pChain);
		if (pChain)
			pChain->GetPresentParameters(&pp);

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX9_Init(pDevice);

		D3DXCreateTextureFromFileInMemoryEx( pDevice, menuBackground, sizeof(menuBackground), 4096, 4096, D3DX_DEFAULT, NULL, pp.BackBufferFormat, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, NULL, &menuBg);

		style = &ImGui::GetStyle();
		ImGuiIO& io = ImGui::GetIO();

		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		menuFont = io.Fonts->AddFontFromMemoryTTF((void*)verdanaBytes, sizeof(verdanaBytes), 11);
		boldMenuFont = io.Fonts->AddFontFromMemoryTTF((void*)verdanaBoldBytes, sizeof(verdanaBoldBytes), 11);
		massiveFont = io.Fonts->AddFontFromMemoryTTF((void*)verdanaBoldBytes, sizeof(verdanaBoldBytes), 34);
		tabFont = io.Fonts->AddFontFromMemoryTTF((void*)rawTabBytes, sizeof(rawTabBytes), 42);

		initialized = true;
	}
	bool tempState = GetAsyncKeyState(InputSystem->ButtonCodeToVirtualKey(Settings::menuKey));
	
	static bool lastState = false;
	if (tempState != lastState && tempState)
		Settings::openMenu = !Settings::openMenu;
	lastState = tempState;

	if (EngineClient->IsInGame())
	{
		doEsp();

		if (Settings::Aimbot::drawAimbotFov)
		{
			DrawCircle(Vector(screenWidth / 2, screenHeight / 2, 0), Settings::Aimbot::aimbotFOV, Settings::Aimbot::aimbotFOV, 0xFFFFFFFF);
		}
		if (Settings::Misc::drawCrosshair) {
			DrawLine(Vector(screenWidth / 2 - Settings::Misc::crosshairSize, screenHeight / 2, 0), Vector(screenWidth / 2 + Settings::Misc::crosshairSize, screenHeight / 2, 0), 0xFFFFFFFF);
			DrawLine(Vector(screenWidth / 2, screenHeight / 2 - Settings::Misc::crosshairSize, 0), Vector(screenWidth / 2, screenHeight / 2 + Settings::Misc::crosshairSize, 0), 0xFFFFFFFF);
		}
		if ((Settings::lastHitmarkerTime + 0.08f) > EngineClient->Time() && Settings::Misc::hitmarker)
		{
			DrawLine(Vector(screenWidth / 2 - 2, screenHeight / 2 - 2, 0), Vector(screenWidth / 2 - Settings::Misc::hitmarkerSize, screenHeight / 2 - Settings::Misc::hitmarkerSize, 0), 0xFFFFFFFF);
			DrawLine(Vector(screenWidth / 2 + 2, screenHeight / 2 - 2, 0), Vector(screenWidth / 2 + Settings::Misc::hitmarkerSize, screenHeight / 2 - Settings::Misc::hitmarkerSize, 0), 0xFFFFFFFF);

			DrawLine(Vector(screenWidth / 2 - 2, screenHeight / 2 + 2, 0), Vector(screenWidth / 2 - Settings::Misc::hitmarkerSize, screenHeight / 2 + Settings::Misc::hitmarkerSize, 0), 0xFFFFFFFF);
			DrawLine(Vector(screenWidth / 2 + 2, screenHeight / 2 + 2, 0), Vector(screenWidth / 2 + Settings::Misc::hitmarkerSize, screenHeight / 2 + Settings::Misc::hitmarkerSize, 0), 0xFFFFFFFF);
		}
	}
	// https://www.unknowncheatsme/forum/3137288-post2.html Thanks to him :)
	// If you don't do that, the color of the menu will match to VGUI's.
	DWORD colorwrite, srgbwrite;
	pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwrite);
	pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &srgbwrite);

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

	ImGui::GetIO().MouseDrawCursor = Settings::openMenu;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImColor(9, 8, 9,255);

	ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
	ImGui::SetNextWindowSize(ImVec2(143.f, 34.f));
	ImGui::BeginMenuBackground("Credits window", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
	{
		ImGui::ColorBar("rainbowBar2", ImVec2(55.f, 2.f));
		style->ItemSpacing = ImVec2(4, 2);
		style->WindowPadding = ImVec2(4, 4);
		ImGui::NewLine();
		ImGui::SameLine(15.f);
		ImGui::Text("Coded by t.me/Gaztoof");
	}
	ImGui::End();
	
	/*// GOD I KNOW I SHOULDN'T DO THAT ITS AWFUL.
	static char* _SetCursorPos = (char*)GetProcAddress(GetModuleHandleA("user32.dll"), "SetCursorPos");
	// if menu is open, and setcursorpos is real, make it a ret
	if (Settings::openMenu && (*_SetCursorPos == '\xE9'))
		BytePatch(_SetCursorPos, 0xC3);
	else if ((*_SetCursorPos == '\xC3') && !Settings::openMenu) // if menu is closed, and setcursorpos is a ret, make it a jmp as it originally is
		BytePatch(_SetCursorPos, 0xE9);*/
	

	if (Settings::openMenu)
	{
		static int tab = 0;
		style->ScrollbarSize = 5.f;

		ImGui::SetNextWindowSize(ImVec2(660.f, 560.f));
		ImGui::BeginMenuBackground("Main Windows", &Settings::openMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar); 
		{
			ImGui::SameLine(6.f);
			ImGui::BeginChild("Complete Border", ImVec2(648.f, 550.f), false); {

				ImGui::Image(menuBg, ImVec2(648.f, 550.f));

			} ImGui::EndChild();

			ImGui::SameLine(6.f);

			ImGui::PushFont(menuFont);

			ImGui::BeginChild("Menu Contents", ImVec2(648.f, 548.f), false); {

				ImGui::ColorBar("rainbowBar1", ImVec2(648.f, 3.f));

				style->ItemSpacing = ImVec2(0.f, -1.f);

				ImGui::BeginTabs("Tabs", ImVec2(75.f, 542.f), false); {

					style->ItemSpacing = ImVec2(0.f, 0.f);

					style->ButtonTextAlign = ImVec2(0.5f, 0.47f);

					ImGui::PopFont();
					ImGui::PushFont(tabFont);

					ImGui::TabSpacer("##Top Spacer", ImVec2(75.f, 10.f));
					switch (tab) {

					case 0:
						if (ImGui::SelectedTab("A", ImVec2(75.f, 75.f))) tab = 0;
						if (ImGui::Tab("C", ImVec2(75.f, 75.f))) tab = 1;
						if (ImGui::Tab("D", ImVec2(75.f, 75.f))) tab = 2;
						if (ImGui::Tab("F", ImVec2(75.f, 75.f))) tab = 3;
						ImGui::PushFont(massiveFont);
						if (ImGui::Tab("LUA", ImVec2(75.f, 75.f))) tab = 4;
						ImGui::PopFont();
						ImGui::Tab("  ", ImVec2(75.f, 75.f));
						ImGui::Tab(" ", ImVec2(75.f, 75.f));
						break;
					case 1:

						if (ImGui::Tab("A", ImVec2(75.f, 75.f))) tab = 0;
						if (ImGui::SelectedTab("C", ImVec2(75.f, 75.f))) tab = 1;
						if (ImGui::Tab("D", ImVec2(75.f, 75.f))) tab = 2;
						if (ImGui::Tab("F", ImVec2(75.f, 75.f))) tab = 3;
						ImGui::PushFont(massiveFont);
						if (ImGui::Tab("LUA", ImVec2(75.f, 75.f))) tab = 4;
						ImGui::PopFont();
						ImGui::Tab("  ", ImVec2(75.f, 75.f));
						ImGui::Tab(" ", ImVec2(75.f, 75.f));
						break;
					case 2:
						if (ImGui::Tab("A", ImVec2(75.f, 75.f))) tab = 0;
						if (ImGui::Tab("C", ImVec2(75.f, 75.f))) tab = 1;
						if (ImGui::SelectedTab("D", ImVec2(75.f, 75.f))) tab = 2;
						if (ImGui::Tab("F", ImVec2(75.f, 75.f))) tab =3;
						ImGui::PushFont(massiveFont);
						if (ImGui::Tab("LUA", ImVec2(75.f, 75.f))) tab = 4;
						ImGui::PopFont();
						ImGui::Tab("  ", ImVec2(75.f, 75.f));
						ImGui::Tab(" ", ImVec2(75.f, 75.f));
						break;
					case 3:
						if (ImGui::Tab("A", ImVec2(75.f, 75.f))) tab = 0;
						if (ImGui::Tab("C", ImVec2(75.f, 75.f))) tab = 1;
						if (ImGui::Tab("D", ImVec2(75.f, 75.f))) tab = 2;
						if (ImGui::SelectedTab("F", ImVec2(75.f, 75.f))) tab = 3;
						ImGui::PushFont(massiveFont);
						if (ImGui::Tab("LUA", ImVec2(75.f, 75.f))) tab = 4;
						ImGui::PopFont();
						ImGui::Tab("  ", ImVec2(75.f, 75.f));
						ImGui::Tab(" ", ImVec2(75.f, 75.f));
						break;
					case 4:
						if (ImGui::Tab("A", ImVec2(75.f, 75.f))) tab = 0;
						if (ImGui::Tab("C", ImVec2(75.f, 75.f))) tab = 1;
						if (ImGui::Tab("D", ImVec2(75.f, 75.f))) tab = 2;
						if (ImGui::Tab("F", ImVec2(75.f, 75.f))) tab = 3;
						ImGui::PushFont(massiveFont);
						if (ImGui::SelectedTab("LUA", ImVec2(75.f, 75.f))) tab = 4;
						ImGui::PopFont();
						ImGui::Tab("  ", ImVec2(75.f, 75.f));
						ImGui::Tab(" ", ImVec2(75.f, 75.f));
						break;
					}
					ImGui::TabSpacer2("##Bottom Spacer", ImVec2(75.f, 7.f));
					ImGui::PopFont();
					style->ButtonTextAlign = ImVec2(0.5f, 0.5f);

				} ImGui::EndTabs();

				ImGui::SameLine(75.f);

				ImGui::PushFont(menuFont);
				ImGui::BeginChild("Tab Contents", ImVec2(572.f, 542.f), false); 
				{
					switch (tab) {

					case 0:
						DrawAimbot();
						break;
					case 1:
						DrawVisuals();
						break;
					case 2:
						DrawMisc();
						break;
					case 3:
						DrawFilters();
						break;
					case 4:
						DrawLua();
						break;
					}

					style->Colors[ImGuiCol_Border] = ImColor(10, 10, 10, 255);

				} ImGui::EndChild();

				style->ItemSpacing = ImVec2(4.f, 4.f);
				style->Colors[ImGuiCol_ChildBg] = ImColor(17, 17, 17, 255);

			} ImGui::EndChild();
			ImGui::PopFont();
		}
		ImGui::End();
	}
	localPlayer = (C_BasePlayer*)ClientEntityList->GetClientEntity(EngineClient->GetLocalPlayer());
	SpectatorList();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, colorwrite);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, srgbwrite);

	return oPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}
