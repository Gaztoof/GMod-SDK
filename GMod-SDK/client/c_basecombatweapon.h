//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
//===========================================================================//

#ifndef COMBATWEAPON_SHARED_H
#define COMBATWEAPON_SHARED_H
#ifdef _WIN32
#pragma once
#endif

#include "../tier0/Vector.h"
#include "../mathlib/math_pfns.h"
#include "../tier0/basetypes.h"
#include "../tier0/shareddefs.h"
#include "../engine/trace.h"
struct WeaponProficiencyInfo_t
{
    float   spreadscale;
    float   bias;
};

enum WeaponProficiency_t
{
    WEAPON_PROFICIENCY_POOR = 0,
    WEAPON_PROFICIENCY_AVERAGE,
    WEAPON_PROFICIENCY_GOOD,
    WEAPON_PROFICIENCY_VERY_GOOD,
    WEAPON_PROFICIENCY_PERFECT,
};

// Hacky


class CBasePlayer;
class CBaseCombatCharacter;
class IPhysicsConstraint;
class CUserCmd;

// How many times to display altfire hud hints (per weapon)
#define WEAPON_ALTFIRE_HUD_HINT_COUNT   1
#define WEAPON_RELOAD_HUD_HINT_COUNT    1

//Start with a constraint in place (don't drop to floor)
#define SF_WEAPON_START_CONSTRAINED (1<<0)  
#define SF_WEAPON_NO_PLAYER_PICKUP  (1<<1)
#define SF_WEAPON_NO_PHYSCANNON_PUNT (1<<2)

//Percent
#define CLIP_PERC_THRESHOLD     0.75f   

// Put this in your derived class definition to declare it's activity table
// UNDONE: Cascade these?
#define DECLARE_ACTTABLE()      static acttable_t m_acttable[];\
     acttable_t *ActivityList( void );\
     int ActivityListCount( void );

 // You also need to include the activity table itself in your class' implementation:
 // e.g.
 //  acttable_t  CWeaponStunstick::m_acttable[] = 
 //  {
 //      { ACT_MELEE_ATTACK1, ACT_MELEE_ATTACK_SWING, TRUE },
 //  };
 //
 // The stunstick overrides the ACT_MELEE_ATTACK1 activity, replacing it with ACT_MELEE_ATTACK_SWING.
 // This animation is required for this weapon's operation.
 //

 // Put this after your derived class' definition to implement the accessors for the
 // activity table.
 // UNDONE: Cascade these?
typedef struct
{
    int         baseAct;
    int         weaponAct;
    bool        required;
} acttable_t;

class CHudTexture;
class Color;

namespace vgui2
{
    typedef unsigned long HFont;
}

// -----------------------------------------
//  Vector cones
// -----------------------------------------
// VECTOR_CONE_PRECALCULATED - this resolves to vec3_origin, but adds some
// context indicating that the person writing the code is not allowing
// FireBullets() to modify the direction of the shot because the shot direction
// being passed into the function has already been modified by another piece of
// code and should be fired as specified. See GetActualShotTrajectory(). 

// NOTE: The way these are calculated is that each component == sin (degrees/2)
#define VECTOR_CONE_PRECALCULATED   vec3_origin
#define VECTOR_CONE_1DEGREES        Vector( 0.00873, 0.00873, 0.00873 )
#define VECTOR_CONE_2DEGREES        Vector( 0.01745, 0.01745, 0.01745 )
#define VECTOR_CONE_3DEGREES        Vector( 0.02618, 0.02618, 0.02618 )
#define VECTOR_CONE_4DEGREES        Vector( 0.03490, 0.03490, 0.03490 )
#define VECTOR_CONE_5DEGREES        Vector( 0.04362, 0.04362, 0.04362 )
#define VECTOR_CONE_6DEGREES        Vector( 0.05234, 0.05234, 0.05234 )
#define VECTOR_CONE_7DEGREES        Vector( 0.06105, 0.06105, 0.06105 )
#define VECTOR_CONE_8DEGREES        Vector( 0.06976, 0.06976, 0.06976 )
#define VECTOR_CONE_9DEGREES        Vector( 0.07846, 0.07846, 0.07846 )
#define VECTOR_CONE_10DEGREES       Vector( 0.08716, 0.08716, 0.08716 )
#define VECTOR_CONE_15DEGREES       Vector( 0.13053, 0.13053, 0.13053 )
#define VECTOR_CONE_20DEGREES       Vector( 0.17365, 0.17365, 0.17365 )

