//========= Copyright Valve Corporation, All rights reserved. ============//
//
// The copyright to the contents herein is the property of Valve, L.L.C.
// The contents may be used and/or copied only with the written permission of
// Valve, L.L.C., or in accordance with the terms and conditions stipulated in
// the agreement/contract under which the contents have been supplied.
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#ifndef ISURFACE_V30_H
#define ISURFACE_V30_H

#ifdef _WIN32
#pragma once
#endif

#include "../tier0/Vector.h"

#ifdef CreateFont
#undef CreateFont
#endif

#ifdef PlaySound
#undef PlaySound
#endif

class Color;

namespace vgui
{

	class Image;
	class Point;

	// handles
	typedef unsigned long HCursor;
	typedef unsigned long HTexture;
	typedef unsigned long HFont;
}



namespace SurfaceV30
{

	//SRC only defines


	struct Vertex_t
	{
		Vertex_t() {}
		Vertex_t(const Vector2D& pos, const Vector2D& coord = Vector2D(0, 0))
		{
			m_Position = pos;
			m_TexCoord = coord;
		}
		void Init(const Vector2D& pos, const Vector2D& coord = Vector2D(0, 0))
		{
			m_Position = pos;
			m_TexCoord = coord;
		}

		Vector2D	m_Position;
		Vector2D	m_TexCoord;
	};


	enum FontDrawType_t
	{
		// Use the "additive" value from the scheme file
		FONT_DRAW_DEFAULT = 0,

		// Overrides
		FONT_DRAW_NONADDITIVE,
		FONT_DRAW_ADDITIVE,

		FONT_DRAW_TYPE_COUNT = 2,
	};


	// Refactor these two
	struct CharRenderInfo
	{
		// In:
		FontDrawType_t	drawType;
		wchar_t			ch;

		// Out
		bool			valid;

		// In/Out (true by default)
		bool			shouldclip;
		// Text pos
		int				x, y;
		// Top left and bottom right
		Vertex_t		verts[2];
		int				textureId;
		int				abcA;
		int				abcB;
		int				abcC;
		int				fontTall;
		vgui::HFont		currentFont;
	};


	struct IntRect
	{
		int x0;
		int y0;
		int x1;
		int y1;
	};


	//-----------------------------------------------------------------------------
	// Purpose: Wraps contextless windows system functions
	//-----------------------------------------------------------------------------

} // end namespace

//-----------------------------------------------------------------------------
// FIXME: This works around using scoped interfaces w/ EXPOSE_SINGLE_INTERFACE
//-----------------------------------------------------------------------------

#define VGUI_SURFACE_INTERFACE_VERSION_30 "VGUI_Surface030"

#endif // ISURFACE_V30_H