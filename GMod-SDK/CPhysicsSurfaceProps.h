#pragma once


struct surfacephysicsparams_t
{
	float friction;
	float elasticity;
	float density;
	float thickness;
	float dampening;
};
struct surfaceaudioparams_t
{
	// sounds / audio data
	float			reflectivity;		// like elasticity, but how much sound should be reflected by this surface
	float			hardnessFactor;	// like elasticity, but only affects impact sound choices
	float			roughnessFactor;	// like friction, but only affects scrape sound choices

// audio thresholds
	float			roughThreshold;	// surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
	float			hardThreshold;	// surface hardness > this causes "hard" impacts, < this causes "soft" impacts
	float			hardVelocityThreshold;	// collision velocity > this causes "hard" impacts, < this causes "soft" impacts
									// NOTE: Hard impacts must meet both hardnessFactor AND velocity thresholds
};
struct surfacesoundnames_t
{
	unsigned short	stepleft;
	unsigned short	stepright;

	unsigned short	impactSoft;
	unsigned short	impactHard;

	unsigned short	scrapeSmooth;
	unsigned short	scrapeRough;

	unsigned short	bulletImpact;
	unsigned short	rolling;

	unsigned short	breakSound;
	unsigned short	strainSound;
};

struct surfacegameprops_t
{
	char pad02[0xC];
	float maxSpeedFactor;
	float jumpFactor;
	char pad00[0x4];
	float flPenetrationModifier;
	float flDamageModifier;
	unsigned short material;
	char pad01[0x3];

};

struct surfacedata_t
{
	surfacephysicsparams_t	physics;	// physics parameters
	surfaceaudioparams_t	audio;		// audio parameters
	surfacesoundnames_t		sounds;		// names of linked sounds
	surfacegameprops_t		game;		// Game data / properties


};

// Auto reconstructed from vtable block @ 0x00111068
// from "vphysics.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class CPhysicsSurfaceProps
{
public:
	/*0*/	virtual void Destr() = 0;
	/*1*/	virtual int ParseSurfaceData(char const* pFilename, char const* pTextfile) = 0;
	/*2*/	virtual int SurfacePropCount(void)const = 0;
	/*3*/	virtual int GetSurfaceIndex(char const* pSurfacePropName)const = 0;
	/*4*/	virtual void GetPhysicsProperties(int surfaceDataIndex, float* density, float* thickness, float* friction , float* elasticity)const = 0;
	/*5*/	virtual surfacedata_t* GetSurfaceData(int surfaceDataIndex) = 0;
	/*6*/	virtual const char* GetString(unsigned short stringTableIndex)const = 0;
	/*7*/	virtual const char* GetPropName(int surfaceDataIndex)const = 0;
	/*8*/	virtual void SetWorldMaterialIndexTable(int* pMapArray, int mapSize) = 0;
	/*9*/	virtual void GetPhysicsParameters(int surfaceDataIndex, surfacephysicsparams_t* pParamsOut)const = 0;
	/*10*/	virtual void GetIVPMaterial(int) = 0;
	/*11*/	virtual void GetIVPMaterialIndex(void const*)const = 0;
	/*12*/	virtual void GetIVPManager(void) = 0;
	/*13*/	virtual void RemapIVPMaterialIndex(int)const = 0;
	/*14*/	virtual void GetReservedMaterialName(int)const = 0;
};