//-----------------------------------------------------------------------------
// Purpose: Base weapon class, shared on client and server
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Purpose: Client side rep of CBaseTFCombatWeapon 
//-----------------------------------------------------------------------------
// Hacky
typedef enum {
	EMPTY,
	SINGLE,
	SINGLE_NPC,
	WPN_DOUBLE, // Can't be "DOUBLE" because windows.h uses it.
	DOUBLE_NPC,
	BURST,
	RELOAD,
	RELOAD_NPC,
	MELEE_MISS,
	MELEE_HIT,
	MELEE_HIT_WORLD,
	SPECIAL1,
	SPECIAL2,
	SPECIAL3,
	TAUNT,
	DEPLOY,

	// Add new shoot sound types here

	NUM_SHOOT_SOUND_TYPES,
} WeaponSound_t;
class C_BaseEntity;
class C_BasePlayer;
class C_BaseCombatWeapon
{
public:
	/*0*/	virtual void* destr1() = 0;
	/*2*/	virtual void* SetRefEHandle(void*) = 0;
	/*3*/	virtual void* GetRefEHandle(void)const = 0;
	/*4*/	virtual void* GetCollideable(void) = 0;
	/*5*/	virtual void* GetClientNetworkable(void) = 0;
	/*6*/	virtual void* GetClientRenderable(void) = 0;
	/*7*/	virtual void* GetIClientEntity(void) = 0;
	/*8*/	virtual void* GetBaseEntity(void) = 0;
	/*9*/	virtual void* GetClientThinkable(void) = 0;
	/*11*/	virtual void* GetAbsOrigin(void)const = 0;
	/*12*/	virtual void* GetAbsAngles(void)const = 0;
	/*13*/	virtual void* GetMouth(void) = 0;
	/*14*/	virtual void* GetSoundSpatialization(SpatializationInfo_t&) = 0;
	/*17*/	virtual void* GetClientClass(void) = 0;
	/*16*/	virtual void* YouForgotToImplementOrDeclareClientClass(void) = 0;
	/*18*/	virtual void* GetPredDescMap(void) = 0;
	/*19*/	virtual void* FireBullets(FireBulletsInfo_t const&) = 0;
	/*20*/	virtual void* ModifyFireBulletsDamage(CTakeDamageInfo*) = 0;
	/*21*/	virtual bool ShouldDrawUnderwaterBulletBubbles(void) = 0;
	/*22*/	virtual bool ShouldDrawWaterImpacts(void) = 0;
	/*23*/	virtual void* HandleShotImpactingWater(FireBulletsInfo_t const&, Vector const&, ITraceFilter*, Vector*) = 0;
	/*24*/	virtual void* GetBeamTraceFilter(void) = 0;
	/*25*/	virtual void* DispatchTraceAttack(CTakeDamageInfo const&, Vector const&, CGameTrace*, void*) = 0;
	/*26*/	virtual void* TraceAttack(CTakeDamageInfo const&, Vector const&, CGameTrace*, void*) = 0;
	/*27*/	virtual void* DoImpactEffect(CGameTrace&, int) = 0;
	/*28*/	virtual void* MakeTracer(Vector const&, CGameTrace const&, int) = 0;
	/*29*/	virtual void* GetTracerAttachment(void) = 0;
	/*30*/	virtual Color BloodColor(void) = 0;
	/*31*/	virtual void* GetTracerType(void) = 0;
	/*32*/	virtual void* Spawn(void) = 0;
	/*33*/	virtual void* SpawnClientEntity(void) = 0;
	/*34*/	virtual void* Precache(void) = 0;
	/*35*/	virtual void* Activate(void) = 0;
	/*36*/	virtual void* ParseMapData(void*) = 0;
	/*37*/	virtual void* KeyValue(char const*, char const*) = 0;
	/*38*/	virtual void* KeyValue(char const*, float) = 0;
	/*39*/	virtual void* KeyValue(char const*, Vector const&) = 0;
	/*40*/	virtual void* GetKeyValue(char const*, char*, int) = 0;
	/*41*/	virtual void* Init(int, int) = 0;
	/*42*/	virtual void* GetIClientUnknown(void) = 0;
	/*43*/	virtual void* GetBaseAnimating(void) = 0;
	/*44*/	virtual void* SetClassname(char const*) = 0;
	/*66*/	virtual void* TestCollision(Ray_t const&, unsigned int, CGameTrace&) = 0;
	/*67*/	virtual void* TestHitboxes(Ray_t const&, unsigned int, CGameTrace&) = 0;
	/*68*/	virtual void* GetAttackDamageScale(void) = 0;
	/*69*/	virtual void* NotifyShouldTransmit(void*) = 0;
	/*70*/	virtual void* PreDataUpdate(void*) = 0;
	/*71*/	virtual void* PostDataUpdate(void*) = 0;
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
	/*96*/	virtual void* VPhysicsGetObjectList(void**, int) = 0;
	/*97*/	virtual void* VPhysicsIsFlesh(void) = 0;
	/*102*/	virtual void* AddEntity(void) = 0;
	/*103*/	virtual void* GetLocalAngles(void)const = 0;
	/*104*/	virtual void* GetPrevLocalOrigin(void)const = 0;
	/*105*/	virtual void* GetPrevLocalAngles(void)const = 0;
	/*106*/	virtual void* CalcOverrideModelIndex(void) = 0;
	/*107*/	virtual void* WorldAlignMins(void)const = 0;
	/*108*/	virtual void* WorldAlignMaxs(void)const = 0;
	/*109*/	virtual void* WorldSpaceCenter(void)const = 0;
	/*110*/	virtual void* ComputeWorldSpaceSurroundingBox(Vector*, Vector*) = 0;
	/*111*/	virtual void* GetSolid(void)const = 0;
	/*112*/	virtual void* GetSolidFlags(void)const = 0;
	/*115*/	virtual void* GetAttachment(int, Vector&) = 0;
	/*117*/	virtual void* GetAttachmentVelocity(int, Vector&, Quaternion&) = 0;
	/*118*/	virtual void* GetTeam(void) = 0;
	/*119*/	virtual void* GetTeamNumber(void)const = 0;
	/*120*/	virtual void* ChangeTeam(int) = 0;
	/*121*/	virtual void* GetRenderTeamNumber(void) = 0;
	/*122*/	virtual void* InSameTeam(C_BaseEntity*) = 0;
	/*123*/	virtual void* InLocalTeam(void) = 0;
	/*124*/	virtual bool IsValidIDTarget(void) = 0;
	/*125*/	virtual void* GetIDString(void) = 0;
	/*126*/	virtual void* ModifyEmitSoundParams(EmitSound_t&) = 0;
	/*127*/	virtual void* InitializeAsClientEntity(char const*, void*) = 0;
	/*130*/	virtual void* OnPreDataChanged(void*) = 0;
	/*131*/	virtual void* GetClientVehicle(void) = 0;
	/*132*/	virtual void* GetAimEntOrigin(void*, Vector*, QAngle*) = 0;
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
	/*148*/	virtual void* DrawBrushModel(bool, int, bool) = 0;
	/*149*/	virtual void* GetTextureAnimationStartTime(void) = 0;
	/*150*/	virtual void* TextureAnimationWrapped(void) = 0;
	/*151*/	virtual void* SetNextClientThink(float) = 0;
	/*152*/	virtual void SetHealth(int) = 0;
	/*153*/	virtual int GetHealth(void)const = 0;
	/*154*/	virtual void* GetMaxHealth(void)const = 0;

