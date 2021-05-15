#pragma once

#include <Windows.h>

#include <string_view>
#include <psapi.h>
#include <signal.h>
#include <limits>
#include <array>

PVOID VMTHook(PVOID** src, PVOID dst, int index);
const char* findPattern(const char* moduleName, std::string_view pattern) noexcept;

char* GetRealFromRelative(char* address, int offset); // Address must be a CALL instruction, not a pointer! And offset the offset to the bytes you want to retrieve.

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
    uintptr_t instruction = ((*(uintptr_t**)(address))[index] + offset + 2);
    return **(T***)(*(uintptr_t*)(instruction));
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
    uintptr_t instruction = (address + offset + 2);
    return **(T***)(*(uintptr_t*)(instruction));
#endif
}