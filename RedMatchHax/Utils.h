#pragma once
#include <cstdint>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>

HWND findWindowFromProcessId(DWORD dwProcessId);
MODULEINFO getModuleInfo(char* szModule);
uintptr_t findPattern(char* pattern, char* mask, MODULEINFO targetModule);
uint64_t absoluteAddress(uint64_t address, uint64_t offset);
void patch(uint64_t addr, unsigned char* bytes, int size);

