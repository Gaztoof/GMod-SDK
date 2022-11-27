#pragma once

#include "../engine/imaterial.h"
#include "../tier1/KeyValues.h"

typedef unsigned short MaterialHandle_t;

#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"

class IMatRenderContext
{
public:
	virtual void				BeginRender() = 0;
	virtual void				EndRender() = 0;

	virtual void				Flush(bool flushHardware = false) = 0;

	virtual void				BindLocalCubemap(ITexture* pTexture) = 0;

	// pass in an ITexture (that is build with "rendertarget" "1") or
	// pass in NULL for the regular backbuffer.
	virtual void				SetRenderTarget(ITexture* pTexture) = 0;
	virtual ITexture* GetRenderTarget(void) = 0;

	virtual void				GetRenderTargetDimensions(int& width, int& height) const = 0;
};

class CMaterialSystem
{
public:
	virtual bool					Connect(void* factory) = 0;
	virtual void					Disconnect() = 0;
	virtual void* QueryInterface(const char* pInterfaceName) = 0;
	virtual void*			Init() = 0;
	virtual void					Shutdown() = 0;

	virtual void* Unimplemented1(void) = 0;
	virtual void* Unimplemented2(void) = 0;
	virtual void* Unimplemented3(void) = 0;
	virtual void* Unimplemented4(void) = 0;

	virtual void*		Init(char const* pShaderAPIDLL, void* pMaterialProxyFactory, void* fileSystemFactory, void* cvarFactory = NULL) = 0;
	virtual void					SetShaderAPI(char const* pShaderAPIDLL) = 0;
	virtual void					SetAdapter(int nAdapter, int nFlags) = 0;
	virtual void					ModInit() = 0;
	virtual void					ModShutdown() = 0;
	virtual void					SetThreadMode(void* mode, int nServiceThread = -1) = 0;
	virtual void*	GetThreadMode() = 0;
	virtual bool					IsRenderThreadSafe() = 0;
	virtual void					ExecuteQueued() = 0;
	virtual void* GetHardwareConfig(const char* pVersion, int* returnCode) = 0;
	virtual bool				UpdateConfig(bool bForceUpdate) = 0;
	virtual bool				OverrideConfig(const void* config, bool bForceUpdate) = 0;
	virtual const void* GetCurrentConfigForVideoCard() const = 0;
	virtual bool				GetRecommendedConfigurationInfo(int nDXLevel, void* pKeyValues) = 0;
	virtual int					GetDisplayAdapterCount() const = 0;
	virtual int					GetCurrentAdapter() const = 0;
	virtual void				GetDisplayAdapterInfo(int adapter, void* info) const = 0;
	virtual int					GetModeCount(int adapter) const = 0;
	virtual void				GetModeInfo(int adapter, int mode, void* info) const = 0;
	virtual void				AddModeChangeCallBack(void* func) = 0;
	virtual void				GetDisplayMode(void*& mode) const = 0;
	virtual bool				SetMode(void* hwnd, const void* config) = 0;
	virtual bool				SupportsMSAAMode(int nMSAAMode) = 0;
	virtual const void* GetVideoCardIdentifier(void) const = 0;
	virtual void				SpewDriverInfo() const = 0;

