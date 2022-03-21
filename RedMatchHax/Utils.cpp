#include "Utils.h"


MODULEINFO getModuleInfo(char* szModule)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandle(szModule);
	if (hModule == 0)
		return modinfo;
	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}

char* scanBasic(char* pattern, char* mask, char* begin, intptr_t size)
{
    intptr_t patternLen = strlen(mask);

    for (int i = 0; i < size; i++)
    {
        bool found = true;
        for (int j = 0; j < patternLen; j++)
        {
            if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j))
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return (begin + i);
        }
    }
    return nullptr;
}


uintptr_t findPattern(char* pattern, char* mask, MODULEINFO targetModule)
{
    char* match{ nullptr };
    MEMORY_BASIC_INFORMATION mbi{};
    int size = targetModule.SizeOfImage;
    char* begin = (char*)targetModule.lpBaseOfDll;

    for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
    {
        if (!VirtualQuery(curr, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

        match = scanBasic(pattern, mask, curr, mbi.RegionSize);

        if (match != nullptr)
        {
            break;
        }
    }
    return (uintptr_t)match;
}


void patch(uint64_t addr, unsigned char* bytes,int size)
{
    DWORD oldProtect;
    VirtualProtect((void*)addr, sizeof(bytes), PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy((void*)addr, bytes, size);
    VirtualProtect((void*)addr, sizeof(bytes), oldProtect, &oldProtect);
}

uint64_t absoluteAddress(uint64_t address, uint64_t offset)
{
    uint64_t v = *(int*)(address + offset);
    return v + (address + offset) + 4;
}




struct EnumData {
    DWORD dwProcessId;
    HWND hWnd;
};

// Application-defined callback for EnumWindows
BOOL CALLBACK EnumProc(HWND hWnd, LPARAM lParam) {
    // Retrieve storage location for communication data
    EnumData& ed = *(EnumData*)lParam;
    DWORD dwProcessId = 0x0;
    // Query process ID for hWnd
    GetWindowThreadProcessId(hWnd, &dwProcessId);
    // Apply filter - if you want to implement additional restrictions,
    // this is the place to do so.
    if (ed.dwProcessId == dwProcessId) {
        // Found a window matching the process ID
        ed.hWnd = hWnd;
        // Report success
        SetLastError(ERROR_SUCCESS);
        // Stop enumeration
        return FALSE;
    }
    // Continue enumeration
    return TRUE;
}

HWND findWindowFromProcessId(DWORD dwProcessId) {
    EnumData ed = { dwProcessId };
    if (!EnumWindows(EnumProc, (LPARAM)&ed) &&
        (GetLastError() == ERROR_SUCCESS)) {
        return ed.hWnd;
    }
    return NULL;
}