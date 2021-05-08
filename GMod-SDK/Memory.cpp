#include "Memory.h"

PVOID VMTHook(PVOID** src, PVOID dst, int index)
{
	// I could do tramp hooking instead of VMT hooking, but I came across a few problems while implementing my tramp, and VMT just makes it easier.
	PVOID* VMT = *src;
	PVOID ret = (VMT[index]);
	DWORD originalProtection;
	VirtualProtect(&VMT[index], sizeof(PVOID), PAGE_EXECUTE_READWRITE, &originalProtection);
	VMT[index] = dst;
	VirtualProtect(&VMT[index], sizeof(PVOID), originalProtection, &originalProtection);
	return ret;
}

 // credits to osiris for the following
static auto generateBadCharTable(std::string_view pattern) noexcept
{
    std::array<std::size_t, 256> table;

    auto lastWildcard = pattern.rfind('?');
    if (lastWildcard == std::string_view::npos)
        lastWildcard = 0;

    const auto defaultShift = (std::max)(std::size_t(1), pattern.length() - 1 - lastWildcard);
    table.fill(defaultShift);

    for (auto i = lastWildcard; i < pattern.length() - 1; ++i)
        table[static_cast<std::uint8_t>(pattern[i])] = pattern.length() - 1 - i;

    return table;
}
uintptr_t findPattern(const char* moduleName, std::string_view pattern) noexcept
{
    PVOID moduleBase = 0;
    std::size_t moduleSize = 0;
    if (HMODULE handle = GetModuleHandleA(moduleName))
        if (MODULEINFO moduleInfo; GetModuleInformation(GetCurrentProcess(), handle, &moduleInfo, sizeof(moduleInfo)))
        {
            moduleBase = moduleInfo.lpBaseOfDll;
            moduleSize = moduleInfo.SizeOfImage;
        }


    if (moduleBase && moduleSize) {
        const auto lastIdx = pattern.length() - 1;
        const auto badCharTable = generateBadCharTable(pattern);

        auto start = static_cast<const char*>(moduleBase);
        const auto end = start + moduleSize - pattern.length();

        while (start <= end) {
            int i = lastIdx;
            while (i >= 0 && (pattern[i] == '?' || start[i] == pattern[i]))
                --i;

            if (i < 0)
                return reinterpret_cast<std::uintptr_t>(start);

            start += badCharTable[static_cast<std::uint8_t>(start[lastIdx])];
        }
    }
    MessageBoxA(NULL, "Failed to find a pattern, let the dev know asap!", "ERROR", MB_OK | MB_ICONWARNING);
    return 0;
}