#pragma once

#include <Windows.h>

#include <string_view>
#include <psapi.h>
#include <signal.h>
#include <limits>
#include <array>

PVOID VMTHook(PVOID** src, PVOID dst, int index);
uintptr_t findPattern(const char* moduleName, std::string_view pattern) noexcept;