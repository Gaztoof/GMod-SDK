#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "Vector.h"
#include "Utils.h"

#include <d3dtypes.h>
#include <dcommon.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

ID3DXLine* pLine = nullptr;
ID3DXFont* pFont = nullptr;
IDirect3DDevice9* pDevice = nullptr;
void InitRenderer(IDirect3DDevice9* pdevice)
{
	D3DXCreateLine(pdevice, &pLine);
	D3DXCreateFont(pdevice, 12, NULL, FW_HEAVY, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (L"Tahoma"), &pFont);
	pDevice = pdevice;
}

void DrawTextW(Vector pos, std::wstring txt, ULONG color, bool outlined) {
	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);

	auto _text = [&](std::wstring_view _text, int _x, int _y, unsigned long _color) {
		RECT r{ _x, _y, _x, _y };
		pFont->DrawTextW(NULL, _text.data(), -1, &r, DT_NOCLIP, _color);
	};

	if (outlined) {
		_text(txt, pos.x - 1, pos.y, D3DCOLOR_RGBA(1, 1, 1, 255));
		_text(txt, pos.x + 1, pos.y, D3DCOLOR_RGBA(1, 1, 1, 255));
		_text(txt, pos.x, pos.y - 1, D3DCOLOR_RGBA(1, 1, 1, 255));
		_text(txt, pos.x, pos.y + 1, D3DCOLOR_RGBA(1, 1, 1, 255));
	}

	_text(txt, pos.x, pos.y, color);

	//tar->DrawText(txt.c_str(), txt.length(), format, D2D1::RectF(pos.x, pos.y, desktop.right, desktop.bottom), brush);
}
void DrawLineOutlined(Vector from, Vector to, ULONG color) {
	D3DXVECTOR2 lines[2] = {
		D3DXVECTOR2(from.x, from.y),
		D3DXVECTOR2(to.x, to.y)
	};
	D3DXVECTOR2 outline1[2] = {
		D3DXVECTOR2(from.x- 1, from.y- 1),
		D3DXVECTOR2(to.x- 1, to.y- 1)
	};
	D3DXVECTOR2 outline2[2] = {
		D3DXVECTOR2(from.x+1, from.y+ 1),
		D3DXVECTOR2(to.x+ 1, to.y+ 1)
	};

	pLine->Begin();
	pLine->Draw(lines, 2, color);
	pLine->Draw(outline1, 2, 0xFF000000);
	pLine->Draw(outline2, 2, 0xFF000000);

	pLine->End();
}
void DrawLine(Vector from, Vector to, ULONG color) {
	D3DXVECTOR2 lines[2] = {
		D3DXVECTOR2(from.x, from.y),
		D3DXVECTOR2(to.x, to.y)
	};

	pLine->Begin();
	pLine->Draw(lines, 2, color);
	pLine->End();
}

