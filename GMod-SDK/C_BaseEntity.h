#pragma once
#include "Vector.h"
#include "soundinfo.h"
#include "shareddefs.h"
#include "IEngineTrace.h"
#include "takedamageinfo.h"
/*#include "IClientEntity.h"
#include "IHandleEntity.h"
#include "IClientUnknown.h"

class C_BaseEntity : public IClientEntity
{
public:

	/*19* 	virtual void* FireBullets(FireBulletsInfo_t const&) = 0;
	/*20* 	virtual void* ModifyFireBulletsDamage(CTakeDamageInfo*) = 0;
	/*21* 	virtual bool ShouldDrawUnderwaterBulletBubbles(void) = 0;
	/*22* 	virtual bool ShouldDrawWaterImpacts(void) = 0;
	/*23* 	virtual void* HandleShotImpactingWater(FireBulletsInfo_t const&, Vector const&, ITraceFilter*, Vector*) = 0;
	/*24* 	virtual void* GetBeamTraceFilter(void) = 0;
	/*25* 	virtual void* DispatchTraceAttack(CTakeDamageInfo const&, Vector const&, CGameTrace*, void*) = 0;
	/*26* 	virtual void* TraceAttack(CTakeDamageInfo const&, Vector const&, CGameTrace*, void*) = 0;
	/*27* 	virtual void* DoImpactEffect(CGameTrace&, int) = 0;
	/*28* 	virtual void* MakeTracer(Vector const&, CGameTrace const&, int) = 0;
	/*29* 	virtual void* GetTracerAttachment(void) = 0;
	/*30* 	virtual Color BloodColor(void) = 0;
	/*31* 	virtual void* GetTracerType(void) = 0;
	/*32* 	virtual void* Spawn(void) = 0;
	/*33* 	virtual void* SpawnClientEntity(void) = 0;
	/*34* 	virtual void* Precache(void) = 0;
	/*35* 	virtual void* Activate(void) = 0;
	/*36* 	virtual void* ParseMapData(void*) = 0;
	/*37* 	virtual void* KeyValue(char const*, char const*) = 0;
	/*38* 	virtual void* KeyValue(char const*, float) = 0;
	/*39* 	virtual void* KeyValue(char const*, Vector const&) = 0;
	/*40* 	virtual void* GetKeyValue(char const*, char*, int) = 0;
	/*41* 	virtual void* Init(int, int) = 0;
	/*42* 	virtual void* GetIClientUnknown(void) = 0;
	/*43* 	virtual void* GetBaseAnimating(void) = 0;
	/*44* 	virtual void* SetClassname(char const*) = 0;
	/*66* 	virtual void* TestCollision(Ray_t const&, unsigned int, CGameTrace&) = 0;
	/*67* 	virtual void* TestHitboxes(Ray_t const&, unsigned int, CGameTrace&) = 0;
	/*68* 	virtual void* GetAttackDamageScale(void) = 0;
	/*69* 	virtual void* NotifyShouldTransmit(void*) = 0;
	/*70* 	virtual void* PreDataUpdate(void*) = 0;
	/*71* 	virtual void* PostDataUpdate(void*) = 0;
	/*83* 	virtual void* GetThinkHandle(void) = 0;
	/*84* 	virtual void* SetThinkHandle(void*) = 0;
	/*85* 	virtual bool ShouldSavePhysics(void) = 0;
	/*86* 	virtual void* OnSave(void) = 0;
	/*87* 	virtual void* OnRestore(void) = 0;
	/*88* 	virtual void* ObjectCaps(void) = 0;
	/*89* 	virtual void* Save(void*) = 0;
	/*90* 	virtual void* Restore(void*) = 0;
	/*91* 	virtual void* CreateVPhysics(void) = 0;
	/*92* 	virtual void* VPhysicsDestroyObject(void) = 0;
	/*93* 	virtual void* GMOD_VPhysicsTest(void*) = 0;
	/*94* 	virtual void* GMOD_GetPhysBoneMatrix(int) = 0;
	/*95* 	virtual void* VPhysicsUpdate(void*) = 0;
	/*96* 	virtual void* VPhysicsGetObjectList(void**, int) = 0;
	/*97* 	virtual void* VPhysicsIsFlesh(void) = 0;
	/*102 /	virtual void* AddEntity(void) = 0;
	/*103 /	virtual void* GetLocalAngles(void)const = 0;
	/*104 /	virtual void* GetPrevLocalOrigin(void)const = 0;
	/*105 /	virtual void* GetPrevLocalAngles(void)const = 0;
	/*106 /	virtual void* CalcOverrideModelIndex(void) = 0;
	/*107 /	virtual void* WorldAlignMins(void)const = 0;
	/*108 /	virtual void* WorldAlignMaxs(void)const = 0;
	/*109 /	virtual void* WorldSpaceCenter(void)const = 0;
	/*110 /	virtual void* ComputeWorldSpaceSurroundingBox(Vector*, Vector*) = 0;
	/*111 /	virtual void* GetSolid(void)const = 0;
	/*112 /	virtual void* GetSolidFlags(void)const = 0;
	/*115 /	virtual void* GetAttachment(int, Vector&) = 0;
	/*117 /	virtual void* GetAttachmentVelocity(int, Vector&, Quaternion&) = 0;
	/*118 /	virtual void* GetTeam(void) = 0;
	/*119 /	virtual void* GetTeamNumber(void)const = 0;
	/*120 /	virtual void* ChangeTeam(int) = 0;
	/*121 /	virtual void* GetRenderTeamNumber(void) = 0;
	/*122 /	virtual void* InSameTeam(C_BaseEntity*) = 0;
	/*123 /	virtual void* InLocalTeam(void) = 0;
	/*124 /	virtual bool IsValidIDTarget(void) = 0;
	/*125 /	virtual void* GetIDString(void) = 0;
	/*126 /	virtual void* ModifyEmitSoundParams(EmitSound_t&) = 0;
	/*127 /	virtual void* InitializeAsClientEntity(char const*, void*) = 0;
	/*130 /	virtual void* OnPreDataChanged(void*) = 0;
	/*131 /	virtual void* GetClientVehicle(void) = 0;
	/*132 /	virtual void* GetAimEntOrigin(void*, Vector*, QAngle*) = 0;
	/*133 /	virtual void* GetOldOrigin(void) = 0;
	/*134 /	virtual void* GetRenderGroup(void) = 0;
	/*135 /	virtual void* GetToolRecordingState(void*) = 0;
	/*136 /	virtual void* CleanupToolRecordingState(void*) = 0;
	/*137 /	virtual void* GetCollideType(void) = 0;
	/*138 /	virtual bool ShouldDraw(void) = 0;
	/*140 /	virtual void* OnLatchInterpolatedVariables(int) = 0;
		  
	/*274 /	virtual void* ControlMouth(void*) = 0;
		  
	/*142 /	virtual void* OnNewParticleEffect(char const*, void*) = 0;
	/*143 /	virtual void* ResetLatched(void) = 0;
	/*144 /	virtual void* Interpolate(float) = 0;
	/*145 /	virtual bool IsSubModel(void) = 0;
	/*146 /	virtual void* CreateLightEffects(void) = 0;
	/*147 /	virtual void* Clear(void) = 0;
	/*148 /	virtual void* DrawBrushModel(bool, int, bool) = 0;
	/*149 /	virtual void* GetTextureAnimationStartTime(void) = 0;
	/*150 /	virtual void* TextureAnimationWrapped(void) = 0;
	/*151 /	virtual void* SetNextClientThink(float) = 0;
	/*152 /	virtual void SetHealth(int) = 0;
	/*153 /	virtual int GetHealth(void)const = 0;
	/*154 /	virtual void* GetMaxHealth(void)const = 0;
		  
	/*162 /	virtual void* AddDecal(Vector const&, Vector const&, Vector const&, int, int, bool, CGameTrace&, int) = 0;
	/*163 /	virtual bool IsClientCreated(void)const = 0;
	/*164 /	virtual void* UpdateOnRemove(void) = 0;
	/*165 /	virtual void* SUB_Remove(void) = 0;
	/*166 /	virtual void* SetPredictable(bool) = 0;
	/*167 /	virtual void* RestoreData(char const*, int, int) = 0;
	/*168 /	virtual void* DamageDecal(int, int) = 0;
		  
	/*169 /	virtual void* DecalTrace(CGameTrace*, char const*) = 0;
	/*170 /	virtual void* ImpactTrace(CGameTrace*, int, char const*) = 0;
	/*171 /	virtual bool ShouldPredict(void) = 0;
	/*172 /	virtual void* Think(void) = 0;
	/*173 /	virtual void* CanBePoweredUp(void) = 0;
	/*174 /	virtual void* AttemptToPowerup(int, float, float, C_BaseEntity*, void*) = 0;
	/*175 /	virtual bool IsCurrentlyTouching(void)const = 0;
	/*176 /	virtual void* StartTouch(C_BaseEntity*) = 0;
	/*177 /	virtual void* Touch(C_BaseEntity*) = 0;
	/*178 /	virtual void* EndTouch(C_BaseEntity*) = 0;
	/*179 /	virtual void* PhysicsSolidMaskForEntity(void)const = 0;
	/*180 /	virtual void* PhysicsSimulate(void) = 0;
	/*181 /	virtual bool IsAlive(void) = 0;
	/*182 /	virtual bool IsPlayer(void)const = 0;
	/*183 /	virtual bool IsBaseCombatCharacter(void) = 0;
	/*184 /	virtual void* MyCombatCharacterPointer(void) = 0;
	/*185 /	virtual bool IsNPC(void) = 0;
	/*186 /	virtual bool IsNextBot(void) = 0;
	/*187 /	virtual bool IsBaseObject(void)const = 0;
	/*188 /	virtual bool IsBaseCombatWeapon(void)const = 0;
	/*189 /	virtual void* MyCombatWeaponPointer(void) = 0;
	/*190 /	virtual bool IsBaseTrain(void)const = 0;
	/*191 /	virtual Vector EyePosition(void) = 0;
	/*192 /	virtual void* EyeAngles(void) = 0;
	/*193 /	virtual void* LocalEyeAngles(void) = 0;
	/*194 /	virtual Vector EarPosition(void) = 0;
	/*195 /	virtual bool ShouldCollide(int, int)const = 0;
	/*196 /	virtual void* GetViewOffset(void)const = 0;
	/*197 /	virtual void* SetViewOffset(Vector const&) = 0;
	/*198 /	virtual void* GetBody(void) = 0;
	/*199 /	virtual void* GetSkin(void) = 0;
	/*200 /	virtual void* GetModelInstance(void) = 0;
	/*202 /	virtual void* RenderHandle(void) = 0;
	/*210 /	virtual void* GetShadowUseOtherEntity(void)const = 0;
	/*211 /	virtual void* SetShadowUseOtherEntity(C_BaseEntity*) = 0;
	/*212 /	virtual void* AddRagdollToFadeQueue(void) = 0;
	/*213 /	virtual bool IsDeflectable(void) = 0;
	/*214 /	virtual void* GetStudioBody(void) = 0;
	/*215 /	virtual void* PerformCustomPhysics(Vector*, Vector*, QAngle*, QAngle*) = 0;
	/*216 /	virtual void* GetRenderClipPlane(void) = 0;
};*/