	virtual void				GetDXLevelDefaults(UINT& max_dxlevel, UINT& recommended_dxlevel) = 0;
	virtual void				GetBackBufferDimensions(int& width, int& height) const = 0;
	virtual void*			GetBackBufferFormat() const = 0;
	virtual bool				SupportsHDRMode(void* nHDRModede) = 0;
	virtual bool				AddView(void* hwnd) = 0;
	virtual void				RemoveView(void* hwnd) = 0;
	virtual void				SetView(void* hwnd) = 0;
	virtual void				BeginFrame(float frameTime) = 0;
	virtual void				EndFrame() = 0;
	virtual void				Flush(bool flushHardware = false) = 0;
	virtual void				SwapBuffers() = 0;
	virtual void				EvictManagedResources() = 0;
	virtual void				ReleaseResources(void) = 0;
	virtual void				ReacquireResources(void) = 0;
	virtual void				AddReleaseFunc(void* func) = 0;
	virtual void				RemoveReleaseFunc(void* func) = 0;
	virtual void				AddRestoreFunc(void* func) = 0;
	virtual void				RemoveRestoreFunc(void* func) = 0;
	virtual void				ResetTempHWMemory(bool bExitingLevel = false) = 0;
	virtual void				HandleDeviceLost() = 0;
	virtual int					ShaderCount() const = 0;
	virtual int					GetShaders(int nFirstShader, int nMaxCount, void** ppShaderList) const = 0;
	virtual int					ShaderFlagCount() const = 0;
	virtual const char* ShaderFlagName(int nIndex) const = 0;
	virtual void				GetShaderFallback(const char* pShaderName, char* pFallbackShader, int nFallbackLength) = 0;
	virtual void* GetMaterialProxyFactory() = 0;
	virtual void				SetMaterialProxyFactory(void* pFactory) = 0;
	virtual void				EnableEditorMaterials() = 0;
	virtual void				SetInStubMode(bool bInStubMode) = 0;
	virtual void				DebugPrintUsedMaterials(const char* pSearchSubString, bool bVerbose) = 0;
	virtual void				DebugPrintUsedTextures(void) = 0;
	virtual void				ToggleSuppressMaterial(char const* pMaterialName) = 0;
	virtual void				ToggleDebugMaterial(char const* pMaterialName) = 0;
	virtual bool				UsingFastClipping(void) = 0;
	virtual int					StencilBufferBits(void) = 0;
	virtual void				UncacheAllMaterials() = 0;
	virtual void				UncacheUnusedMaterials(bool bRecomputeStateSnapshots = false) = 0;
	virtual void				CacheUsedMaterials() = 0;
	virtual void				ReloadTextures() = 0;
	virtual void				ReloadMaterials(const char* pSubString = NULL) = 0;
	virtual IMaterial* CreateMaterial(const char* pMaterialName, void* pVMTKeyValues) = 0;
	virtual IMaterial* FindMaterial(char const* pMaterialName, const char* pTextureGroupName, bool complain = true, const char* pComplainPrefix = NULL) = 0;
	virtual bool				IsMaterialLoaded(char const* pMaterialName) = 0;
	virtual MaterialHandle_t	FirstMaterial() const = 0;
	virtual MaterialHandle_t	NextMaterial(MaterialHandle_t h) const = 0;
	virtual MaterialHandle_t	InvalidMaterial() const = 0;
	virtual IMaterial* GetMaterial(MaterialHandle_t h) const = 0;
	virtual int					GetNumMaterials() const = 0;
	virtual void				SetAsyncTextureLoadCache(void* hFileCache) = 0;
	virtual ITexture* FindTexture(char const* pTextureName, const char* pTextureGroupName, bool complain = true, int nAdditionalCreationFlags = 0) = 0;
	virtual bool				IsTextureLoaded(char const* pTextureName) const = 0;
	
	virtual ITexture* CreateProceduralTexture(const char* pTextureName, const char* pTextureGroupName, int w, int h, void* fmt, int nFlags) = 0;
	virtual void BeginRenderTargetAllocation() = 0;
	virtual void EndRenderTargetAllocation() = 0;
	ITexture* CreateRenderTargetTexture(int w, int h, void* sizeMode, void* format, void* depth);
	ITexture* CreateNamedRenderTargetTextureEx(const char* pRTName, int w, int h, void* sizeMode, void* format, void* depth, unsigned int textureFlags, unsigned int renderTargetFlags);
	ITexture* CreateNamedRenderTargetTexture(const char* pRTName, int w, int h, void* sizeMode, void* format, void* depth, bool bClampTexCoords, bool bAutoMipMap);
	ITexture* CreateNamedRenderTargetTextureEx2(const char* pRTName, int w, int h, void* sizeMode, void* format, void* depth, unsigned int textureFlags, unsigned int renderTargetFlags = 0);
	ITexture* CreateNamedMultiRenderTargetTexture(const char* pRTName, int w, int h, void* sizeMode, void* format, void* depth, unsigned int textureFlags, unsigned int renderTargetFlags);
	// Every function untill next comment are not in the right order
	virtual void UNKNOWN() = 0;
	virtual int AllocateWhiteLightmap(IMaterial* pMaterial) = 0;
	virtual void UpdateLightmap(int lightmapPageID, int lightmapSize[2], int offsetIntoLightmapPage[2], float* pFloatImage, float* pFloatImageBump1, float* pFloatImageBump2, float* pFloatImageBump3) = 0;
	virtual int GetNumSortIDs() = 0;
	virtual void GetSortInfo(void* sortInfoArray) = 0;
	//virtual IMatRenderContext* GetRenderContext() = 0;
	virtual void GetLightmapPageSize(int lightmap, int* width, int* height) const = 0;
	virtual void ResetMaterialLightmapPageInfo() = 0;
	virtual bool IsStereoSupported() = 0;
	virtual bool IsStereoActiveThisFrame() const = 0;
	virtual void NVStereoUpdate() = 0;
	virtual void ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil = false) = 0;
	virtual void SpinPresent(unsigned int nFrames) = 0;

	IMatRenderContext* GetRenderContext()
		{
		return ((IMatRenderContext * (__thiscall *)(PVOID)) * (*(const void***)this + 102))(this);
	}

};