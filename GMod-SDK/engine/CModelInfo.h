#pragma once

#include "../tier0/Vector.h"

struct mstudiobone_t
{
	int					sznameindex;
	inline char* const pszName(void) const 
	{ 
		return ((char*)this) + sznameindex; 
	}
	int		 			parent;		// parent bone
	int					bonecontroller[6];	// bone controller index, -1 == none

	// default values
	Vector				pos;
	Quaternion			quat;
	RadianEuler			rot;
	// compression scale
	Vector				posscale;
	Vector				rotscale;

	matrix3x4_t			poseToBone;
	Quaternion			qAlignment;
	int					flags;
	int					proctype;
	int					procindex;		// procedural rule
	mutable int			physicsbone;	// index into physically simulated bone
	inline void* pProcedure() const { if (procindex == 0) return NULL; else return  (void*)(((BYTE*)this) + procindex); };
	int					surfacepropidx;	// index into string tablefor property name
	inline char* const pszSurfaceProp(void) const { return ((char*)this) + surfacepropidx; }
	int					contents;		// See BSPFlags.h for the contents flags

	int					unused[8];		// remove as appropriate

	mstudiobone_t() {}
private:
	// No copy constructors allowed
	mstudiobone_t(const mstudiobone_t& vOther);
};
struct studiohdr_t {
	int id;
	int version;
	int checksum;        // this has to be the same in the phy and vtx files to load!
	char name[64];
	int length;

	Vector eyeposition;    // ideal eye position
	Vector illumposition;    // illumination center
	Vector hull_min;        // ideal movement hull size
	Vector hull_max;
	Vector view_bbmin;        // clipping bounding box
	Vector view_bbmax;

	int flags;
	int numbones;            // bones
	int boneindex;
	inline mstudiobone_t* pBone(int i) const { return (mstudiobone_t*)(((BYTE*)this) + boneindex) + i; };



	int RemapSeqBone(int iSequence, int iLocalBone) const;    // maps local sequence bone to global bone
	int RemapAnimBone(int iAnim, int iLocalBone) const;        // maps local animations bone to global bone
	int numbonecontrollers;        // bone controllers
	int bonecontrollerindex;
	int numhitboxsets;
	int hitboxsetindex;

	// Look up hitbox set by index
	void* pHitboxSet(int i) const
	{
		return (void*)((((BYTE*)this) + hitboxsetindex) + i);
	};


	// file local animations? and sequences
//private:
	int					numlocalanim;			// animations/poses
	int					localanimindex;		// animation descriptions
	inline BYTE* pLocalAnimdesc(int i) const { if (i < 0 || i >= numlocalanim) i = 0; return (BYTE*)(((BYTE*)this) + localanimindex) + i; };

	int					numlocalseq;				// sequences
	int					localseqindex;
	inline BYTE* pLocalSeqdesc(int i) const { if (i < 0 || i >= numlocalseq) i = 0; return (BYTE*)(((BYTE*)this) + localseqindex) + i; };

	//public:
	bool				SequencesAvailable() const;
	int					GetNumSeq() const;
	void* pAnimdesc(int i) const;
	void* pSeqdesc(int i) const;
	int					iRelativeAnim(int baseseq, int relanim) const;	// maps seq local anim reference to global anim index
	int					iRelativeSeq(int baseseq, int relseq) const;		// maps seq local seq reference to global seq index

//private:
	mutable int			activitylistversion;	// initialization flag - have the sequences been indexed?
	mutable int			eventsindexed;
	//public:
	int					GetSequenceActivity(int iSequence);
	void				SetSequenceActivity(int iSequence, int iActivity);
	int					GetActivityListVersion(void);
	void				SetActivityListVersion(int version) const;
	int					GetEventListVersion(void);
	void				SetEventListVersion(int version);

	// raw textures
	int					numtextures;
	int					textureindex;
	inline BYTE* pTexture(int i) const { return (BYTE*)(((BYTE*)this) + textureindex) + i; };


	// raw textures search paths
	int					numcdtextures;
	int					cdtextureindex;
	inline char* pCdtexture(int i) const { return (((char*)this) + *((int*)(((BYTE*)this) + cdtextureindex) + i)); };

	// replaceable textures tables
	int					numskinref;
	int					numskinfamilies;
	int					skinindex;
	inline short* pSkinref(int i) const { return (short*)(((BYTE*)this) + skinindex) + i; };

	int					numbodyparts;
	int					bodypartindex;
	inline BYTE* pBodypart(int i) const { return (BYTE*)(((BYTE*)this) + bodypartindex) + i; };

	// queryable attachable points
//private:
	int					numlocalattachments;
	int					localattachmentindex;
	inline BYTE* pLocalAttachment(int i) const { return (BYTE*)(((BYTE*)this) + localattachmentindex) + i; };
	//public:
	int					GetNumAttachments(void) const;
	const void* pAttachment(int i) const;
	int					GetAttachmentBone(int i);
	// used on my tools in hlmv, not persistant
	void				SetAttachmentBone(int iAttachment, int iBone);

