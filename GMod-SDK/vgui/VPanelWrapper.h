#pragma once


// Auto reconstructed from vtable block @ 0x0002D6F8
// from "vgui2.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class VPanel
{
public:
	/*0*/	virtual void* Destr() = 0;
	/*1*/	virtual void* Init(void*) = 0;
	/*2*/	virtual void* Plat(void) = 0;
	/*3*/	virtual void* SetPlat(void*) = 0;
	/*4*/	virtual void* GetHPanel(void) = 0;
	/*5*/	virtual void* SetHPanel(unsigned long) = 0;
	/*6*/	virtual void* PopupWantsFront(void) = 0;
	/*7*/	virtual void* SetPopupWantsFront(bool) = 0;
	/*8*/	virtual void* IsPopup(void) = 0;
	/*9*/	virtual void* SetPopup(bool) = 0;
	/*10*/	virtual void* IsFullyVisible(void) = 0;
	/*11*/	virtual void* SetPos(int, int) = 0;
	/*12*/	virtual void* GetPos(int&, int&) = 0;
	/*13*/	virtual void* SetSize(int, int) = 0;
	/*14*/	virtual void* GetSize(int&, int&) = 0;
	/*15*/	virtual void* SetMinimumSize(int, int) = 0;
	/*16*/	virtual void* GetMinimumSize(int&, int&) = 0;
	/*17*/	virtual void* SetZPos(int) = 0;
	/*18*/	virtual void* GetZPos(void) = 0;
	/*19*/	virtual void* GetAbsPos(int&, int&) = 0;
	/*20*/	virtual void* GetClipRect(int&, int&, int&, int&) = 0;
	/*21*/	virtual void* SetInset(int, int, int, int) = 0;
	/*22*/	virtual void* GetInset(int&, int&, int&, int&) = 0;
	/*23*/	virtual void* Solve(void) = 0;
	/*24*/	virtual void* SetVisible(bool) = 0;
	/*25*/	virtual void* SetEnabled(bool) = 0;
	/*26*/	virtual void* IsVisible(void) = 0;
	/*27*/	virtual void* IsEnabled(void) = 0;
	/*28*/	virtual void* SetParent(VPanel*) = 0;
	/*29*/	virtual void* GetChildCount(void) = 0;
	/*30*/	virtual void* GetChild(int) = 0;
	/*31*/	virtual void* GetParent(void) = 0;
	/*32*/	virtual void* MoveToFront(void) = 0;
	/*33*/	virtual void* MoveToBack(void) = 0;
	/*34*/	virtual void* HasParent(VPanel*) = 0;
	/*35*/	virtual void* GetChildren(void) = 0;
	/*36*/	virtual void* GetName(void) = 0;
	/*37*/	virtual void* GetClassName(void) = 0;
	/*38*/	virtual void* GetScheme(void) = 0;
	/*39*/	virtual void* SendMessage(void*, unsigned int) = 0;
	/*40*/	virtual void* Client(void) = 0;
	/*41*/	virtual void* SetKeyBoardInputEnabled(bool) = 0;
	/*42*/	virtual void* SetMouseInputEnabled(bool) = 0;
	/*43*/	virtual void* IsKeyBoardInputEnabled(void) = 0;
	/*44*/	virtual void* IsMouseInputEnabled(void) = 0;
	/*45*/	virtual void* IsTopmostPopup(void)const = 0;
	/*46*/	virtual void* SetTopmostPopup(bool) = 0;
	/*47*/	virtual void* SetSiblingPin(VPanel*, unsigned char, unsigned char) = 0;
	/*48*/	virtual void* GetInternalAbsPos(int&, int&) = 0;
};

// Auto reconstructed from vtable block @ 0x0002E034
// from "vgui2.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.

