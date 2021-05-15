#pragma once

// Auto reconstructed from vtable block @ 0x00019438
// from "libvstdlib.dylib", by ida_vtables.idc
// Modified VTable dumper script obviously by t.me/Gaztoof.
class CUniformRandomStream
{
public:
	//Don't forget the constructor.
	/*0*/	virtual void SetSeed(int) = 0;
	/*1*/	virtual float RandomFloat(float, float) = 0;
	/*2*/	virtual int RandomInt(int, int) = 0;
	/*3*/	virtual float RandomFloatExp(float, float, float) = 0;
};