void DrawCircle(Vector pos, float r, int vertices, ULONG color) {
	D3DXVECTOR2 Line[128];
	if (vertices > 50)vertices = 50;
	float Step = D3DX_PI * 2.0 / vertices;
	int Count = 0;
	for (float a = 0; a < D3DX_PI * 2.0; a += Step)
	{
		float X1 = r * cos(a) + pos.x;
		float Y1 = r * sin(a) + pos.y;
		float X2 = r * cos(a + Step) + pos.x;
		float Y2 = r * sin(a + Step) + pos.y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count + 1].x = X2;
		Line[Count + 1].y = Y2;
		Count += 2;
	}
	pLine->Draw(Line, Count, color);
}
void DrawRect(Vector pos, float height, float width, ULONG color) {
	D2D1_RECT_F rect = { pos.x - 3.f, pos.y - height + 13.f, pos.x + width + 3.f, pos.y + height };
	DrawLine(Vector(pos.x, pos.y, 0), Vector(pos.x + width, pos.y, 0), color);
	DrawLine(Vector(pos.x, pos.y, 0), Vector(pos.x, pos.y + height, 0), color);
	DrawLine(Vector(pos.x + width, pos.y, 0), Vector(pos.x + width, pos.y + height, 0), color);
	DrawLine(Vector(pos.x, pos.y + height, 0), Vector(pos.x + width + 1.f, pos.y + height, 0), color);
}
void DrawFilledRect(Vector pos, float height, float width, ULONG color) {
	D3DTLVERTEX qV[4] = {
		{ float(pos.x), float(pos.y + height), 0.f, 1.f, color },
		{ float(pos.x), float(pos.y), 0.f, 1.f, color },
		{ float(pos.x + width), float(pos.y + height), 0.f, 1.f, color },
		{ float(pos.x + width), float(pos.y) , 0.f, 1.f, color }
	};

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->SetTexture(0, nullptr);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, qV, sizeof(D3DTLVERTEX));
}
void DrawEsp2D(Vector targetPos, Vector targetTop, ULONG color) {

	float height = targetTop.y - targetPos.y;
	Vector tl, tr;
	tl.x = targetTop.x - height / 4 ;
	tr.x = targetTop.x + height / 4;
	tl.y = tr.y = targetTop.y;

	Vector bl, br;
	bl.x = targetPos.x - height / 4;
	br.x = targetPos.x + height / 4;
	bl.y = br.y = targetPos.y;

	DrawLineOutlined(tl, tr, color);
	DrawLineOutlined(bl, br, color);
	DrawLineOutlined(tl, bl, color);
	DrawLineOutlined(tr, br, color);
}

void DrawEspBox3D(Vector top, Vector bot, float a, D3DCOLOR color)
{
	int width = 25;

	int height3D = abs(top.z - bot.z);
	Vector b1, b2, b3, b4, t1, t2, t3, t4;
	b1.z = b2.z = b3.z = b4.z = bot.z;
	b1.x = bot.x + (cos(DEG2RAD(a + 45)) * width) + width/2;
	b1.y = bot.y + (sin(DEG2RAD(a + 45)) * width) + width/2;

	b2.x = bot.x + (cos(DEG2RAD(a + 135)) * width) + width / 2;
	b2.y = bot.y + (sin(DEG2RAD(a + 135)) * width) + width / 2;

	b3.x = bot.x + (cos(DEG2RAD(a + 225)) * width) + width / 2;
	b3.y = bot.y + (sin(DEG2RAD(a + 225)) * width) + width / 2;

	b4.x = bot.x + (cos(DEG2RAD(a + 315)) * width) + width / 2;
	b4.y = bot.y + (sin(DEG2RAD(a + 315)) * width) + width / 2;

	t1.x = b1.x;
	t1.y = b1.y;
	t1.z = b1.z + height3D;

	t2.x = b2.x;
	t2.y = b2.y;
	t2.z = b2.z + height3D;

	t3.x = b3.x;
	t3.y = b3.y;
	t3.z = b3.z + height3D;

	t4.x = b4.x;
	t4.y = b4.y;
	t4.z = b4.z + height3D;
	Vector b1_2, b2_2, b3_2, b4_2, t1_2, t2_2, t3_2, t4_2;

	#define W2S(x,y) WorldToScreen(x, y)

	if (W2S(b1, b1_2) && W2S(b2, b2_2) && W2S(b3, b3_2) && W2S(b4, b4_2) && W2S(t1, t1_2) && W2S(t2, t2_2) && W2S(t3, t3_2) && W2S(t4, t4_2))
	{
		// collumns
		DrawLine(t1_2, b1_2, color);
		DrawLine(t2_2, b2_2, color);
		DrawLine(t3_2, b3_2, color);
		DrawLine(t4_2, b4_2, color);
		// top base
		DrawLine(t1_2, t2_2, color);
		DrawLine(t2_2, t3_2, color);
		DrawLine(t3_2, t4_2, color);
		DrawLine(t4_2, t1_2, color);
		// bottom bvase
		DrawLine(b1_2, b2_2, color);
		DrawLine(b2_2, b3_2, color);
		DrawLine(b3_2, b4_2, color);
		DrawLine(b4_2, b1_2, color);

	}



}