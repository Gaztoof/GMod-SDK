#pragma once
#include "Vector.h"
#include "vmatrix.h"
#include "soundinfo.h"
class C_BaseEntity;
class C_BaseFlex
{
public:

	virtual void Spawn();

	virtual void InitPhonemeMappings();

	virtual void	StandardBlendingRules(void* hdr, Vector pos[], Quaternion q[], float currentTime, int boneMask);

	virtual void BuildTransformations(void* pStudioHdr, Vector* pos, Quaternion q[], const matrix3x4_t& cameraTransform, int boneMask, void* boneComputed);
	virtual	bool	SetupGlobalWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights);
	virtual	void	SetupLocalWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights);

	virtual Vector	SetViewTarget(void* pStudioHdr);
	virtual bool	GetSoundSpatialization(SpatializationInfo_t& info);
	virtual void	GetToolRecordingState(void* msg);
	virtual bool		StartSceneEvent(void* info, void* scene, void* event, void* actor, C_BaseEntity* pTarget);

	virtual void		ProcessSceneEvents(bool bFlexEvents);
	virtual	bool		ProcessSceneEvent(bool bFlexEvents, void* info, void* scene, void* event);
	virtual bool		ProcessSequenceSceneEvent(void* info, void* scene, void* event);

	void				ClearSceneEvents(void* scene, bool canceled);
	virtual	bool		ClearSceneEvent(void* info, bool fastKill, bool canceled);
	void				AddSceneEvent(void* scene, void* event, C_BaseEntity* pTarget = NULL, bool bClientSide = false);
	virtual bool		CheckSceneEventCompletion(void* info, float currenttime, void* scene, void* event);
	virtual void		EnsureTranslations(const void* pSettinghdr);


};