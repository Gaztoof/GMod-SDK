#pragma once
#include "../tier0/Vector.h"
#include "../tier0/soundinfo.h"
#include "../tier0/shareddefs.h"
#include "../engine/IEngineTrace.h"
#include "../engine/takedamageinfo.h"
#include "../engine/vmatrix.h"
#include "../engine/imaterial.h"
#include "c_basecombatweapon.h"
#include "usercmd.h"
#include "CCollisionProperty.h"

typedef struct player_info_s
{
	char name[128];
	int userID; // local server user ID, unique while server is running <- THIS IS NOT STEAMID
	char guid[33]; // that is Steamid
	unsigned int friendsid;
	char friendsname[128];
	bool fakeplayer; // true, if player is a bot controlled by game.dll
	bool ishltv;
	unsigned int customfiles[4]; // custom files CRC for this player
	unsigned char filesdownloaded; // this counter increases each time the server downloaded a new file
} player_info_t;

// Auto reconstructed from vtable block @ 0x008830B8
// from "client.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.

enum LineOfSightCheckType
{
	IGNORE_NOTHING,
	IGNORE_ACTORS
};
#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<2)	// player jumping out of water
#define FL_ONTRAIN				(1<<3) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<4)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<5) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<6) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<7)	// Is a player
#define FL_FAKECLIENT			(1<<8)	// Fake client, simulated server side; don't send network messages to them
#define MOVETYPE_NONE		0	
#define MOVETYPE_ISOMETRIC	1
#define MOVETYPE_WALK		2	
#define MOVETYPE_STEP		3	
#define MOVETYPE_FLY		4	
#define MOVETYPE_FLYGRAVITY	5
#define MOVETYPE_VPHYSICS	6
#define MOVETYPE_PUSH		7
#define MOVETYPE_NOCLIP		8
#define MOVETYPE_LADDER		9
#define MOVETYPE_OBSERVER	10
#define MOVETYPE_CUSTOM		11

// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define	FL_INWATER				(1<<9)	// In water

#define 	AUTOAIM_2DEGREES   0.0348994967025

#define 	AUTOAIM_5DEGREES   0.08715574274766

#define 	AUTOAIM_8DEGREES   0.1391731009601

#define 	AUTOAIM_10DEGREES   0.1736481776669

#define 	AUTOAIM_20DEGREES   0.3490658503989

class IClientRenderable
{
public:
	virtual void* GetIClientUnknown() = 0;
	virtual Vector const& GetRenderOrigin() = 0;
	virtual QAngle const& GetRenderAngles() = 0;
	virtual bool					ShouldDraw() = 0;
	virtual bool					IsTransparent() = 0;
	virtual bool					UsesPowerOfTwoFrameBufferTexture() = 0;
	virtual bool					UsesFullFrameBufferTexture() = 0;
	virtual void*	GetShadowHandle() = 0;
	virtual void* RenderHandle() = 0;
	virtual void* GetModel() = 0;
	virtual void					DrawModel(int flags) = 0;
	virtual int						GetBody() = 0;
	virtual void					ComputeFxBled() = 0;
	virtual int						GetFxBlend() = 0;
	virtual void					GetColorModulation(float* color) = 0;
	virtual bool					LODTest() = 0;
	virtual bool					SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void					SetupWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual void					DoAnimationEvents(void) = 0;
	virtual void* GetPVSNotifyInterface() = 0;
	virtual void					GetRenderBounds(Vector& mins, Vector& maxs) = 0;
	virtual void					GetRenderBoundsWorldspace(Vector& mins, Vector& maxs) = 0;
	virtual void					GetShadowRenderBounds(Vector& mins, Vector& maxs, void* shadowType) = 0;
	virtual bool					ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool					GetShadowCastDistance(float* pDist, void* shadowType) const = 0;
	virtual bool					GetShadowCastDirection(Vector* pDirection, void* shadowType) const = 0;
	virtual bool					IsShadowDirty() = 0;
	virtual void					MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable* GetShadowParent() = 0;
	virtual IClientRenderable* FirstShadowChild() = 0;
	virtual IClientRenderable* NextShadowPeer() = 0;
	virtual void*			ShadowCastType() = 0;
	virtual void					CreateModelInstance() = 0;
	virtual void*	GetModelInstance() = 0;
	virtual const matrix3x4_t& RenderableToWorldTransform() = 0;
	virtual int						LookupAttachment(const char* pAttachmentName) = 0;
	virtual	bool					GetAttachment(int number, Vector& origin, QAngle& angles) = 0;
	virtual bool					GetAttachment(int number, matrix3x4_t& matrix) = 0;
	virtual float* GetRenderClipPlane(void) = 0;
	virtual int						GetSkin() = 0;
	virtual bool					IsTwoPass(void) = 0;
	virtual void					OnThreadedDrawSetup() = 0;
	virtual bool					UsesFlexDelayedWeights() = 0;
	virtual void					RecordToolMessage() = 0;
	virtual bool					IgnoresZBuffer(void) const = 0;
};
#define OBS_MODE_NONE		0	//Not spectating
#define OBS_MODE_DEATHCAM	1	//
#define OBS_MODE_FREEZECAM	2	//TF2-like freezecam
#define OBS_MODE_FIXED		3	//Same as OBS_MODE_CHASE, but you can't rotate the view
#define OBS_MODE_IN_EYE		4	//First person cam
#define OBS_MODE_CHASE		5	//Chase cam, 3rd person cam, free rotation around the spectated target
#define OBS_MODE_ROAMING	6	//Free roam/noclip-alike. Does not work from GM:PlayerDeath