// DO NOT USE ANY METHOD FROM THIS, IT IS ONE METHOD OFF FROM THE ACTUAL ONE AND I'm CURRENTLY LAZY TO FIX.
class VPanelWrapper
{
public:
	//Don't forget the constructor.
	/*0*/	virtual void* Destr() = 0;
	/*1*/	virtual void* Init(unsigned int, void*) = 0;
	/*2*/	virtual void* SetPos(unsigned int, int, int) = 0;
	/*3*/	virtual void* GetPos(unsigned int, int&, int&) = 0;
	/*4*/	virtual void* SetSize(unsigned int, int, int) = 0;
	/*5*/	virtual void* GetSize(unsigned int, int&, int&) = 0;
	/*6*/	virtual void* SetMinimumSize(unsigned int, int, int) = 0;
	/*7*/	virtual void* GetMinimumSize(unsigned int, int&, int&) = 0;
	/*8*/	virtual void* SetZPos(unsigned int, int) = 0;
	/*9*/	virtual void* GetZPos(unsigned int) = 0;
	/*10*/	virtual void* GetAbsPos(unsigned int, int&, int&) = 0;
	/*11*/	virtual void* GetClipRect(unsigned int, int&, int&, int&, int&) = 0;
	/*12*/	virtual void* SetInset(unsigned int, int, int, int, int) = 0;
	/*13*/	virtual void* GetInset(unsigned int, int&, int&, int&, int&) = 0;
	/*14*/	virtual void* SetVisible(unsigned int, bool) = 0;
	/*15*/	virtual void* IsVisible(unsigned int) = 0;
	/*16*/	virtual void* SetParent(unsigned int, unsigned int) = 0;
	/*17*/	virtual void* GetChildCount(unsigned int) = 0;
	/*18*/	virtual void* GetChild(unsigned int, int) = 0;
	/*19*/	virtual void* GetChildren(unsigned int) = 0;
	/*20*/	virtual void* GetParent(unsigned int) = 0;
	/*21*/	virtual void* MoveToFront(unsigned int) = 0;
	/*22*/	virtual void* MoveToBack(unsigned int) = 0;
	/*23*/	virtual void* HasParent(unsigned int, unsigned int) = 0;
	/*24*/	virtual void* IsPopup(unsigned int) = 0;
	/*25*/	virtual void* SetPopup(unsigned int, bool) = 0;
	/*26*/	virtual void* IsFullyVisible(unsigned int) = 0;
	/*27*/	virtual void* GetScheme(unsigned int) = 0;
	/*28*/	virtual void* IsProportional(unsigned int) = 0;
	/*29*/	virtual void* IsAutoDeleteSet(unsigned int) = 0;
	/*30*/	virtual void* DeletePanel(unsigned int) = 0;
	/*31*/	virtual void* SetKeyBoardInputEnabled(VPanel* panel, bool) = 0;
	/*32*/	virtual void* SetMouseInputEnabled(VPanel* panel, bool) = 0;
	/*33*/	virtual bool IsKeyBoardInputEnabled(VPanel* panel) = 0;
	/*34*/	virtual void* IsMouseInputEnabled(unsigned int) = 0;
	/*35*/	virtual void* Solve(unsigned int) = 0;
	/*36*/	virtual const char* GetName(VPanel* ) = 0;
	/*37*/	virtual const char* GetClassName(unsigned int) = 0;
	/*38*/	virtual void* SendMessage(unsigned int, void*, unsigned int) = 0;
	/*39*/	virtual void* Think(unsigned int) = 0;
	/*40*/	virtual void* PerformApplySchemeSettings(unsigned int) = 0;
	/*41*/	virtual void* PaintTraverse(unsigned int, bool, bool) = 0;
	/*42*/	virtual void* Repaint(unsigned int) = 0;
	/*43*/	virtual void* IsWithinTraverse(unsigned int, int, int, bool) = 0;
	/*44*/	virtual void* OnChildAdded(unsigned int, unsigned int) = 0;
	/*45*/	virtual void* OnSizeChanged(unsigned int, int, int) = 0;
	/*46*/	virtual void* InternalFocusChanged(unsigned int, bool) = 0;
	/*47*/	virtual void* RequestInfo(unsigned int, void*) = 0;
	/*48*/	virtual void* RequestFocus(unsigned int, int) = 0;
	/*49*/	virtual void* RequestFocusPrev(unsigned int, unsigned int) = 0;
	/*50*/	virtual void* RequestFocusNext(unsigned int, unsigned int) = 0;
	/*51*/	virtual void* GetCurrentKeyFocus(unsigned int) = 0;
	/*52*/	virtual void* GetTabPosition(unsigned int) = 0;
	/*53*/	virtual void* Plat(unsigned int) = 0;
	/*54*/	virtual void* SetPlat(unsigned int, void*) = 0;
	/*55*/	virtual void* GetPanel(unsigned int, char const*) = 0;
	/*56*/	virtual void* IsEnabled(unsigned int) = 0;
	/*57*/	virtual void* SetEnabled(unsigned int, bool) = 0;
	/*58*/	virtual void* IsTopmostPopup(unsigned int) = 0;
	/*59*/	virtual void* SetTopmostPopup(unsigned int, bool) = 0;
	/*60*/	virtual void* SetSiblingPin(unsigned int, unsigned int, unsigned char, unsigned char) = 0;
	/*61*/	virtual void* PopupWantsFront(unsigned int) = 0;
	/*62*/	virtual void* SetPopupWantsFront(unsigned int, bool) = 0;
	/*63*/	virtual void* Client(unsigned int) = 0;
	/*64*/	virtual void* GetModuleName(unsigned int) = 0;
};