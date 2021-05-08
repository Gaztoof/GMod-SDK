#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "globals.h"

const char* items[] = {
    ("Players"),
    ("Ragdolls"),
    ("Weapons"),
    ("NPCs"),
};
const char* chamsMaterials[] =
{
    "Normal",
    "Flat",
};

void DrawVisuals()
{
    if (!visualsOpen) return;

    if (!styleSingleWindow)
        ImGui::Begin(("Visuals"), &visualsOpen, ImGuiWindowFlags_NoResize);

    ImGui::Text(("Chams"));
    static int currItem = 0;
    chamsSetting* chamsSetting = nullptr;
    switch (currItem)
    {
    case 0: chamsSetting = &playerChamsSettings; break;
    case 1: chamsSetting = &ragdollChamsSettings; break;
    case 2: chamsSetting = &weaponChamsSettings; break;
    case 3: chamsSetting = &npcChamsSettings; break;
    }
    ImGui::ListBox("", &currItem, items, IM_ARRAYSIZE(items), 6);

    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::Text("Chams");
    ImGui::Checkbox(("Enable Visible"), &chamsSetting->enableVisible); ImGui::SameLine(150);
    ImGui::Checkbox(("Enable Hidden"), &chamsSetting->enableHidden);

    static int currVisibleMaterial = 0;
    static int currHiddenMaterial = 0;
    ImGui::Combo("##COMBO__VISIBLECHAMSMATERIAL", &currVisibleMaterial, chamsMaterials, ARRAYSIZE(chamsMaterials)); ImGui::SameLine(); ImGui::Text("Visible Material"); 
    ImGui::Combo("##COMBO__HIDDENCHAMSMATERIAL", &currHiddenMaterial, chamsMaterials, ARRAYSIZE(chamsMaterials)); ImGui::SameLine(); ImGui::Text("Hidden Material");
    chamsSetting->visibleMaterial = currVisibleMaterial;
    chamsSetting->hiddenMaterial = currHiddenMaterial;
    
    ImGui::ColorEdit3(("Visible Color"), chamsSetting->visibleColor.fCol);
    ImGui::ColorEdit3(("Hidden Color"), chamsSetting->hiddenColor.fCol);
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Text("Misc");

    ImGui::ColorEdit3(("World Color"), worldColor.fCol);

    ImGui::SliderFloat(("FOV"), &fov, 40.f, 150.f);
    ImGui::SliderFloat(("ViewModel FOV"), &viewModelFOV, 40.f, 150.f);

    ImGui::Checkbox("Disable SkyBox NOTWOKRING", &disableSkyBox);
    ImGui::Checkbox("Hide Hands", &hideHands);

    if (!styleSingleWindow)ImGui::End();
}