class C_BasePlayer
{
public:
	//Don't forget the constructor.
	/*0*/	virtual void* destr1() = 0;
	/*1*/	virtual void* SetRefEHandle(void*) = 0;
	/*2*/	virtual void* GetRefEHandle(void)const = 0;
	/*3*/	virtual CCollisionProperty* GetCollideable(void) = 0;
	/*4*/	virtual void* GetClientNetworkable(void) = 0;
	/*5*/	virtual IClientRenderable* GetClientRenderable(void) = 0;
	/*6*/	virtual void* GetIClientEntity(void) = 0;
	/*7*/	virtual void* GetBaseEntity(void) = 0;
	/*8*/	virtual void* GetClientThinkable(void) = 0;
	/*9*/	virtual Vector& GetAbsOrigin(void)const = 0;
	/*10*/	virtual QAngle& GetAbsAngles(void)const = 0;
	/*11*/	virtual void* GetMouth(void) = 0;
	/*12*/	virtual void* GetSoundSpatialization(SpatializationInfo_t&) = 0;
	/*13*/	virtual void* GetClientClass(void) = 0;
	/*14*/	virtual void* YouForgotToImplementOrDeclareClientClass(void) = 0;
	/*15*/	virtual void* GetPredDescMap(void) = 0;
	/*16*/	virtual void* FireBullets(FireBulletsInfo_t const&) = 0;
	/*17*/	virtual void* ModifyFireBulletsDamage(CTakeDamageInfo*) = 0;
	/*18*/	virtual bool ShouldDrawUnderwaterBulletBubbles(void) = 0;
	/*19*/	virtual bool ShouldDrawWaterImpacts(void) = 0;
	/*20*/	virtual void* HandleShotImpactingWater(FireBulletsInfo_t const&,Vector const&,ITraceFilter*,Vector*) = 0;
	/*21*/	virtual void* GetBeamTraceFilter(void) = 0;
	/*22*/	virtual void* DispatchTraceAttack(CTakeDamageInfo const&,Vector const&,CGameTrace*, void*) = 0;
	/*23*/	virtual void* TraceAttack(CTakeDamageInfo const&,Vector const&,CGameTrace*, void*) = 0;
	/*24*/	virtual void* DoImpactEffect(CGameTrace&,int) = 0;
	/*25*/	virtual void* MakeTracer(Vector const&,CGameTrace const&,int) = 0;
	/*26*/	virtual void* GetTracerAttachment(void) = 0;
	/*30*/	virtual Color BloodColor(void) = 0;
	/*31*/	virtual void* GetTracerType(void) = 0;
	/*32*/	virtual void* Spawn(void) = 0;
	/*33*/	virtual void* SpawnClientEntity(void) = 0;
	/*34*/	virtual void* Precache(void) = 0;
	/*35*/	virtual void* Activate(void) = 0;
	/*36*/	virtual void* ParseMapData(void*) = 0;
	/*37*/	virtual void* KeyValue(char const*,char const*) = 0;
	/*38*/	virtual void* KeyValue(char const*,float) = 0;
	/*39*/	virtual void* KeyValue(char const*,Vector const&) = 0;
	/*40*/	virtual void* GetKeyValue(char const*,char*,int) = 0;
	/*41*/	virtual void* Init(int,int) = 0;
	/*42*/	virtual void* GetIClientUnknown(void) = 0;
	/*43*/	virtual void* GetBaseAnimating(void) = 0;
	/*44*/	virtual const char* SetClassname(char const*) = 0;
	/*66*/	virtual void* TestCollision(Ray_t const&,unsigned int,CGameTrace&) = 0;
	/*67*/	virtual void* TestHitboxes(Ray_t const&,unsigned int,CGameTrace&) = 0;
	/*68*/	virtual void* GetAttackDamageScale(void) = 0;
	/*69*/	virtual void* NotifyShouldTransmit(void*) = 0;
	// ^ A few of those might be wrong, let's hope not.
	/*70*/	virtual bool IsDormantDONOTUSE(void) = 0; // <- Do not use it, that is wrong.
	/*71*/	virtual void SetDormant(void*) = 0; // <- However, this is correct