	/*162*/	virtual void* AddDecal(Vector const&, Vector const&, Vector const&, int, int, bool, CGameTrace&, int) = 0;
	/*163*/	virtual bool IsClientCreated(void)const = 0;
	/*164*/	virtual void* UpdateOnRemove(void) = 0;
	/*165*/	virtual void* SUB_Remove(void) = 0;
	/*166*/	virtual void* SetPredictable(bool) = 0;
	/*167*/	virtual void* RestoreData(char const*, int, int) = 0;
	/*168*/	virtual void* DamageDecal(int, int) = 0;

	/*169*/	virtual void* DecalTrace(CGameTrace*, char const*) = 0;
	/*170*/	virtual void* ImpactTrace(CGameTrace*, int, char const*) = 0;
	/*171*/	virtual bool ShouldPredict(void) = 0;
	/*172*/	virtual void* Think(void) = 0;
	/*173*/	virtual void* CanBePoweredUp(void) = 0;
	/*174*/	virtual void* AttemptToPowerup(int, float, float, C_BaseEntity*, void*) = 0;
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
	/*192*/	virtual void* EyeAngles(void) = 0;
	/*193*/	virtual void* LocalEyeAngles(void) = 0;
	/*194*/	virtual Vector EarPosition(void) = 0;
	/*195*/	virtual bool ShouldCollide(int, int)const = 0;
	/*196*/	virtual void* GetViewOffset(void)const = 0;
	/*197*/	virtual void* SetViewOffset(Vector const&) = 0;
	/*198*/	virtual void* GetBody(void) = 0;
	/*199*/	virtual void* GetSkin(void) = 0;
	/*200*/	virtual void* GetModelInstance(void) = 0;
	/*202*/	virtual void* RenderHandle(void) = 0;
	/*210*/	virtual void* GetShadowUseOtherEntity(void)const = 0;
	/*211*/	virtual void* SetShadowUseOtherEntity(C_BaseEntity*) = 0;
	/*212*/	virtual void* AddRagdollToFadeQueue(void) = 0;
	/*213*/	virtual bool IsDeflectable(void) = 0;
	/*214*/	virtual void* GetStudioBody(void) = 0;
	/*215*/	virtual void* PerformCustomPhysics(Vector*, Vector*, QAngle*, QAngle*) = 0;
	/*216*/	virtual void* GetRenderClipPlane(void) = 0;


