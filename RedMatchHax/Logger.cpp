#include "Logger.h"
#include <stdio.h>
#include <Windows.h>



void initLogger()
{
	AllocConsole();
	freopen("CON", "w", stdout);
	AttachConsole(GetCurrentProcessId());
	SetConsoleTitleA("[DEBUG] RED MATCH CHEAT CONSOLE");
}

void closeLogger()
{
	FreeConsole();
}