	/*83*/	virtual void* GetThinkHandle(void) = 0;
	/*84*/	virtual void* SetThinkHandle(void*) = 0;
	/*85*/	virtual bool ShouldSavePhysics(void) = 0;
	/*86*/	virtual void* OnSave(void) = 0;
	/*87*/	virtual void* OnRestore(void) = 0;
	/*88*/	virtual void* ObjectCaps(void) = 0;
	/*89*/	virtual void* Save(void*) = 0;
	/*90*/	virtual void* Restore(void*) = 0;
	/*91*/	virtual void* CreateVPhysics(void) = 0;
	/*92*/	virtual void* VPhysicsDestroyObject(void) = 0;
	/*93*/	virtual void* GMOD_VPhysicsTest(void*) = 0;
	/*94*/	virtual void* GMOD_GetPhysBoneMatrix(int) = 0;
	/*95*/	virtual void* VPhysicsUpdate(void*) = 0;
	/*96*/	virtual void* VPhysicsGetObjectList(void**,int) = 0;
	/*97*/	virtual void* VPhysicsIsFlesh(void) = 0;
	/*102*/	virtual void* AddEntity(void) = 0;
	/*103*/	virtual void* GetLocalAngles(void)const = 0;
	/*104*/	virtual void* GetPrevLocalOrigin(void)const = 0;
	/*105*/	virtual void* GetPrevLocalAngles(void)const = 0;
	/*106*/	virtual void* CalcOverrideModelIndex(void) = 0;
	/*107*/	virtual void* WorldAlignMins(void)const = 0;
	/*108*/	virtual void* WorldAlignMaxs(void)const = 0;
	/*109*/	virtual void* WorldSpaceCenter(void)const = 0;
	/*110*/	virtual void* ComputeWorldSpaceSurroundingBox(Vector*,Vector*) = 0;
	/*111*/	virtual void* GetSolid(void)const = 0;
	/*112*/	virtual void* GetSolidFlags(void)const = 0;
	/*115*/	virtual void* GetAttachment(int,Vector&) = 0;
	/*117*/	virtual void* GetAttachmentVelocity(int,Vector&,Quaternion&) = 0;
	/*118*/	virtual int GetTeam(void) = 0;
	/*119*/	virtual int GetTeamNumber(void)const = 0;
	/*120*/	virtual void ChangeTeam(int) = 0;
	/*121*/	virtual int GetRenderTeamNumber(void) = 0;
	/*122*/	virtual bool InSameTeam(C_BaseEntity*) = 0;
	/*123*/	virtual bool InLocalTeam(void) = 0;
	/*124*/	virtual bool IsValidIDTarget(void) = 0;
	/*125*/	virtual void* GetIDString(void) = 0;
	/*126*/	virtual void* ModifyEmitSoundParams(EmitSound_t&) = 0;
	/*127*/	virtual void* InitializeAsClientEntity(char const*, void*) = 0;
	/*130*/	virtual void* OnPreDataChanged(void*) = 0;
	/*131*/	virtual void* GetClientVehicle(void) = 0;
	/*132*/	virtual void* GetAimEntOrigin(void*,Vector*,QAngle*) = 0;
	/*133*/	virtual void* GetOldOrigin(void) = 0;
	/*134*/	virtual void* GetRenderGroup(void) = 0;
	/*135*/	virtual void* GetToolRecordingState(void*) = 0;
	/*136*/	virtual void* CleanupToolRecordingState(void*) = 0;
	/*137*/	virtual void* GetCollideType(void) = 0;
	/*138*/	virtual bool ShouldDraw(void) = 0;
	/*140*/	virtual void* OnLatchInterpolatedVariables(int) = 0;

	/*274*/	virtual void* ControlMouth(void*) = 0;

	/*142*/	virtual void* OnNewParticleEffect(char const*, void*) = 0;
	/*143*/	virtual void* ResetLatched(void) = 0;
	/*144*/	virtual void* Interpolate(float) = 0;
	/*145*/	virtual bool IsSubModel(void) = 0;
	/*146*/	virtual void* CreateLightEffects(void) = 0;
	/*147*/	virtual void* Clear(void) = 0;
	/*148*/	virtual void* DrawBrushModel(bool,int,bool) = 0;
	/*149*/	virtual void* GetTextureAnimationStartTime(void) = 0;
	/*150*/	virtual void* TextureAnimationWrapped(void) = 0;
	/*151*/	virtual void* SetNextClientThink(float) = 0;
	/*152*/	virtual void SetHealth(int) = 0;
	/*153*/	virtual int GetHealth(void)const = 0;
	/*154*/	virtual int GetMaxHealth(void)const = 0;

	/*162*/	virtual void* AddDecal(Vector const&,Vector const&,Vector const&,int,int,bool,CGameTrace&,int) = 0;
	/*163*/	virtual bool IsClientCreated(void)const = 0;
	/*164*/	virtual void* UpdateOnRemove(void) = 0;
	/*165*/	virtual void* SUB_Remove(void) = 0;
	/*166*/	virtual void* SetPredictable(bool) = 0;
	/*167*/	virtual void* RestoreData(char const*,int,int) = 0;
	/*168*/	virtual void* DamageDecal(int,int) = 0;

