#pragma once

#include "../globals.hpp"

void __fastcall hkPaintTraverse(VPanelWrapper* _this,
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif
	VPanel* panel, bool force_repaint, bool allow_force)
{
	/*
	* Why do this here instead of inside present?
	* Because this has the panel argument, which is required to call any functions using the wrapper.
	* Why am I using the wrapper and not directly VPanel?
	* The panel argument is not actually a pointer to panel, but instead some kind of identifier.
	* What does this do? Blocks any form of input while the menu is open, doing only EnableInput(false) will automatically 
	* set your mouse to the screen's center which is real annoying cause you have to pause the game everytime you open the menu.
	*/

	/*vmatrix_t matrix;
	memcpy(&matrix, &EngineClient->WorldToScreenMatrix().m, sizeof(vmatrix_t));
	
	Globals::viewMatr.store(matrix);*/

	InputSystem->EnableInput(!Globals::openMenu);
	if (!strcmp(PanelWrapper->GetName(panel), "FocusOverlayPanel"))
	{
		Globals::lastPanelIdentifier = panel;
		PanelWrapper->SetKeyBoardInputEnabled(panel, Globals::openMenu);
		PanelWrapper->SetMouseInputEnabled(panel, Globals::openMenu);
	}
	auto l = Globals::waitingToBeExecuted.load();
	if(l.first && l.second && oRunStringEx)
	{
		oRunStringEx(LuaShared->GetLuaInterface(Globals::executeState * 2), RandomString(16).c_str(), "", l.second, true, true, true, true);
		Globals::waitingToBeExecuted.store(std::make_pair(false, nullptr));
	}

	oPaintTraverse(_this, panel, force_repaint, allow_force);

}