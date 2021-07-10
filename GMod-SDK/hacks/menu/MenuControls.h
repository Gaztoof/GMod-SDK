#pragma once
#include "../../ImGui/imgui.h"

void ColorPicker(const char* name, Color *color, bool alpha) {

	ImGuiStyle* style = &ImGui::GetStyle();

	auto alphaSliderFlag = alpha ? ImGuiColorEditFlags_AlphaBar : ImGuiColorEditFlags_NoAlpha;

	ImGui::SameLine(219.f);
	ImGui::ColorEdit4(std::string{ "##" }.append(name).append("Picker").c_str(), color->fCol, alphaSliderFlag | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip, &color->rainbow);
}

#define InsertSpacer(x1) ImGui::BeginChild(x1, ImVec2(210.f, 18.f), false);  ImGui::EndChild(); 
#define InsertGroupboxSpacer(x1) ImGui::BeginChild(x1, ImVec2(210.f, 9.f), false);  ImGui::EndChild();
#define InsertGroupboxTitle(x1) ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(11.f); ImGui::GroupBoxTitle(x1);

#define InsertGroupBoxLeft(x1,x2) ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::BeginGroupBox(x1, ImVec2(258.f, x2), true);
#define InsertGroupBoxRight(x1,x2) ImGui::NewLine(); ImGui::SameLine(10.f); ImGui::BeginGroupBox(x1, ImVec2(258.f, x2), true);
#define InsertEndGroupBoxLeft(x1,x2) ImGui::EndGroupBox(); ImGui::SameLine(19.f); ImGui::BeginGroupBoxScroll(x1, x2, ImVec2(258.f, 11.f), true); ImGui::EndGroupBoxScroll();
#define InsertEndGroupBoxRight(x1,x2) ImGui::EndGroupBox(); ImGui::SameLine(10.f); ImGui::BeginGroupBoxScroll(x1, x2, ImVec2(258.f, 11.f), true); ImGui::EndGroupBoxScroll();

#define InsertGroupBoxLarge(x1,x2) ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::BeginGroupBox(x1, ImVec2(526.f, x2), true);
#define InsertEndGroupBoxLarge(x1,x2) ImGui::EndGroupBox(); ImGui::SameLine(19.f); ImGui::BeginGroupBoxScroll(x1, x2, ImVec2(526.f, 11.f), true); ImGui::EndGroupBoxScroll();

#define InsertGroupBoxTop(x1,x2) ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::BeginGroupBox(x1, x2, true);
#define InsertEndGroupBoxTop(x1,x2,x3) ImGui::EndGroupBox(); ImGui::SameLine(19.f); ImGui::BeginGroupBoxScroll(x1, x2, x3, true); ImGui::EndGroupBoxScroll();

#define InsertCheckbox(x1,x2) ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::Checkbox(x1, &x2);
#define InsertSlider(x1,x2,x3,x4,x5) ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(159.f); ImGui::SliderFloat(x1, &x2, x3, x4, x5); ImGui::PopItemWidth();
#define InsertSlider(x1,x2,x3,x4) ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::SliderFloat(x1, &x2, x3, x4, "%.f"); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);

#define InsertSliderWithoutText(x1,x2,x3,x4,x5) ImGui::Spacing(); ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(159.f); ImGui::SliderFloat(x1, &x2, x3, x4, x5); ImGui::PopItemWidth();
#define InsertCombo(x1,x2,x3) ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::Combo(x1, &x2, x3, IM_ARRAYSIZE(x3)); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
#define InsertComboMiddle(x1,x2,x3) ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(50.f); ImGui::PushItemWidth(158.f); ImGui::Combo(x1, &x2, x3, IM_ARRAYSIZE(x3)); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);

#define InsertComboColor(x1,x2,x3, x4, x5) ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::Combo(x1, &x2, x3, IM_ARRAYSIZE(x3)); ImGui::PopItemWidth(); ImGui::SameLine(1.f); ColorPicker(x1, &x4, x5);
#define InsertComboWithoutText(x1,x2,x3) ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::Combo(x1, &x2, x3, IM_ARRAYSIZE(x3)); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
#define InsertMultiCombo(x1,x2,x3,x4) ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::MultiCombo(x1, x2, x3, x4); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
#define InsertMultiComboWithoutText(x1,x2,x3,x4) ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::MultiCombo(x1, x2, x3, x4); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);

#define InsertButton(x1) ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::Button(x1, ImVec2(158.f,0)); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
#define InsertButtonLeft(x1, x2) ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::PushItemWidth(158.f); x2 = ImGui::Button(x1, ImVec2(158.f,0)); ImGui::PopItemWidth(); 

#define InsertButtonSameline(x1, x2) ImGui::SameLine(); ImGui::PushItemWidth(158.f); x2 = ImGui::Button(x1, ImVec2(158.f,0)); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);

#define InsertButtonMiddle(x1) ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(50.f); ImGui::PushItemWidth(158.f); ImGui::Button(x1, ImVec2(158.f,0)); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
#define InsertButtonMiddleV(x1, x2) ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(50.f); ImGui::PushItemWidth(158.f); x2 = ImGui::Button(x1, ImVec2(158.f,0)); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);

#define InsertText(x1) ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::Text(x1);
#define InsertMultiTextInput(x1, x2, x3, x4) ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::PushItemWidth(158.f); ImGui::InputTextMultiline(x1, x2, IM_ARRAYSIZE(x2), ImVec2(x3, x4), ImGuiInputTextFlags_AllowTabInput);ImGui::PopItemWidth();

#define InsertColorPicker(x1,x2,x3) ImGui::SameLine(219.f); ColorPicker(x1, &x2, x3);
#define InsertComboColorPicker(x1,x2,x3) ImGui::SameLine(1.f); ColorPicker(x1, &x2, x3);