	/*169*/	virtual void* DecalTrace(CGameTrace*,char const*) = 0;
	/*170*/	virtual void* ImpactTrace(CGameTrace*,int,char const*) = 0;
	/*171*/	virtual bool ShouldPredict(void) = 0;
	/*172*/	virtual void* Think(void) = 0;
	/*173*/	virtual void* CanBePoweredUp(void) = 0;
	/*174*/	virtual void* AttemptToPowerup(int,float,float,C_BaseEntity*, void*) = 0;
	/*175*/	virtual bool IsCurrentlyTouching(void)const = 0;
	/*176*/	virtual void* StartTouch(C_BaseEntity*) = 0;
	/*177*/	virtual void* Touch(C_BaseEntity*) = 0;
	/*178*/	virtual void* EndTouch(C_BaseEntity*) = 0;
	/*179*/	virtual void* PhysicsSolidMaskForEntity(void)const = 0;
	/*180*/	virtual void* PhysicsSimulate(void) = 0;
	/*181*/	virtual bool IsAlive(void) = 0;
	/*182*/	virtual bool IsPlayer(void)const = 0;
	/*183*/	virtual bool IsBaseCombatCharacter(void) = 0;
	/*184*/	virtual void* MyCombatCharacterPointer(void) = 0;
	/*185*/	virtual bool IsNPC(void) = 0;
	/*186*/	virtual bool IsNextBot(void) = 0;
	/*187*/	virtual bool IsBaseObject(void)const = 0;
	/*188*/	virtual bool IsBaseCombatWeapon(void)const = 0;
	/*189*/	virtual void* MyCombatWeaponPointer(void) = 0;
	/*190*/	virtual bool IsBaseTrain(void)const = 0;
	/*191*/	virtual Vector EyePosition(void) = 0;
	/*192*/	virtual QAngle& EyeAngles(void) = 0;
	/*193*/	virtual QAngle& LocalEyeAngles(void) = 0;
	/*194*/	virtual Vector EarPosition(void) = 0;
	/*195*/	virtual bool ShouldCollide(int,int)const = 0;
	/*196*/	virtual Vector&  GetViewOffset(void) = 0;
	/*197*/	virtual void SetViewOffset(Vector const&) = 0;
	/*198*/	virtual void* GetBody(void) = 0;
	/*199*/	virtual void* GetSkin(void) = 0;
	/*200*/	virtual void* GetModelInstance(void) = 0;
	/*202*/	virtual void* RenderHandle(void) = 0;
	/*210*/	virtual void* GetShadowUseOtherEntity(void)const = 0;
	/*211*/	virtual void* SetShadowUseOtherEntity(C_BaseEntity*) = 0;
	/*212*/	virtual void* AddRagdollToFadeQueue(void) = 0;
	/*213*/	virtual bool IsDeflectable(void) = 0;
	/*214*/	virtual void* GetStudioBody(void) = 0;
	/*215*/	virtual void* PerformCustomPhysics(Vector*,Vector*,QAngle*,QAngle*) = 0;
	/*216*/	virtual void* GetRenderClipPlane(void) = 0;
	/*218*/	virtual void* VPhysicsGetElement(int) = 0;
	/*219*/	virtual bool IsARagdoll(void) = 0;
	/*220*/	virtual void SetMaterialOverride(char const*) = 0;
	/*221*/	virtual void SetMaterialOverridePointer(IMaterial*) = 0;
	/*222*/	virtual IMaterial* GetMaterialOverridePointer(void) = 0;
	/*223*/	virtual char const* GetMaterialOverride(void) = 0;
	/*224*/	virtual void* StartMaterialOverride(bool) = 0;
	/*225*/	virtual void* EndMaterialOverride(bool) = 0;
	/*226*/	virtual void* GetCreationTime(void) = 0;
	/*227*/	virtual bool IsPredicted(void)const = 0;
	/*228*/	virtual bool IsWeapon(void)const = 0;
	/*229*/	virtual bool IsVehicle(void)const = 0;
	/*230*/	virtual bool IsJeep(void)const = 0;
	/*231*/	virtual bool UsesLua(void) = 0;
	/*232*/	virtual int GetLuaEntityType(void) = 0;
	/*233*/	virtual void PushEntity(void) = 0;
	///*234*/	virtual void Push_This_Entity(void) = 0;
	/*235*/	virtual void* SetEntity(char const*,C_BaseEntity*) = 0;
	/*236*/	virtual void* GetParentPhysicsNum(void) = 0;
	/*237*/	virtual void* SetParentPhysicsNum(int) = 0;
	/*238*/	virtual void* StartMotionController(void) = 0;
	/*239*/	virtual void* StopMotionController(void) = 0;
	/*240*/	virtual void* AttachObjectToMotionController(void*) = 0;
	/*241*/	virtual void* DetachObjectFromMotionController(void*) = 0;
	/*242*/	virtual void* GetCustomisedRenderBounds(Vector&,Vector&) = 0;
	/*243*/	virtual void* SetCustomisedRenderBounds(Vector*,Vector*) = 0;
	/*244*/	virtual const char* GetLuaScriptName(void) = 0;
	/*245*/	virtual void* SpawnedViaLua(void) = 0;
	/*246*/	virtual void* OverridePosition(void) = 0;
	/*247*/	virtual void* InitializeScriptedEntity(char const*) = 0;
	/*248*/	virtual void* ClearLuaData(void) = 0;
	/*249*/	virtual void* GetLuaTable(void) = 0;
	/*250*/	virtual void* GetLuaEntity(void) = 0;
	/*251*/	virtual void* SetLuaTable(void*) = 0;
	/*252*/	virtual void* Lua_OnEntityInitialized(void) = 0;
	/*253*/	virtual bool HasLuaTable(void) = 0;
	/*254*/	virtual void* LuaEntityInitialized(void) = 0;
	/*255*/	virtual void* ForcePhysicsDropObject(void) = 0;
	/*256*/	virtual void* StartDriving(C_BasePlayer*) = 0;
	/*257*/	virtual void* FinishDriving(C_BasePlayer*) = 0;
	/*258*/	virtual void* GMod_ShouldRenderEntity(void) = 0;
	/*259*/	virtual void* OnClientsideLuaRestored(void) = 0;
	/*260*/	virtual void* Lua_GetLuaClass(void) = 0;
	/*261*/	virtual void* VPhysicsCollision(int, void*) = 0;
	/*262*/	virtual void* GetNextBot(void) = 0;
	/*263*/	virtual void* GetBoneControllers(float*) = 0;
	/*264*/	virtual void* SetBoneController(int,float) = 0;
	/*265*/	virtual void* GetBoneController(int) = 0;
	/*266*/	virtual void* GetPoseParameters(void*,float*) = 0;
	/*267*/	virtual void* BuildTransformations(void*,Vector*,Quaternion*,matrix3x4_t const&,int, void*,Vector const*) = 0;
	/*268*/	virtual void* ApplyBoneMatrixTransform(matrix3x4_t&) = 0;
	/*269*/	virtual void* UpdateIKLocks(float) = 0;
	/*270*/	virtual void* CalculateIKLocks(float) = 0;
	/*271*/	virtual void* InternalDrawModel(int) = 0;
	/*272*/	virtual void* OnInternalDrawModel(void*) = 0;
	/*273*/	virtual void* OnPostInternalDrawModel(void*) = 0;
	/*274*/	virtual void* ControlMouth2(void*) = 0;
	/*275*/	virtual void* DoAnimationEvents(void*) = 0;
	/*276*/	virtual void* FireEvent(Vector const&,QAngle const&,int,char const*) = 0;
	/*277*/	virtual void* FireObsoleteEvent(Vector const&,QAngle const&,int,char const*) = 0;
	/*278*/	virtual void* ModifyEventParticles(char const*) = 0;
	/*279*/	virtual void* ResetEventsParity(void) = 0;
	/*280*/	virtual void* DispatchMuzzleEffect(char const*,bool) = 0;
	/*281*/	virtual void* StandardBlendingRules(void*,Vector*,Quaternion*,float,int) = 0;
	/*282*/	virtual void* AccumulateLayers(void*,Vector*,Quaternion*,float) = 0;
	/*283*/	virtual void* ChildLayerBlend(Vector*,Quaternion*,float,int) = 0;
	/*284*/	virtual void* AttachEntityToBone(void*,int,Vector,QAngle) = 0;
	/*285*/	virtual void* NotifyBoneAttached(void*) = 0;
	/*286*/	virtual void* UpdateBoneAttachments(void) = 0;
	/*287*/	virtual bool IsRagdoll(void)const = 0;
	/*288*/	virtual void* BecomeRagdollOnClient(void) = 0;
	/*289*/	virtual void* SaveRagdollInfo(int,matrix3x4_t const&, void*) = 0;
	/*290*/	virtual void* RetrieveRagdollInfo(Vector*,Quaternion*) = 0;
	/*291*/	virtual void* GetRagdollInitBoneArrays(matrix3x4_t*,matrix3x4_t*,matrix3x4_t*,float) = 0;
	/*292*/	virtual void* RefreshCollisionBounds(void) = 0;
	/*293*/	virtual void* SetSequence(int) = 0;
	/*294*/	virtual void* StudioFrameAdvance(void) = 0;
	/*295*/	virtual void* FrameAdvance(float) = 0;
	/*296*/	virtual void* GetSequenceCycleRate(void*,int) = 0;
	/*297*/	virtual void* UpdateClientSideAnimation(void) = 0;
	/*298*/	virtual void* ComputeClientSideAnimationFlags(void) = 0;
	/*299*/	virtual void* ResetClientsideFrame(void) = 0;
	/*300*/	virtual bool IsActivityFinished(void) = 0;
	/*301*/	virtual void* UncorrectViewModelAttachment(Vector&) = 0;
	/*302*/	virtual void* DoMuzzleFlash(void) = 0;
	/*303*/	virtual void* ProcessMuzzleFlashEvent(void) = 0;
	/*304*/	virtual void* SetServerIntendedCycle(float) = 0;
	/*305*/	virtual void* GetServerIntendedCycle(void) = 0;
	/*306*/	virtual bool ShouldResetSequenceOnNewModel(void) = 0;
	/*307*/	virtual bool IsViewModel(void)const = 0;
	/*308*/	virtual void* FormatViewModelAttachment(int,matrix3x4_t&) = 0;
	/*309*/	virtual bool IsMenuModel(void)const = 0;
	/*310*/	virtual void* CalcAttachments(void) = 0;
	/*311*/	virtual void* LastBoneChangedTime(void) = 0;
	/*313*/	virtual void* SetOverrideViewTarget(Vector) = 0;
	/*314*/	virtual void* GetNumPhysicsBones(void) = 0;
	/*315*/	virtual void* GetForcedLod(void) = 0;
	/*316*/	virtual void* SetForcedLod(int) = 0;
	/*317*/	virtual void* GetPhysBoneNumber(int) = 0;
	/*318*/	virtual void* GetBoneManipulator(bool) = 0;
	/*319*/	virtual void* GetFlexManipulator(bool) = 0;
	/*320*/	virtual void* UnqueueSetupBones(void) = 0;
	/*321*/	virtual void* StartMeshOverride(void*) = 0;
	/*322*/	virtual void* StopMeshOverride(void) = 0;
	/*323*/	virtual void* InitPhonemeMappings(void) = 0;
	/*324*/	virtual void* SetupGlobalWeights(matrix3x4_t const*,int,float*,float*) = 0;
	/*325*/	virtual void* SetupLocalWeights(matrix3x4_t const*,int,float*,float*) = 0;
	/*326*/	virtual void* SetViewTarget(void*) = 0;
	/*327*/	virtual void* StartSceneEvent(void*, void*, void*, void*,C_BaseEntity*) = 0;
	/*328*/	virtual void* ProcessSceneEvents(bool) = 0;
	/*329*/	virtual void* ProcessSceneEvent(bool, void*, void*, void*) = 0;
	/*330*/	virtual void* ProcessSequenceSceneEvent(void*, void*, void*) = 0;
	/*331*/	virtual void* ClearSceneEvent(void*,bool,bool) = 0;
	/*332*/	virtual void* CheckSceneEventCompletion(void*,float, void*, void*) = 0;
	/*333*/	virtual void* EnsureTranslations(void const*) = 0;
	/*335*/	virtual bool IsLookingTowards(Vector const&,float)const = 0;
	/*336*/	virtual bool IsInFieldOfView(C_BaseEntity*)const = 0;
	/*337*/	virtual bool IsInFieldOfView(Vector const&)const = 0;
	/*338*/	virtual bool IsLineOfSightClear(C_BaseEntity*,LineOfSightCheckType)const = 0;
	/*339*/	virtual bool IsLineOfSightClear(Vector const&,LineOfSightCheckType,C_BaseEntity*)const = 0;
	/*340*/	virtual void* Weapon_Switch(void*,int) = 0;
	/*341*/	virtual void* Weapon_CanSwitchTo(void*) = 0;
	/*342*/	virtual C_BaseCombatWeapon* GetActiveWeapon(void)const = 0;
	/*343*/	virtual void* SharedSpawn(void) = 0;
	/*344*/	virtual bool GetSteamID(void*) = 0; // requires csteamid ptr as arg
	/*345*/	virtual float GetPlayerMaxSpeed(void) = 0;
	/*346*/	virtual void* CalcView(Vector&,QAngle&,float&,float&,float&) = 0;
	/*347*/	virtual void* CalcViewModelView(Vector const&,QAngle const&) = 0;
	/*348*/	virtual void* CalcRoll(QAngle const&,Vector const&,float,float) = 0;
	/*349*/	virtual void* SetPlayerUnderwater(bool) = 0;
	/*194*/	virtual void* Weapon_ShootPosition(void) = 0;
	/*351*/	virtual void* Weapon_DropPrimary(void) = 0;
	/*352*/	virtual Vector GetAutoaimVector(float flDelta) = 0;
	/*353*/	virtual void* CreateMove(float,CUserCmd*) = 0;
	/*354*/	virtual void* AvoidPhysicsProps(CUserCmd*) = 0;
	/*355*/	virtual void* PlayerUse(void) = 0;
	/*356*/	virtual bool IsUseableEntity(C_BaseEntity*,unsigned int) = 0;
	/*357*/	virtual int GetObserverMode(void)const = 0;
	/*358*/	virtual C_BasePlayer* GetObserverTarget(void)const = 0;
	/*359*/	virtual void* GetRepresentativeRagdoll(void)const = 0;
	/*360*/	virtual void* TeamChange(int) = 0;
	/*361*/	virtual void* UpdateFlashlight(void) = 0;
	/*362*/	virtual bool IsAllowedToSwitchWeapons(void) = 0;
	/*363*/	virtual void* GetActiveWeaponForSelection(void) = 0;
	/*364*/	virtual void* GetRenderedWeaponModel(void) = 0;
	/*365*/	virtual bool IsOverridingViewmodel(void) = 0;
	/*366*/	virtual void* DrawOverriddenViewmodel(void*,int) = 0;
	/*367*/	virtual void* GetDefaultAnimSpeed(void) = 0;
	/*368*/	virtual void* ThirdPersonSwitch(bool) = 0; // dont use that lmao
	/*369*/	virtual void* CanSetSoundMixer(void) = 0;
	/*370*/	virtual void* GetVisionFilterFlags(bool) = 0;
	/*371*/	virtual void* CalculateVisionUsingCurrentFlags(void) = 0;
	/*372*/	virtual void* ViewModel_IsTransparent(void) = 0;
	/*373*/	virtual void* ViewModel_IsUsingFBTexture(void) = 0;
	/*374*/	virtual void* PreThink(void) = 0;
	/*375*/	virtual void* PostThink(void) = 0;
	/*376*/	virtual void* ItemPreFrame(void) = 0;
	/*377*/	virtual void* ItemPostFrame(void) = 0;
	/*378*/	virtual void* AbortReload(void) = 0;
	/*379*/	virtual void* SelectLastItem(void) = 0;
	/*380*/	virtual void* Weapon_SetLast(C_BaseCombatWeapon*) = 0;
	/*381*/	virtual void* Weapon_ShouldSetLast(C_BaseCombatWeapon*,C_BaseCombatWeapon*) = 0;
	/*382*/	virtual void* Weapon_ShouldSelectItem(C_BaseCombatWeapon*) = 0;
	/*383*/	virtual void* GetLastWeapon(void) = 0;
	/*384*/	virtual void* SelectItem(char const*,int) = 0;
	/*385*/	virtual void* UpdateClientData(void) = 0;
	/*386*/	virtual double GetFOV(void) = 0;
	/*387*/	virtual bool IsZoomed(void) = 0;
	/*388*/	virtual void* ViewPunch(QAngle const& angleOffset) = 0;
	/*389*/	virtual void* UpdateButtonState(int) = 0;
	/*390*/	virtual void* OverrideView(void*) = 0;
	/*391*/	virtual void* GetPlayerMins(void)const = 0;
	/*392*/	virtual void* GetPlayerMaxs(void)const = 0;
	/*393*/	virtual void* SetVehicleRole(int) = 0;
	/*394*/	virtual void* SetAnimation(PLAYER_ANIM) = 0;
	/*395*/	virtual double GetMinFOV(void)const = 0;
	/*396*/	virtual void* PlayPlayerJingle(void) = 0;
	/*397*/	virtual void* UpdateStepSound(void*,Vector const&,Vector const&) = 0;
	/*398*/	virtual void* PlayStepSound(Vector&, void*,float,bool) = 0;
	/*399*/	virtual void* GetFootstepSurface(Vector const&,char const*) = 0;
	/*400*/	virtual void* GetStepSoundVelocities(float*,float*) = 0;
	/*401*/	virtual void* SetStepSoundTime(void*,bool) = 0;
	/*402*/	virtual void* GetOverrideStepSound(char const*) = 0;
	/*403*/	virtual void* OnEmitFootstepSound(CSoundParameters const&,Vector const&,float) = 0;
	/*404*/	virtual void* ExitLadder(void) = 0;
	/*405*/	virtual void* Hints(void) = 0;
	/*406*/	virtual void* GetHeadLabelMaterial(void) = 0;
	/*407*/	virtual void* OnAchievementAchieved(int) = 0;
	/*408*/	virtual bool CanUseFirstPersonCommand(void) = 0;
	/*409*/	virtual int CalcObserverView(Vector&,QAngle&,float&) = 0;
	/*410*/	virtual void* GetChaseCamViewOffset(C_BaseEntity*) = 0;
	/*411*/	virtual void* CalcInEyeCamView(Vector&,QAngle&,float&) = 0;
	/*412*/	virtual double GetDeathCamInterpolationTime(void) = 0;
	/*413*/	virtual float* CalcDeathCamView(Vector&,QAngle&,float&) = 0;
	/*414*/	virtual void* CalcFreezeCamView(Vector&,QAngle&,float&) = 0;
	/*415*/	virtual int SetLocalViewAngles(QAngle const&) = 0;
	/*416*/	virtual int SetViewAngles(QAngle const&) = 0;
	/*417*/	virtual bool IsDucked(void)const = 0;
	/*418*/	virtual bool IsDucking(void)const = 0;
	/*419*/	virtual double GetFallVelocity(void) = 0;
	/*420*/	virtual void* RestrictPlayerPitch(void) = 0;
	/*421*/	virtual void* FlashlightIsOn(void) = 0;
	/*422*/	virtual float GetPlayerViewOffset(bool) = 0;
	/*423*/	virtual double GetSprintSpeed(void) = 0;
	/*424*/	virtual double GetWalkSpeed(void) = 0;
	/*425*/	virtual double GetSlowWalkSpeed(void) = 0;
	/*426*/	virtual double GetLadderSpeed(void) = 0;
	/*427*/	virtual double GetCrouchedWalkSpeed(void) = 0;
	/*428*/	virtual double GetDuckSpeed(void) = 0;
	/*429*/	virtual double GetUnDuckSpeed(void) = 0;
	/*430*/	virtual void SetSprintSpeed(float) = 0;
	/*431*/	virtual void SetWalkSpeed(float) = 0;
	/*432*/	virtual void SetSlowWalkSpeed(float) = 0;
	/*433*/	virtual void SetLadderSpeed(float) = 0;
	/*434*/	virtual void SetCrouchedWalkSpeed(float) = 0;
	/*435*/	virtual void SetDuckSpeed(float) = 0;
	/*436*/	virtual void SetUnDuckSpeed(float) = 0;
	/*437*/	virtual bool CanAttack(void) = 0;
	/*438*/	virtual int MouseWheel(void) = 0;
	/*439*/	virtual void* SetMouseWheel(int) = 0;
	/*440*/	virtual double GestureEndTime(void) = 0;