	// animation node to animation node transition graph
//private:
	int					numlocalnodes;
	int					localnodeindex;
	int					localnodenameindex;
	inline char* pszLocalNodeName(int iNode) const { return (((char*)this) + *((int*)(((BYTE*)this) + localnodenameindex) + iNode)); }
	inline BYTE* pLocalTransition(int i) const { return (BYTE*)(((BYTE*)this) + localnodeindex) + i; };

	//public:
	int					EntryNode(int iSequence);
	int					ExitNode(int iSequence);
	char* pszNodeName(int iNode);
	int					GetTransition(int iFrom, int iTo) const;

	int					numflexdesc;
	int					flexdescindex;
	inline BYTE* pFlexdesc(int i) const { return (BYTE*)(((BYTE*)this) + flexdescindex) + i; };

	int					numflexcontrollers;
	int					flexcontrollerindex;
	inline BYTE* pFlexcontroller(int i) const { return (BYTE*)(((BYTE*)this) + flexcontrollerindex) + i; };

	int					numflexrules;
	int					flexruleindex;
	inline BYTE* pFlexRule(int i) const { return (BYTE*)(((BYTE*)this) + flexruleindex) + i; };

	int					numikchains;
	int					ikchainindex;
	inline BYTE* pIKChain(int i) const { return (BYTE*)(((BYTE*)this) + ikchainindex) + i; };

	int					nummouths;
	int					mouthindex;
	inline BYTE* pMouth(int i) const { return (BYTE*)(((BYTE*)this) + mouthindex) + i; };

	//private:
	int					numlocalposeparameters;
	int					localposeparamindex;
	inline BYTE* pLocalPoseParameter(int i) const { return (BYTE*)(((BYTE*)this) + localposeparamindex) + i; };
	//public:
	int					GetNumPoseParameters(void) const;
	const void* pPoseParameter(int i);
	int					GetSharedPoseParameter(int iSequence, int iLocalPose) const;

	int					surfacepropindex;
	inline char* const pszSurfaceProp(void) const { return ((char*)this) + surfacepropindex; }

	// Key values
	int					keyvalueindex;
	int					keyvaluesize;
	inline const char* KeyValueText(void) const { return keyvaluesize != 0 ? ((char*)this) + keyvalueindex : NULL; }

	int					numlocalikautoplaylocks;
	int					localikautoplaylockindex;
	inline BYTE* pLocalIKAutoplayLock(int i) const { return (BYTE*)(((BYTE*)this) + localikautoplaylockindex) + i; };

	int					GetNumIKAutoplayLocks(void) const;
	const void* pIKAutoplayLock(int i);
	int					CountAutoplaySequences() const;
	int					CopyAutoplaySequences(unsigned short* pOut, int outCount) const;
	int					GetAutoplayList(unsigned short** pOut) const;

	// The collision model mass that jay wanted
	float				mass;
	int					contents;

	// external animations, models, etc.
	int					numincludemodels;
	int					includemodelindex;
	inline BYTE* pModelGroup(int i) const { return (BYTE*)(((BYTE*)this) + includemodelindex) + i; };
	// implementation specific call to get a named model
	const studiohdr_t* FindModel(void** cache, char const* modelname) const;

	// implementation specific back pointer to virtual data
	mutable void* virtualModel;
	void* GetVirtualModel(void) const;

	// for demand loaded animation blocks
	int					szanimblocknameindex;
	inline char* const pszAnimBlockName(void) const { return ((char*)this) + szanimblocknameindex; }
	int					numanimblocks;
	int					animblockindex;
	/*inline BYTE* pAnimBlock(int i) const { return (BYTE*)(((BYTE*)this) + animblockindex) + i; };
	mutable void* animblockModel;
	BYTE* GetAnimBlock(int i) const;
	*/
	int					bonetablebynameindex;
	inline const BYTE* GetBoneTableSortedByName() const { 
		return (BYTE*)this + bonetablebynameindex;
	}
};

