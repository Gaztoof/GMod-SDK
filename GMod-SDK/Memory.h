#pragma once

#include <Windows.h>

#include <string_view>
#include <psapi.h>
#include <signal.h>
#include <limits>
#include <array>

void BytePatch(PVOID source, BYTE newValue);

template<typename T>
T VMTHook(PVOID** src, PVOID dst, int index)
{
    // I could do tramp hooking instead of VMT hooking, but I came across a few problems while implementing my tramp, and VMT just makes it easier.
    PVOID* VMT = *src;
    PVOID ret = (VMT[index]);
    DWORD originalProtection;
    VirtualProtect(&VMT[index], sizeof(PVOID), PAGE_EXECUTE_READWRITE, &originalProtection);
    VMT[index] = dst;
    VirtualProtect(&VMT[index], sizeof(PVOID), originalProtection, &originalProtection);
    return (T)ret;
};
void RestoreVMTHook(PVOID** src, PVOID dst, int index);

const char* findPattern(const char* moduleName, std::string_view pattern) noexcept;

char* GetRealFromRelative(char* address, int offset, int instructionSize = 6, bool isRelative = true); // Address must be a CALL instruction, not a pointer! And offset the offset to the bytes you want to retrieve.

template<typename T>
T* GetVMT(uintptr_t address, int index, uintptr_t offset) // Address must be a VTable pointer, not a VTable !
{
#ifdef _WIN64
    uintptr_t step = 3;
    uintptr_t instructionSize = 7;
    uintptr_t instruction = ((*(uintptr_t**)(address))[index] + offset);

    uintptr_t relativeAddress = *(DWORD*)(instruction + step);
    uintptr_t realAddress = instruction + instructionSize + relativeAddress;
    return *(T**)(realAddress);
#else
    uintptr_t instruction = ((*(uintptr_t**)(address))[index] + offset);
    return *(T**)(*(uintptr_t*)(instruction));
#endif
}
template<typename T>
T* GetVMT(uintptr_t address, uintptr_t offset) // This doesn't reads from the VMT, address must be the function's base ! Not a pointer!
{
#ifdef _WIN64
    uintptr_t step = 3;
    uintptr_t instructionSize = 7;
    uintptr_t instruction = address + offset;

    uintptr_t relativeAddress = *(DWORD*)(instruction + step);
    uintptr_t realAddress = instruction + instructionSize + relativeAddress;
    return *(T**)(realAddress);
#else
    uintptr_t instruction = (address + offset);
    return *(T**)(*(uintptr_t*)(instruction));
#endif
}