	// LMAO hard coding offsets
	// i'll eventually make a dumper

	/* If you want to update an offset, open IDA, search for the netvar (exemple search in strings for m_fflags)
	* Double click the occurence.
	* Find xref (press key) to a dq offset. https://i.imgur.com/qoyuLzS.png
	* Double click it.
	* There's your offset.
	* For exemple, in https://i.imgur.com/88fYuYY.png this case, the offset will be 0x01F4 AND NOT 0x010F4 !
	*/

	// Note to myself, before releasing x86, update x86 offsets...
		
	int getTeamNum() {
#ifdef _WIN64
		return *(int*)((uintptr_t)this + 0xD4); // m_iTeamNum
#else
		return *(int*)((uintptr_t)this + 0x9C); // m_iTeamNum
#endif
	}

	int getMoveType() {
#ifdef _WIN64
		return *(int*)((uintptr_t)this + 0x1F4); // https://i.imgur.com/NV5vl7c.png m_movetype
#else
		return *(int*)((uintptr_t)this + 0x178); // https://i.imgur.com/oRWjTg9.png
#endif
	}
	int getFlags() {
#ifdef _WIN64
		return *(int*)((uintptr_t)this + 0x440);
#else
		return *(int*)((uintptr_t)this + 0x350); // m_fFlags
#endif
	}
	unsigned int getTickBase() {
#ifdef _WIN64
		return *(unsigned int*)((uintptr_t)this + 0x2D48);
#else
		return *(unsigned int*)((uintptr_t)this + 0x350); // m_nTickBase // THIS IS UNSET!!!!!!!!!!
#endif
	}

