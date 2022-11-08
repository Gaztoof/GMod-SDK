#pragma once
#include "../../ImGui/imgui.h"

void ColorPicker(const char* name, Color* color, bool alpha) {
	
	ImGuiStyle* style = &ImGui::GetStyle();
	auto alphaSliderFlag = alpha ? ImGuiColorEditFlags_AlphaBar : ImGuiColorEditFlags_NoAlpha;
	ImGui::SameLine(219.f);
	ImGui::ColorEdit4(std::string{ "##" }.append(name).append("Picker").c_str(), color->fCol, alphaSliderFlag | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip, &color->rainbow);
}


namespace Menu {
	const void InsertSpacer(const char* label) {
		ImGui::BeginChild(label, ImVec2(210.f, 18.f), false);  ImGui::EndChild();
	}
	const void InsertGroupboxSpacer(const char* label) {
		ImGui::BeginChild(label, ImVec2(210.f, 9.f), false);  ImGui::EndChild();
	}
	const void InsertGroupboxTitle(const char* label) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(11.f); ImGui::GroupBoxTitle(label);
	}

	const void InsertGroupBoxLeft(const char* label, float y) {
		ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::BeginGroupBox(label, ImVec2(258.f, y), true);
	}
	const void InsertGroupBoxRight(const char* label, float y) {
		ImGui::NewLine(); ImGui::SameLine(10.f); ImGui::BeginGroupBox(label, ImVec2(258.f, y), true);
	}
	const void InsertEndGroupBoxLeft(const char* label, const char* y) {
		ImGui::EndGroupBox(); ImGui::SameLine(19.f); ImGui::BeginGroupBoxScroll(label, y, ImVec2(258.f, 11.f), true); ImGui::EndGroupBoxScroll();
	}
	const void InsertEndGroupBoxRight(const char* label, const char* y) {
		ImGui::EndGroupBox(); ImGui::SameLine(10.f); ImGui::BeginGroupBoxScroll(label, y, ImVec2(258.f, 11.f), true); ImGui::EndGroupBoxScroll();
	}

	const void InsertGroupBoxLarge(const char* label, float y) {
		ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::BeginGroupBox(label, ImVec2(526.f, y), true);
	}
	const void InsertEndGroupBoxLarge(const char* label, const char* groupboxName) {
		ImGui::EndGroupBox(); ImGui::SameLine(19.f); ImGui::BeginGroupBoxScroll(label, groupboxName, ImVec2(526.f, 11.f), true); ImGui::EndGroupBoxScroll();
	}

	const void InsertGroupBoxTop(const char* label, ImVec2& size) {
		ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::BeginGroupBox(label, size, true);
	}
	const void InsertEndGroupBoxTop(const char* label, const char* groupboxName, ImVec2& size) {
		ImGui::EndGroupBox(); ImGui::SameLine(19.f); ImGui::BeginGroupBoxScroll(label, groupboxName, size, true); ImGui::EndGroupBoxScroll();
	}

	const void InsertCheckbox(const char* label, bool* button) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::Checkbox(label, button);
	}
	const void InsertSlider(const char* label, float* fl, float v_min, float v_max, const char* format = "%.f") {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(159.f); ImGui::SliderFloat(label, fl, v_min, v_max, format); ImGui::PopItemWidth();
	}

	const void InsertSliderWithoutText(const char* label, float *v, float v_min, float v_max, const char* format = "%.f")
	{
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::NewLine();
		ImGui::SameLine(42.f);
		ImGui::PushItemWidth(159.f);
		ImGui::SliderFloat(label, v, v_min, v_max, format);
		ImGui::PopItemWidth();
	}


	const void InsertCombo(const char* label, int* current_item, const char* const items[], int size) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::Combo(label, current_item, items, size); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
	}
	const void InsertComboMiddle(const char* label, int* current_item, const char* const items[], int size) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(50.f); ImGui::PushItemWidth(158.f); ImGui::Combo(label, current_item, items, size); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
	}

	const void InsertComboColor(const char* label, int* current_item, const char* const items[], int size, Color* col, bool alpha) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::Combo(label, current_item, items, size); ImGui::PopItemWidth(); ImGui::SameLine(1.f); ColorPicker(label, col, alpha);
	}
	const void InsertComboWithoutText(const char* label, int* current_item, const char* items[], int size) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::Combo(label, current_item, items, size); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
	}
	const void InsertMultiCombo(const char* label, const char** displayName,  bool* data, int dataSize) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::MultiCombo(label, displayName, data, dataSize); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
	}
	const void InsertMultiComboWithoutText(const char* label, const char** displayName, bool* data, int dataSize) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::MultiCombo(label, displayName, data, dataSize); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
	}

	const void InsertButton(const char* label) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::PushItemWidth(158.f); ImGui::Button(label, ImVec2(158.f, 0)); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
	}

	const void InsertButtonLeft(const char* label, bool& button) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::PushItemWidth(158.f); button = ImGui::Button(label, ImVec2(158.f, 0)); ImGui::PopItemWidth();
	}

	const void InsertButtonSameline(const char* label, bool& button) {
		ImGui::SameLine(); ImGui::PushItemWidth(158.f); button = ImGui::Button(label, ImVec2(158.f, 0)); ImGui::PopItemWidth();
	}

	const void InsertButtonMiddle(const char* label, bool& button) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(50.f); ImGui::PushItemWidth(158.f); button = ImGui::Button(label, ImVec2(158.f, 0)); ImGui::PopItemWidth(); ImGui::CustomSpacing(1.f);
	}

	const void InsertText(const char* label) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::SameLine(42.f); ImGui::Text(label);
	}
	const void InsertMultiTextInput(const char* label, char* buf, int bufSize, float x, float y) {
		ImGui::Spacing(); ImGui::NewLine(); ImGui::NewLine(); ImGui::SameLine(19.f); ImGui::PushItemWidth(158.f); ImGui::InputTextMultiline(label, buf, bufSize, ImVec2(x, y), ImGuiInputTextFlags_AllowTabInput); ImGui::PopItemWidth();
	}
	const void InsertColorPicker(const char* label, Color *col, bool alpha) {
		ImGui::SameLine(219.f); ColorPicker(label, col, alpha);
	}
	const void InsertComboColorPicker(const char* label, Color *col, bool alpha) {
		ImGui::SameLine(1.f); ColorPicker(label, col, alpha);
	}

}