	/*218*/	virtual void* VPhysicsGetElement(int) = 0;
	/*219*/	virtual bool IsARagdoll(void) = 0;
	/*220*/	virtual void* SetMaterialOverride(char const*) = 0;
	/*221*/	virtual void* SetMaterialOverridePointer(IMaterial*) = 0;
	/*222*/	virtual void* GetMaterialOverridePointer(void) = 0;
	/*223*/	virtual void* GetMaterialOverride(void) = 0;
	/*224*/	virtual void* StartMaterialOverride(bool) = 0;
	/*225*/	virtual void* EndMaterialOverride(bool) = 0;
	/*226*/	virtual void* GetCreationTime(void) = 0;
	/*227*/	virtual bool IsPredicted(void)const = 0;
	/*228*/	virtual bool IsWeapon(void)const = 0;
	/*229*/	virtual bool IsVehicle(void)const = 0;
	/*230*/	virtual bool IsJeep(void)const = 0;
	/*231*/	virtual bool UsesLua(void) = 0;
	/*232*/	virtual void* GetLuaEntityType(void) = 0;
	/*233*/	virtual void PushEntity(void) = 0;
	/*234*/	virtual void Push_This_Entity(void) = 0;
	/*235*/	virtual void SetEntity(char const*, C_BaseEntity*) = 0;
	/*236*/	virtual void* GetParentPhysicsNum(void) = 0;
	/*237*/	virtual void* SetParentPhysicsNum(int) = 0;
	/*238*/	virtual void* StartMotionController(void) = 0;
	/*239*/	virtual void* StopMotionController(void) = 0;
	/*240*/	virtual void* AttachObjectToMotionController(void*) = 0;
	/*241*/	virtual void* DetachObjectFromMotionController(void*) = 0;
	/*242*/	virtual void* GetCustomisedRenderBounds(Vector&, Vector&) = 0;
	/*243*/	virtual void* SetCustomisedRenderBounds(Vector*, Vector*) = 0;
	/*244*/	virtual void* GetLuaScriptName(void) = 0;
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
	/*264*/	virtual void* SetBoneController(int, float) = 0;
	/*265*/	virtual void* GetBoneController(int) = 0;
	/*266*/	virtual void* GetPoseParameters(void*, float*) = 0;
	/*267*/	virtual void* BuildTransformations(void*, Vector*, Quaternion*, matrix3x4_t const&, int, void*, Vector const*) = 0;
	/*268*/	virtual void* ApplyBoneMatrixTransform(matrix3x4_t&) = 0;
	/*269*/	virtual void* UpdateIKLocks(float) = 0;
	/*270*/	virtual void* CalculateIKLocks(float) = 0;
	/*271*/	virtual void* InternalDrawModel(int) = 0;
	/*272*/	virtual void* OnInternalDrawModel(void*) = 0;
	/*273*/	virtual void* OnPostInternalDrawModel(void*) = 0;
	/*274*/	virtual void* ControlMouth2(void*) = 0;
	/*275*/	virtual void* DoAnimationEvents(void*) = 0;
	/*276*/	virtual void* FireEvent(Vector const&, QAngle const&, int, char const*) = 0;
	/*277*/	virtual void* FireObsoleteEvent(Vector const&, QAngle const&, int, char const*) = 0;
	/*278*/	virtual void* ModifyEventParticles(char const*) = 0;
	/*279*/	virtual void* ResetEventsParity(void) = 0;
	/*280*/	virtual void* DispatchMuzzleEffect(char const*, bool) = 0;
	/*281*/	virtual void* StandardBlendingRules(void*, Vector*, Quaternion*, float, int) = 0;
	/*282*/	virtual void* AccumulateLayers(void*, Vector*, Quaternion*, float) = 0;
	/*283*/	virtual void* ChildLayerBlend(Vector*, Quaternion*, float, int) = 0;
	/*284*/	virtual void* AttachEntityToBone(void*, int, Vector, QAngle) = 0;
	/*285*/	virtual void* NotifyBoneAttached(void*) = 0;
	/*286*/	virtual void* UpdateBoneAttachments(void) = 0;
	/*287*/	virtual bool IsRagdoll(void)const = 0;
	/*288*/	virtual void* BecomeRagdollOnClient(void) = 0;
	/*289*/	virtual void* SaveRagdollInfo(int, matrix3x4_t const&, void*) = 0;
	/*290*/	virtual void* RetrieveRagdollInfo(Vector*, Quaternion*) = 0;
	/*291*/	virtual void* GetRagdollInitBoneArrays(matrix3x4_t*, matrix3x4_t*, matrix3x4_t*, float) = 0;
	/*292*/	virtual void* RefreshCollisionBounds(void) = 0;
	/*293*/	virtual void* SetSequence(int) = 0;
	/*294*/	virtual void* StudioFrameAdvance(void) = 0;
	/*295*/	virtual void* FrameAdvance(float) = 0;
	/*296*/	virtual void* GetSequenceCycleRate(void*, int) = 0;
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
	/*308*/	virtual void* FormatViewModelAttachment(int, matrix3x4_t&) = 0;
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

