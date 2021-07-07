#pragma once
#include "../tier0/Vector.h"
#include "../engine/vmatrix.h"
enum ClearFlags_t
{
	VIEW_CLEAR_COLOR = 0x1,
	VIEW_CLEAR_DEPTH = 0x2,
	VIEW_CLEAR_FULL_TARGET = 0x4,
	VIEW_NO_DRAW = 0x8,
	VIEW_CLEAR_OBEY_STENCIL = 0x10, // Draws a quad allowing stencil test to clear through portals
	VIEW_CLEAR_STENCIL = 0x20,
};

enum StereoEye_t
{
	STEREO_EYE_MONO = 0,
	STEREO_EYE_LEFT = 1,
	STEREO_EYE_RIGHT = 2,
	STEREO_EYE_MAX = 3,
};


//-----------------------------------------------------------------------------
// Purpose: Renderer setup data.  
//-----------------------------------------------------------------------------
class CViewSetup
{
public:
	
	int			x;
	int			m_nUnscaledX;
	int			y;
	int			m_nUnscaledY;
	int			width;
	int			m_nUnscaledWidth;
	int			height;
	StereoEye_t m_eStereoEye;
	int			m_nUnscaledHeight;
	bool		m_bOrtho;
	float		m_OrthoLeft;
	float		m_OrthoTop;
	float		m_OrthoRight;
	float		m_OrthoBottom;
	float		fov;	
	float		fovViewmodel;
	Vector		origin;
	QAngle		angles;
	float		zNear;
	float		zFar;
	float		zNearViewmodel;	
	float		zFarViewmodel;
	float		m_flAspectRatio;
	bool		m_bOffCenter;
	float		m_flOffCenterTop;
	float		m_flOffCenterBottom;
	float		m_flOffCenterLeft;
	float		m_flOffCenterRight;
	bool		m_bDoBloomAndToneMapping;

	bool		m_bCacheFullSceneState;
	bool        m_bViewToProjectionOverride;
	VMatrix     m_ViewToProjection;
};