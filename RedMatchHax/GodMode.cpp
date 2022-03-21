#include "GodMode.h"
#include "includes.h"
#include "SDK.h"


GodMode godMode;

#define patternPlayerControllerDie (char*)"\x40\x53\x57\x48\x83\xEC\x68\x80\x3D\x00\x00\x00\x00\x00\x48\x8B\xD9"
#define maskPlayerControllerDie (char*)"xxxxxxxxx?????xxx"

void GodMode::onStart()
{
	fnPlayerControllerDie = findPattern(patternPlayerControllerDie,maskPlayerControllerDie, modGameAssemblyDll);
	printf("fnPlayerControllerDie : %p", fnPlayerControllerDie);
}

void GodMode::onEnable()
{
	memcpy(originalBytes, (void*)fnPlayerControllerDie, 2);
	patch(fnPlayerControllerDie, modBytes,sizeof(modBytes));
}

void GodMode::onDisable()
{
	if (originalBytes[0] != 0) {
		patch(fnPlayerControllerDie, originalBytes, sizeof(originalBytes));
	}
}

void GodMode::onGUI()
{
	if (ImGui::Checkbox("GodMode", &this->enable))
	{
		enable ? this->onEnable() : this->onDisable();
	}
}