	/*323*/	virtual void* GetSubType(void) = 0;
	/*324*/	virtual void* SetSubType(int) = 0;
	/*325*/	virtual void* Equip(void*) = 0;
	/*326*/	virtual void* Drop(Vector const&) = 0;
	/*327*/	virtual void* UpdateClientData(C_BasePlayer*) = 0;
	/*328*/	virtual bool IsAllowedToSwitch(void) = 0;
	/*329*/	virtual bool CanBeSelected(void) = 0;
	/*330*/	virtual void* VisibleInWeaponSelection(void) = 0;
	/*331*/	virtual bool HasAmmo(void) = 0;
	/*332*/	virtual void* SetPickupTouch(void) = 0;
	/*333*/	virtual void* DefaultTouch(C_BaseEntity*) = 0;
	/*334*/	virtual void* GiveTo(C_BaseEntity*) = 0;
	/*335*/	virtual bool ShouldDisplayAltFireHUDHint(void) = 0;
	/*336*/	virtual void* DisplayAltFireHudHint(void) = 0;
	/*337*/	virtual void* RescindAltFireHudHint(void) = 0;
	/*338*/	virtual bool ShouldDisplayReloadHUDHint(void) = 0;
	/*339*/	virtual void* DisplayReloadHudHint(void) = 0;
	/*340*/	virtual void* RescindReloadHudHint(void) = 0;
	/*341*/	virtual void* SetViewModelIndex(int) = 0;
	/*342*/	virtual void* SendWeaponAnim(int) = 0;
	/*343*/	virtual void* SendViewModelAnim(int) = 0;
	/*344*/	virtual void* SetViewModel(void) = 0;
	/*345*/	virtual bool HasWeaponIdleTimeElapsed(void) = 0;
	/*346*/	virtual void* SetWeaponIdleTime(float) = 0;
	/*347*/	virtual float GetWeaponIdleTime(void) = 0;
	/*348*/	virtual bool HasAnyAmmo(void) = 0;
	/*349*/	virtual bool HasPrimaryAmmo(void) = 0;
	/*350*/	virtual bool HasSecondaryAmmo(void) = 0;
	/*351*/	virtual void* CanHolster(void) = 0;
	/*352*/	virtual void* DefaultDeploy(char*, char*, int, char*) = 0;
	/*353*/	virtual void* CanDeploy(void) = 0;
	/*354*/	virtual void* Deploy(void) = 0;
	/*355*/	virtual void* Holster(C_BaseCombatWeapon*) = 0;
	/*356*/	virtual void* GetLastWeapon(void) = 0;
	/*357*/	virtual void* SetWeaponVisible(bool) = 0;
	/*358*/	virtual bool IsWeaponVisible(void) = 0;
	/*359*/	virtual void* ReloadOrSwitchWeapons(void) = 0;
	/*360*/	virtual void* OnActiveStateChanged(int) = 0;
	/*361*/	virtual void* HolsterOnDetach(void) = 0;
	/*362*/	virtual bool IsHolstered(void) = 0;
	/*363*/	virtual void* Detach(void) = 0;
	/*364*/	virtual void* ItemPreFrame(void) = 0;
	/*365*/	virtual void* ItemPostFrame(void) = 0;
	/*366*/	virtual void* ItemBusyFrame(void) = 0;
	/*367*/	virtual void* ItemHolsterFrame(void) = 0;
	/*368*/	virtual void* WeaponIdle(void) = 0;
	/*369*/	virtual void* HandleFireOnEmpty(void) = 0;
	/*370*/	virtual void* CanPerformSecondaryAttack(void)const = 0;
	/*371*/	virtual bool ShouldBlockPrimaryFire(void) = 0;
	/*372*/	virtual void* CreateMove(float, CUserCmd*, QAngle const&) = 0;
	/*373*/	virtual bool IsWeaponZoomed(void) = 0;
	/*374*/	virtual void* CheckReload(void) = 0;
	/*375*/	virtual void* FinishReload(void) = 0;
	/*376*/	virtual void* AbortReload(void) = 0;
	/*377*/	virtual void* Reload(void) = 0;
	/*378*/	virtual void* AutoFiresFullClip(void) = 0;
	/*379*/	virtual void* UpdateAutoFire(void) = 0;
	/*380*/	virtual void* PrimaryAttack(void) = 0;
	/*381*/	virtual void* SecondaryAttack(void) = 0;
	/*382*/	virtual void* GetPrimaryAttackActivity(void) = 0;
	/*383*/	virtual void* GetSecondaryAttackActivity(void) = 0;
	/*384*/	virtual void* GetDrawActivity(void) = 0;
	/*385*/	virtual void* GetDefaultAnimSpeed(void) = 0;
	/*386*/	virtual int GetBulletType(void) = 0;
	/*387*/	virtual const Vector& GetBulletSpread(void) = 0;
	/*388*/	virtual Vector GetBulletSpread(WeaponProficiency_t) = 0;
	/*389*/	virtual Vector GetSpreadBias(WeaponProficiency_t) = 0;
	/*390*/	virtual void* GetFireRate(void) = 0;
	/*391*/	virtual void* GetMinBurst(void) = 0;
	/*392*/	virtual void* GetMaxBurst(void) = 0;
	/*393*/	virtual void* GetMinRestTime(void) = 0;
	/*394*/	virtual void* GetMaxRestTime(void) = 0;
	/*395*/	virtual void* GetRandomBurst(void) = 0;
	/*396*/	virtual void WeaponSound(WeaponSound_t, float) = 0;
	/*397*/	virtual void StopWeaponSound(WeaponSound_t) = 0;
	/*398*/	virtual void* GetProficiencyValues(void) = 0;
	/*399*/	virtual void* GetMaxAutoAimDeflection(void) = 0;
	/*400*/	virtual void* WeaponAutoAimScale(void) = 0;
	/*401*/	virtual void* StartSprinting(void) = 0;
	/*402*/	virtual void* StopSprinting(void) = 0;
	/*403*/	virtual float GetDamage(float flDistance, int iLocation) = 0;
	/*404*/	virtual void* SetActivity(void*, float) = 0;
	/*405*/	virtual void* AddViewKick(void) = 0;
	/*406*/	virtual void* GetDeathNoticeName(void) = 0;
	/*407*/	virtual void* OnPickedUp(void*) = 0;
	/*408*/	virtual void* AddViewmodelBob(void*, Vector&, QAngle&) = 0;
	/*409*/	virtual void* CalcViewmodelBob(void) = 0;
	/*410*/	virtual void* GetControlPanelInfo(int, char const*&) = 0;
	/*411*/	virtual void* GetControlPanelClassName(int, char const*&) = 0;
	/*412*/	virtual bool ShouldShowControlPanels(void) = 0;
	/*413*/	virtual void* CanBePickedUpByNPCs(void) = 0;
	/*414*/	virtual void* GetSkinOverride(void)const = 0;
	/*415*/	virtual void* GetViewModel(int)const = 0;
	/*416*/	virtual void* GetWorldModel(void)const = 0;
	/*417*/	virtual void* GetAnimPrefix(void)const = 0;
	/*418*/	virtual void* GetMaxClip1(void)const = 0;
	/*419*/	virtual void* GetMaxClip2(void)const = 0;
	/*420*/	virtual void* GetDefaultClip1(void)const = 0;
	/*421*/	virtual void* GetDefaultClip2(void)const = 0;
	/*422*/	virtual void* GetWeight(void)const = 0;
	/*423*/	virtual void* AllowsAutoSwitchTo(void)const = 0;
	/*424*/	virtual void* AllowsAutoSwitchFrom(void)const = 0;
	/*425*/	virtual void* ForceWeaponSwitch(void)const = 0;
	/*426*/	virtual void* GetWeaponFlags(void)const = 0;
	/*427*/	virtual void* GetSlot(void) = 0;
	/*428*/	virtual void* GetPosition(void) = 0;
	/*429*/	virtual const char* GetName(void)const = 0;
	/*430*/	virtual const char* GetPrintName(void)const = 0;
	/*431*/	virtual void* GetShootSound(int)const = 0;
	/*432*/	virtual void* GetRumbleEffect(void)const = 0;
	/*433*/	virtual void* UsesClipsForAmmo1(void)const = 0;
	/*434*/	virtual void* UsesClipsForAmmo2(void)const = 0;
	/*435*/	virtual void* GetHoldType(void)const = 0;
	/*436*/	virtual void* SetHoldType(char const*) = 0;
	/*437*/	virtual void* GetEncryptionKey(void) = 0;
	/*438*/	virtual void* GetPrimaryAmmoType(void)const = 0;
	/*439*/	virtual void* GetSecondaryAmmoType(void)const = 0;
	/*440*/	virtual void* Clip1(void) = 0;
	/*441*/	virtual void* Clip2(void) = 0;
	/*442*/	virtual void* GetSpriteActive(void)const = 0;
	/*443*/	virtual void* GetSpriteInactive(void)const = 0;
	/*444*/	virtual void* GetSpriteAmmo(void)const = 0;
	/*445*/	virtual void* GetSpriteAmmo2(void)const = 0;
	/*446*/	virtual void* GetSpriteCrosshair(void)const = 0;
	/*447*/	virtual void* GetSpriteAutoaim(void)const = 0;
	/*448*/	virtual void* GetSpriteZoomedCrosshair(void)const = 0;
	/*449*/	virtual void* GetSpriteZoomedAutoaim(void)const = 0;
	/*450*/	virtual void* ActivityOverride(void*, bool*) = 0;
	/*451*/	virtual void* ActivityList(void) = 0;
	/*452*/	virtual void* ActivityListCount(void) = 0;
	/*453*/	virtual void* PoseParameterOverride(bool) = 0;
	/*454*/	virtual void* PoseParamList(int&) = 0;
	/*455*/	virtual bool ShouldUseLargeViewModelVROverride(void) = 0;
	/*456*/	virtual void* OnFireEvent(void*, Vector const&, QAngle const&, int, char const*) = 0;
	/*457*/	virtual void* RestartParticleEffect(void) = 0;
	/*458*/	virtual void* Redraw(void) = 0;
	/*459*/	virtual void* ViewModelDrawn(void*) = 0;
	/*460*/	virtual void* NothingLiterally(void) = 0;
	/*460*/	virtual void* RenderScreen(void) = 0;
	/*461*/	virtual void* DrawCrosshair(void) = 0;
	/*462*/	virtual bool ShouldDrawCrosshair(void) = 0;
	/*463*/	virtual bool IsCarriedByLocalPlayer(void) = 0;
	/*464*/	virtual bool ShouldDrawUsingViewModel(void) = 0;
	/*465*/	virtual bool IsActiveByLocalPlayer(void) = 0;
	/*466*/	virtual bool ShouldDrawPickup(void) = 0;

