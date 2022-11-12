#pragma once

#pragma once

#include "../globals.hpp"
#include <Windows.h>
#include <optional>

enum PaintMode_t
{
    PAINT_UIPANELS = (1 << 0),
    PAINT_INGAMEPANELS = (1 << 1),
    PAINT_CURSOR = (1 << 2)
};

typedef void(__thiscall* _Paint)(void*, PaintMode_t);
_Paint oPaint;



void __fastcall hkPaint(void* _this,
#ifndef _WIN64
	void*, // __fastcall does literally nothing in x64, so that's why we make it inactive
#endif 
	PaintMode_t mode)
{
    if (mode & 2)
    {
        vmatrix_t matrix;
        memcpy(&matrix, &EngineClient->WorldToScreenMatrix().m, sizeof(vmatrix_t));

        Globals::viewMatr.store(matrix);
    }
    return oPaint(_this, mode);
}