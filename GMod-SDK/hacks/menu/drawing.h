#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "../../tier0/Vector.h"
#include "../Utils.h"

#include <d3dtypes.h>
#include <dcommon.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

ID3DXLine* pLine = nullptr;
ID3DXFont* pFont = nullptr;
IDirect3DDevice9* pDevice = nullptr;

int DrawingFontSize = 11;

void InitRenderer(IDirect3DDevice9* pdevice)
{
	D3DXCreateLine(pdevice, &pLine);
	D3DXCreateFont(pdevice, DrawingFontSize, NULL, FW_HEAVY, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (L"Tahoma"), &pFont);
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
		{ pos.x, pos.y + height, 0.f, 1.f, color },
		{ pos.x, pos.y, 0.f, 1.f, color },
		{ pos.x + width, pos.y + height, 0.f, 1.f, color },
		{ pos.x + width, pos.y , 0.f, 1.f, color }
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
void RotateVec(QAngle ang, Vector& in, int height3D)
{
	float Sin = sin(DEG2RAD(ang.y));
	float Cos = cos(DEG2RAD(ang.y));
	//float CosZ = cos(DEG2RAD(ang.z));
	//float Tan = tan(DEG2RAD(ang.z));
	Vector vecCl(in.x, in.y, in.z);

	//std::cout << "tan: " << Tan  << " cosz: " << CosZ << " Cos: " << Cos << " sin: " << sin(DEG2RAD(ang.y)) << " x: " << ang.x << " y: " << ang.y << " z: " << ang.z   << std::endl;
	in.x = (vecCl.x * Cos - vecCl.y * Sin);
	in.y = (vecCl.x * Sin + vecCl.y * Cos);
	in.z = vecCl.z;
}

void DrawEspBox3D(Vector max, Vector min, Vector orig, QAngle ang, D3DCOLOR color)
{
	int height3D = max.z - min.z;
	//max = Vector(10, 10, 10);
	//min = Vector(-10, -10, -10);
	//ang.x = std::sin(GlobalVars->realtime) * 180.f + 180.f; // roll
	//ang.y = std::sin(GlobalVars->realtime) * 180.f + 180.f; // yaw
	//ang.z = std::sin(GlobalVars->realtime) * 180.f + 180.f; // yaw

	Vector b1(min.x, min.y, min.z);
	Vector b2(min.x, max.y, min.z);
	Vector b3(max.x, max.y, min.z);
	Vector b4(max.x, min.y, min.z);
	
	RotateVec(ang, b1, height3D);
	RotateVec(ang, b2, height3D);
	RotateVec(ang, b3, height3D);
	RotateVec(ang, b4, height3D);

	b1 += orig;
	b2 += orig;
	b3 += orig;
	b4 += orig;


	Vector t1 = Vector(b1.x , b1.y, b1.z + height3D);
	Vector t2 = Vector(b2.x , b2.y, b2.z + height3D);
	Vector t3 = Vector(b3.x , b3.y, b3.z + height3D);
	Vector t4 = Vector(b4.x , b4.y, b4.z + height3D);

	// cos(DEG2RAD(ang.z))
#define W2S(x,y) WorldToScreen(x, y)
	/*Vector tt1, tt2, tt3, tt4;
	W2S(b1, tt1);
	W2S(b2, tt2);
	W2S(b4, tt3);
	W2S(t1, tt4);
	DrawLine(tt1, tt2, 0xFF00FF00);
	DrawLine(tt1, tt3, 0xFF00FF00);
	DrawLine(tt1, tt4, 0xFF00FF00);
	DrawTextW(tt1, L"  OOO", 0xFF00FF00, true);
	DrawTextW(tt2, L"  XXX", 0xFF00FF00, true);
	DrawTextW(tt3, L"  YYY", 0xFF00FF00, true);
	DrawTextW(tt4, L"  ZZZ", 0xFF00FF00, true);*/

	Vector b1_2, b2_2, b3_2, b4_2, t1_2, t2_2, t3_2, t4_2;


	if (W2S(b1, b1_2) && W2S(b2, b2_2) && W2S(b3, b3_2) && W2S(b4, b4_2) && W2S(t1, t1_2) && W2S(t2, t2_2) && W2S(t3, t3_2) && W2S(t4, t4_2))
	{
		/*DrawTextW(b1_2, L"b1", 0xFFFFFFFF, false);
		DrawTextW(b2_2, L"b2", 0xFFFFFFFF, false);
		DrawTextW(b3_2, L"b3", 0xFFFFFFFF, false);
		DrawTextW(b4_2, L"b4", 0xFFFFFFFF, false);
		DrawTextW(t1_2, L"t1", 0xFFFFFFFF, false);
		DrawTextW(t2_2, L"t2", 0xFFFFFFFF, false);
		DrawTextW(t3_2, L"t3", 0xFFFFFFFF, false);
		DrawTextW(t4_2, L"t4", 0xFFFFFFFF, false);*/

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
