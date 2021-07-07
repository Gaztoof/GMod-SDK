#pragma once

#include "../tier0/Vector.h"
#include "vmatrix.h"
#include "../tier0/Color.h"
#include "trace.h"
#include "IEngineTrace.h"
#include "imaterial.h"
#include "IStudioRender.h"

struct model_t
{
	int pad;
	char *name;
};

struct ModelRenderInfo_t
{
	Vector origin;
	QAngle angles;
	void* pRenderable;
	const model_t* pModel;
	const matrix3x4_t* pModelToWorld;
	const matrix3x4_t* pLightingOffset;
	const Vector* pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	void* instance;

	ModelRenderInfo_t()
	{
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};
typedef unsigned short ModelInstanceHandle_t;

struct DrawModelState_t
{
	void* m_pStudioHdr;
	void* m_pStudioHWData;
	void* m_pRenderable;
	const matrix3x4_t* m_pModelToWorld;
	void*		m_decals;
	int						m_drawFlags;
	int						m_lod;
};

class CModelRender
{
public:
	/*0*/	virtual int		DrawModel(int flags, void* pRenderable, ModelInstanceHandle_t instance, int entity_index, const void* model, Vector const& origin, QAngle const& angles, int skin, int body, int hitboxset, const matrix3x4_t* modelToWorld = NULL, const matrix3x4_t* pLightingOffset = NULL) = 0;
	/*1*/	virtual void	ForcedMaterialOverride(IMaterial* newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL) = 0;
	/*2*/	virtual void	SetViewTarget(const void* pStudioHdr, int nBodyIndex, const Vector& target) = 0;
	/*3*/	virtual ModelInstanceHandle_t CreateInstance(void* pRenderable, void* pCache = NULL) = 0;
	/*4*/	virtual void DestroyInstance(ModelInstanceHandle_t handle) = 0;
	/*5*/	virtual void SetStaticLighting(ModelInstanceHandle_t handle, void* pHandle) = 0;
	/*6*/	virtual void* GetStaticLighting(ModelInstanceHandle_t handle) = 0;
	/*7*/	virtual bool ChangeInstance(ModelInstanceHandle_t handle, void* pRenderable) = 0;
	/*8*/	virtual void AddDecal(ModelInstanceHandle_t handle, Ray_t const& ray, Vector const& decalUp, int decalIndex, int body, bool noPokeThru = false, int maxLODToDecal = ADDDECAL_TO_ALL_LODS) = 0;
	/*9*/	virtual void GMODAddDecal(ModelInstanceHandle_t handle, Ray_t const& ray, Vector const& decalUp, int decalIndex, int body, bool noPokeThru = false, int maxLODToDecal = ADDDECAL_TO_ALL_LODS) = 0;
	/*1*/	virtual void RemoveAllDecals(ModelInstanceHandle_t handle) = 0;
	/*11*/	virtual void RemoveAllDecalsFromAllModels() = 0;
	/*12*/	virtual matrix3x4_t* DrawModelShadowSetup(void* pRenderable, int body, int skin, DrawModelInfo_t* pInfo, matrix3x4_t* pCustomBoneToWorld = NULL) = 0;
	/*13*/	virtual void DrawModelShadow(void* pRenderable, const DrawModelInfo_t& info, matrix3x4_t* pCustomBoneToWorld = NULL) = 0;
	/*14*/	virtual bool RecomputeStaticLighting(ModelInstanceHandle_t handle) = 0;
	/*15*/	virtual void ReleaseAllStaticPropColorData(void) = 0;
	/*16*/	virtual void RestoreAllStaticPropColorData(void) = 0;
	/*17*/	virtual int	DrawModelEx(ModelRenderInfo_t& pInfo) = 0;
	/*18*/	virtual int	DrawModelExStaticProp(ModelRenderInfo_t& pInfo) = 0;
	/*19*/	virtual bool DrawModelSetup(ModelRenderInfo_t& pInfo, DrawModelState_t* pState, matrix3x4_t* pCustomBoneToWorld, matrix3x4_t** ppBoneToWorldOut) = 0;
	/*20*/	virtual void DrawModelExecute(const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld = NULL) = 0;
	/*21*/	virtual void SetupLighting(const Vector& vecCenter) = 0;
	/*22*/	virtual int DrawStaticPropArrayFast(void* pProps, int count, bool bShadowDepth) = 0;
	/*23*/	virtual void SuppressEngineLighting(bool bSuppress) = 0;
	/*24*/	virtual void SetupColorMeshes(int nTotalVerts) = 0;
	/*25*/	virtual void AddColoredDecal(ModelInstanceHandle_t handle, Ray_t const& ray, Vector const& decalUp, int decalIndex, int body, Color cColor, bool noPokeThru = false, int maxLODToDecal = ADDDECAL_TO_ALL_LODS) = 0;
};