	/*467*/	virtual void* LITERALLYNOTHING(void) = 0;

	/*467*/	virtual void* HandleInput(void) = 0;
	/*468*/	virtual void* OverrideMouseInput(float*, float*) = 0;
	/*469*/	virtual void* KeyInput(int, ButtonCode_t, char const*) = 0;
	/*470*/	virtual void* AddLookShift(void) = 0;
	/*471*/	virtual void* GetViewmodelBoneControllers(void*, float*) = 0;
	/*472*/	virtual void* GetWorldModelIndex(void) = 0;
	/*473*/	virtual void* GetWeaponCrosshairScale(float&) = 0;
	/*474*/	virtual void* ViewModel_IsTransparent(void) = 0;
	/*475*/	virtual void* ViewModel_IsUsingFBTexture(void) = 0;
	/*476*/	virtual bool IsOverridingViewmodel(void) = 0;
	/*477*/	virtual void* DrawOverriddenViewmodel(void*, int) = 0;
	/*478*/	virtual void* ThirdPersonSwitch(bool) = 0;
	/*479*/	virtual void* CanLower(void) = 0;
	/*480*/	virtual void* Ready(void) = 0;
	/*481*/	virtual void* Lower(void) = 0;
	/*482*/	virtual void* HideThink(void) = 0;
	/*483*/	virtual void* CanReload(void) = 0;
	/*484*/	virtual void* NetworkStateChanged_m_nNextThinkTick(void) = 0;
	/*485*/	virtual void* NetworkStateChanged_m_nNextThinkTick(void*) = 0;
	/*486*/	virtual void* GetPlayerDamage(void) = 0;
	/*487*/	virtual void* EquipAmmo(C_BaseEntity*) = 0;
	/*488*/	virtual bool ShouldDropOnDie(void) = 0;
	/*489*/	virtual bool ShouldDrawViewModel(void) = 0;
	/*490*/	virtual void* GetLastShootTime(void) = 0;	
	/*492*/	virtual void* GetFOV(float) = 0;
	/*493*/	virtual void* GetTracerOrigin(Vector&) = 0;
	/*494*/	virtual void* OverrideMouseInput(void) = 0;
	/*495*/	virtual void* DrawWeaponSelection(int, int, int, int, int) = 0;
	/*496*/	virtual void* DrawHUD(void) = 0;
	/*498*/	virtual bool ShouldDrawAmmo(void) = 0;
	/*499*/	virtual void* GetViewModelFOV(float) = 0;
	/*500*/	virtual void* GetSwayScale(void) = 0;
	/*501*/	virtual void* GetWeaponBobScale(void) = 0;
	/*502*/	virtual bool ShouldFlipViewModel(unsigned int, bool) = 0;
	/*503*/	virtual bool ShouldDrawAccurateCrosshair(void) = 0;
	/*504*/	virtual void* DrawCrosshair(float, float) = 0;
	/*506*/	virtual void* WasDropped(void) = 0;
	/*507*/	virtual void* MarkAsDropped(void) = 0;

	int PrimaryAmmoCount() { 
		if (!this) return 0; 
#ifdef _WIN64
		return *(int*)((uintptr_t)this + 0x1C48);
#else
		return *(int*)((uintptr_t)this + 0x1818); // m_iClip1
#endif
	}
	int SecondaryAmmoCount() {
		if (!this) return 0;
#ifdef _WIN64
		return *(int*)((uintptr_t)this + 0x1C4C);
#else
		return *(int*)((uintptr_t)this + 0x181C); // m_iClip2
#endif
	}
	float NextPrimaryAttack() {
		if (!this) return 0;
#ifdef _WIN64
		return *(float*)((uintptr_t)this + 0x1BFC);
#else
		return *(float*)((uintptr_t)this + 0x17D4); // m_flNextPrimaryAttack
#endif
	}
	float NextSecondaryAttack() {
		if (!this) return 0;
#ifdef _WIN64
		return *(float*)((uintptr_t)this + 0x1C00);
#else
		return *(float*)((uintptr_t)this + 0x17D4); // m_flNextSecondaryAttack
#endif
	}


};

#endif // COMBATWEAPON_SHARED_H
