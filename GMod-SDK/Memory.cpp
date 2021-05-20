#include "Memory.h"

void BytePatch(PVOID source, BYTE newValue)
{
    DWORD originalProtection;
    VirtualProtect(source, sizeof(PVOID), PAGE_EXECUTE_READWRITE, &originalProtection);
    *(BYTE*)(source) = newValue;
    VirtualProtect(source, sizeof(PVOID), originalProtection, &originalProtection);
}

void RestoreVMTHook(PVOID** src, PVOID dst, int index)
{
    // I could do tramp hooking instead of VMT hooking, but I came across a few problems while implementing my tramp, and VMT just makes it easier.
    PVOID* VMT = *src;
    PVOID ret = (VMT[index]);
    DWORD originalProtection;
    VirtualProtect(src, sizeof(PVOID), PAGE_EXECUTE_READWRITE, &originalProtection);
    VMT[index] = dst;
    VirtualProtect(src, sizeof(PVOID), originalProtection, &originalProtection);
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
const char* findPattern(const char* moduleName, std::string_view pattern) noexcept
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
        int lastIdx = pattern.length() - 1;
        const auto badCharTable = generateBadCharTable(pattern);

        auto start = static_cast<const char*>(moduleBase);
        const auto end = start + moduleSize - pattern.length();

        while (start <= end) {
            int i = lastIdx;
            while (i >= 0 && (pattern[i] == '?' || start[i] == pattern[i]))
                --i;

            if (i < 0)
            {
                return start;
            }

            start += badCharTable[static_cast<std::uint8_t>(start[lastIdx])];
        }
    }
    MessageBoxA(NULL, "Failed to find a pattern, let the dev know asap!", "ERROR", MB_OK | MB_ICONWARNING);
    return 0;
}
char* GetRealFromRelative(char* address, int offset, int instructionSize, bool isRelative) // Address must be an instruction, not a pointer! And offset = the offset to the bytes you want to retrieve.
{
#ifdef _WIN64
    isRelative = true;
#endif
    char* instruction = address + offset;
    if (!isRelative)
    {
        return *(char**)(instruction);
    }

    int relativeAddress = *(int*)(instruction);
    char* realAddress = address + instructionSize + relativeAddress;
    return realAddress;
}