	Vector getVelocity() {
#ifdef _WIN64
		return *(Vector*)((uintptr_t)this + 0x148);
#else
		return *(Vector*)((uintptr_t)this + 0xF4);
#endif
	}
	int hitboxSet()
	{
#ifdef _WIN64
		return *(int*)((uintptr_t)this + 0x16D0);
#else
		return *(int*)((uintptr_t)this + 0x1398); // m_nHitboxSet
#endif
	}
	void* GetModelPtr()
	{
		return *(void**)((uintptr_t)this + 0x16CC); // this might be outdated, didn't bother to check
	}
	QAngle& GetViewPunch()
	{
		// the method is C_BasePlayer::CalcPlayerView
		// the x86 sig is "E8 ? ? ? ? 8B CE E8 ? ? ? ? 84 C0 74 19"
		// the x64 sig is "E8 ? ? ? ? 48 8B CB E8 ? ? ? ? 4C 8B 7C 24 ? 4C 8B 74 24 ?"
		// Update 30/10/2021: Tests show that you can't sig CalcPlayerView anymore (tested in X64), so here's an alternative:
		// String XREF "Initialize All Game Systems", you'll find this https://i.imgur.com/rWlXdHI.png, so XREF vieweffects, and the first reference should look like this: https://i.imgur.com/rxXt4Wt.png. That's your CalcPlayerView
#ifdef _WIN64
		return *(QAngle*)((uintptr_t)this + 0x2A00);
#else
		return *(QAngle*)((uintptr_t)this + 0x24D0); // https://i.imgur.com/Y5hSyqS.png <- that's viewpunch offset. see screenshot above on how to get it, sig the stuff if u want to find it again
#endif
	}

	QAngle& GetAimPunch()
	{
#ifdef _WIN64
		//return *(QAngle*)((uintptr_t)this + 0x2A74);
#else
		return *(QAngle*)((uintptr_t)this + 0x250C); // that's aimpunch offset. viewpunch + 0x3C
#endif
	}
	bool IsDormant()
	{
#ifdef _WIN64
		return *(bool*)((uintptr_t)this + 0x1FA);
#else
		return *(bool*)((uintptr_t)this + 0x17E); // https://i.imgur.com/cRvUYqV.png Weirdly enough, I could not find GetDormant, but who cares as SetDormant gives the offset.
												  // Actually, i'm retarded... using the method stated above (string references) will simply give it out lmao https://i.imgur.com/8gwG3jv.png
#endif
	}

	float GetSimulationTime() {
#ifdef _WIN64
		return *(float*)((uintptr_t)this + 0xA0); // m_flSimulationTime
#else
		return *(float*)((uintptr_t)this + 0x68); // m_flSimulationTime
#endif
	}
};
