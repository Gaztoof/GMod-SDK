//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=====================================================================================//
#include "../tier0/Vector.h"
#include <Windows.h>

#ifndef _MATH_PFNS_H_
#define _MATH_PFNS_H_

#if defined( _X360 )
#include <xboxmath.h>
#endif

#if !defined( _X360 )
typedef unsigned char BYTE;

// These globals are initialized by mathlib and redirected based on available fpu features
extern float (*pfSqrt)(float x);
extern float (*pfRSqrt)(float x);
extern float (*pfRSqrtFast)(float x);
extern void  (*pfFastSinCos)(float x, float* s, float* c);
extern float (*pfFastCos)(float x);

// The following are not declared as macros because they are often used in limiting situations,
// and sometimes the compiler simply refuses to inline them for some reason
#define FastSqrt(x)			sqrtf(x)
#define	FastRSqrt(x)		1.0f / sqrtf(x)
#define FastRSqrtFast(x)    1.0f / sqrtf(x)
#define FastSinCos(x,s,c)   0
#define FastCos(x)			cosf(x)

#if defined(__i386__) || defined(_M_IX86)
// On x86, the inline FPU or SSE sqrt instruction is faster than
// the overhead of setting up a function call and saving/restoring
// the FPU or SSE register state and can be scheduled better, too.
#undef FastSqrt
#define FastSqrt(x)			::sqrtf(x)
#endif

#endif // !_X360

#if defined( _X360 )

FORCEINLINE float _VMX_Sqrt(float x)
{
	return __fsqrts(x);
}

FORCEINLINE float _VMX_RSqrt(float x)
{
	float rroot = __frsqrte(x);

	// Single iteration NewtonRaphson on reciprocal square root estimate
	return (0.5f * rroot) * (3.0f - (x * rroot) * rroot);
}

FORCEINLINE float _VMX_RSqrtFast(float x)
{
	return __frsqrte(x);
}

FORCEINLINE void _VMX_SinCos(float a, float* pS, float* pC)
{
	XMScalarSinCos(pS, pC, a);
}

FORCEINLINE float _VMX_Cos(float a)
{
	return XMScalarCos(a);
}

// the 360 has fixed hw and calls directly
#define FastSqrt(x)			_VMX_Sqrt(x)
#define	FastRSqrt(x)		_VMX_RSqrt(x)
#define FastRSqrtFast(x)	_VMX_RSqrtFast(x)
#define FastSinCos(x,s,c)	_VMX_SinCos(x,s,c)
#define FastCos(x)			_VMX_Cos(x)

#endif // _X360

/*struct cplane_t
{
	float normal[3];
	float	dist;
	BYTE	type;			// for fast side tests
	BYTE	signbits;		// signx + (signy<<1) + (signz<<1)
	BYTE	pad[2];

#ifdef VECTOR_NO_SLOW_OPERATIONS
	cplane_t() {}

private:
	// No copy constructors allowed if we're in optimal mode
	cplane_t(const cplane_t& vOther);
#endif
};

// structure offset for asm code
#define CPLANE_NORMAL_X			0
#define CPLANE_NORMAL_Y			4
#define CPLANE_NORMAL_Z			8
#define CPLANE_DIST				12
#define CPLANE_TYPE				16
#define CPLANE_SIGNBITS			17
#define CPLANE_PAD0				18
#define CPLANE_PAD1				19*/


const float PI = 3.141592654f;
inline constexpr float DEG2RAD(float fDegrees) { return fDegrees * (PI / 180.0f); }
inline constexpr float RAD2DEG(float fRadians) { return fRadians * (180.0f / PI); }
inline constexpr float ANG2DEG(float fAngle) { if (fAngle < 0.f) return fAngle + 360.f; else return fAngle; }


#endif // _MATH_PFNS_H_