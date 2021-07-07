#pragma once

#include "../tier0/shareddefs.h"
#include "../tier0/Vector.h"
#include "vmatrix.h"
#include "imaterial.h"
#include "../client/CViewSetup.h"

enum DrawBrushModelMode_t
{
	DBM_DRAW_ALL = 0,
	DBM_DRAW_OPAQUE_ONLY,
	DBM_DRAW_TRANSLUCENT_ONLY,
};

class CVRenderView
{
public:
	virtual void			DrawBrushModel(void* baseentity, void* model, const Vector& origin, const QAngle& angles, bool bUnused) = 0;
	virtual void			DrawIdentityBrushModel(void* pList, void* model) = 0;
	virtual void			TouchLight(struct dlight_t* light) = 0;
	virtual void			Draw3DDebugOverlays(void) = 0;
	virtual void			SetBlend(float blend) = 0;
	virtual float			GetBlend(void) = 0;
	virtual void			SetColorModulation(float const* blend) = 0;
	virtual void			GetColorModulation(float* blend) = 0;
	virtual void			SceneBegin(void) = 0;
	virtual void			SceneEnd(void) = 0;
	virtual void			GetVisibleFogVolume(const Vector& eyePoint, void* pInfo) = 0;	
	virtual void* CreateWorldList() = 0;

	virtual void			BuildWorldLists(void* pList, void* pInfo, int iForceFViewLeaf, const void* pVisData = NULL, bool bShadowDepth = false, float* pReflectionWaterHeight = NULL) = 0;
	virtual void			DrawWorldLists(void* pList, unsigned long flags, float waterZAdjust) = 0;

	// Optimization for top view
	virtual void			DrawTopView(bool enable) = 0;
	virtual void			TopViewBounds(Vector2D const& mins, Vector2D const& maxs) = 0;

	// Draw lights
	virtual void			DrawLights(void) = 0;
	// FIXME:  This function is a stub, doesn't do anything in the engine right now
	virtual void			DrawMaskEntities(void) = 0;

	// Draw surfaces with alpha
	virtual void			DrawTranslucentSurfaces(void* pList, int sortIndex, unsigned long flags, bool bShadowDepth) = 0;

	// Draw Particles ( just draws the linefine for debugging map leaks )
	virtual void			DrawLineFile(void) = 0;
	// Draw lightmaps
	virtual void			DrawLightmaps(void* pList, int pageId) = 0;
	// Wraps view render sequence, sets up a view
	virtual void			ViewSetupVis(bool novis, int numorigins, const Vector origin[]) = 0;

	// Return true if any of these leaves are visible in the current PVS.
	virtual bool			AreAnyLeavesVisible(int* leafList, int nLeaves) = 0;

	virtual	void			VguiPaint(void) = 0;
	// Sets up view fade parameters
	virtual void			ViewDrawFade(byte* color, IMaterial* pMaterial) = 0;
	// Sets up the projection matrix for the specified field of view
	virtual void			OLD_SetProjectionMatrix(float fov, float zNear, float zFar) = 0;
	// Determine lighting at specified position
	virtual colorVec		GetLightAtPoint(Vector& pos) = 0;
	// Whose eyes are we looking through?
	virtual int				GetViewEntity(void) = 0;
	// Get engine field of view setting
	virtual float			GetFieldOfView(void) = 0;
	// 1 == ducking, 0 == not
	virtual unsigned char** GetAreaBits(void) = 0;

	// Set up fog for a particular leaf
	virtual void			SetFogVolumeState(int nVisibleFogVolume, bool bUseHeightFog) = 0;

	// Installs a brush surface draw override method, null means use normal renderer
	virtual void			InstallBrushSurfaceRenderer(void* pBrushRenderer) = 0;

	// Draw brush model shadow
	virtual void			DrawBrushModelShadow(void* pRenderable) = 0;

	// Does the leaf contain translucent surfaces?
	virtual	bool			LeafContainsTranslucentSurfaces(void* pList, int sortIndex, unsigned long flags) = 0;

	virtual bool			DoesBoxIntersectWaterVolume(const Vector& mins, const Vector& maxs, int leafWaterDataID) = 0;

	virtual void			SetAreaState() = 0;

	// See i
	virtual void			VGui_Paint(int mode) = 0;

	// Push, pop views (see PushViewFlags_t above for flags)
	virtual void			Push3DView(const CViewSetup& view, int nFlags, ITexture* pRenderTarget, void *frustumPlanes) = 0;
	virtual void			Push2DView(const CViewSetup& view, int nFlags, ITexture* pRenderTarget, void *frustumPlanes) = 0;
	virtual void			PopView(void *frustumPlanes) = 0;

	// Sets the main view
	virtual void			SetMainView(const Vector& vecOrigin, const QAngle& angles) = 0;

	enum
	{
		VIEW_SETUP_VIS_EX_RETURN_FLAGS_USES_RADIAL_VIS = 0x00000001
	};

	// Wraps view render sequence, sets up a view
	virtual void			ViewSetupVisEx(bool novis, int numorigins, const Vector origin[], unsigned int& returnFlags) = 0;

	//replaces the current view frustum with a rhyming replacement of your choice
	virtual void			OverrideViewFrustum(void *custom) = 0;

	virtual void			DrawBrushModelShadowDepth(void* baseentity, void* model, const Vector& origin, const QAngle& angles, void *DepthMode) = 0;
	virtual void			UpdateBrushModelLightmap(void* model, void* pRenderable) = 0;
	virtual void			BeginUpdateLightmaps(void) = 0;
	virtual void			EndUpdateLightmaps(void) = 0;
	virtual void			OLD_SetOffCenterProjectionMatrix(float fov, float zNear, float zFar, float flAspectRatio, float flBottom, float flTop, float flLeft, float flRight) = 0;
	virtual void			OLD_SetProjectionMatrixOrtho(float left, float top, float right, float bottom, float zNear, float zFar) = 0;
	virtual void			Push3DView(const CViewSetup& view, int nFlags, ITexture* pRenderTarget, void*frustumPlanes, ITexture* pDepthTexture) = 0;
	virtual void			GetMatricesForView(const CViewSetup& view, VMatrix* pWorldToView, VMatrix* pViewToProjection, VMatrix* pWorldToProjection, VMatrix* pWorldToPixels) = 0;
	virtual void			DrawBrushModelEx(void* baseentity, void* model, const Vector& origin, const QAngle& angles, DrawBrushModelMode_t mode) = 0;
};