// Auto reconstructed from vtable block @ 0x004F47E8
// from "engine.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class CModelInfo
{
public:
	//Don't forget the constructor.
	/*0*/	virtual void* Destr1() = 0;
	/*1*/	virtual void* Unknown1() = 0;
	/*2*/	virtual void* GetModelIndex(char const*)const = 0;
	/*3*/	virtual void* GetModelName(model_t const*)const = 0;
	/*4*/	virtual void* GetVCollide(model_t const*) = 0;
	/*5*/	virtual void* GetVCollide(int) = 0;
	/*6*/	virtual void* GetModelBounds(model_t const*, Vector&, Vector&)const = 0;
	/*7*/	virtual void* GetModelRenderBounds(model_t const*, Vector&, Vector&)const = 0;
	/*8*/	virtual void* GetModelFrameCount(model_t const*)const = 0;
	/*9*/	virtual void* GetModelType(model_t const*)const = 0;
	/*10*/	virtual void* GetModelExtraData(model_t const*) = 0;
	/*11*/	virtual void* ModelHasMaterialProxy(model_t const*)const = 0;
	/*12*/	virtual void* IsTranslucent(model_t const*)const = 0;
	/*13*/	virtual void* IsTranslucentTwoPass(model_t const*)const = 0;
	/*14*/	virtual void* RecomputeTranslucency(model_t const*, int, int, void*, float) = 0;
	/*15*/	virtual void* GetModelMaterialCount(model_t const*)const = 0;
	/*16*/	virtual void* GetModelMaterials(model_t const*, int, IMaterial**) = 0;
	/*17*/	virtual void* IsModelVertexLit(model_t const*)const = 0;
	/*18*/	virtual void* GetModelKeyValueText(model_t const*) = 0;
	/*19*/	virtual void* GetModelKeyValue(model_t const*, void*) = 0;//CUtlBuffer& as arg 2
	/*20*/	virtual void* GetModelRadius(model_t const*) = 0;
	/*21*/	virtual void* FindModel(studiohdr_t const*, void**, char const*)const = 0;
	/*22*/	virtual void* FindModel(void*)const = 0;
	/*23*/	virtual void* GetVirtualModel(studiohdr_t const*)const = 0;
	/*24*/	virtual void* GetAnimBlock(studiohdr_t const*, int)const = 0;
	/*25*/	virtual void* Unknown2() = 0;
	/*26*/	virtual void* GetIlluminationPoint(model_t const*, IClientRenderable*, Vector const&, QAngle const&, Vector*) = 0;
	/*27*/	virtual void* GetModelContents(int) = 0;
	/*28*/	virtual studiohdr_t* GetStudiomodel(model_t const*) = 0;
	/*29*/	virtual void* GetModelSpriteWidth(model_t const*)const = 0;
	/*30*/	virtual void* GetModelSpriteHeight(model_t const*)const = 0;
	/*31*/	virtual void* SetLevelScreenFadeRange(float, float) = 0;
	/*32*/	virtual void* GetLevelScreenFadeRange(float*, float*)const = 0;
	/*33*/	virtual void* SetViewScreenFadeRange(float, float) = 0;
	/*34*/	virtual void* ComputeLevelScreenFade(Vector const&, float, float)const = 0;
	/*35*/	virtual void* ComputeViewScreenFade(Vector const&, float, float)const = 0;
	/*36*/	virtual void* GetAutoplayList(studiohdr_t const*, unsigned short**)const = 0;
	/*37*/	virtual void* GetCollideForVirtualTerrain(int) = 0;
	/*38*/	virtual void* IsUsingFBTexture(model_t const*, int, int, void*)const = 0;
	/*49*/	virtual void* Unknown3() = 0;
	/*41*/	virtual void* InitDynamicModels(void) = 0;
	/*42*/	virtual void* ShutdownDynamicModels(void) = 0;
	/*43*/	virtual void* AddDynamicModel(char const*, int) = 0;
	/*44*/	virtual void* ReferenceModel(int) = 0;
	/*45*/	virtual void* UnreferenceModel(int) = 0;
	/*46*/	virtual void* CleanupDynamicModels(bool) = 0;
	/*47*/	virtual void* GetCacheHandle(model_t const*)const = 0;
	/*48*/	virtual void* GetBrushModelPlaneCount(model_t const*)const = 0;
	/*49*/	virtual void* GetBrushModelPlane(model_t const*, int, cplane_t&, Vector*)const = 0;
	/*50*/	virtual void* GetSurfacepropsForVirtualTerrain(int) = 0;
	/*51*/	virtual void* OnLevelChange(void) = 0;
	/*52*/	virtual void* GetModelClientSideIndex(char const*)const = 0;
	/*53*/	virtual void* Unknown4() = 0;
	/*54*/	virtual void* IsDynamicModelLoading(int) = 0;
	/*55*/	virtual void* AddRefDynamicModel(int) = 0;
	/*56*/	virtual void* ReleaseDynamicModel(int) = 0;
	/*57*/	virtual void* RegisterModelLoadCallback(int, void*, bool) = 0;
	/*58*/	virtual void* UnregisterModelLoadCallback(int, void*) = 0;
	/*59*/	virtual void* GetBrushSurfaceCount(model_t const*)const = 0;
	/*60*/	virtual void* GetBrushSurfaces(model_t const*, int*, unsigned long)const = 0;
	/*61*/	virtual void* GetSurfaceVertexIndices(int)const = 0;
	/*62*/	virtual void* GetSurfaceVertices(int, int&)const = 0;
	/*63*/	virtual void* GetSurfaceMaterial(int)const = 0;
	/*64*/	virtual void* IsWaterSurface(int)const = 0;
	/*65*/	virtual void* IsSkyboxSurface(int)const = 0;
	/*66*/	virtual void* IsNoDrawSurface(int)const = 0;
};