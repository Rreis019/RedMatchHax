#include "CheatManager.h"
#include "GameSDK.h"
#include "SDK.h"
PlayerController_c* playerController_c;
/*
PlayerControlDie
40 53 57 48 83 EC 68 80 3D ? ? ? ? ? 48 8B D9
\x40\x53\x57\x48\x83\xEC\x68\x80\x3D\x00\x00\x00\x00\x00\x48\x8B\xD9 xxxxxxxxx?????xxx

Patch: C3 90



Localplayer
48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 44 88 71 20
\x48\x8B\x05\x00\x00\x00\x00\x48\x8B\x88\x00\x00\x00\x00\x44\x88\x71\x20 xxx????xxx????xxxx


TimeScale
48 63 C1 48 8D 0D ? ? ? ? 48 89 14
\x48\x63\xC1\x48\x8D\x0D\x00\x00\x00\x00\x48\x89\x14 xxxxxx????xxx

lea     rcx, qword_1817F8BE0 ; this
.text:000000018059BC17 E9 E4 FB FF FF                          jmp     ?InitializeClasses@ManagerContext@@QEAAXXZ


48 8B 15 ? ? ? ? 48 83 C2 20 48 3B
\x48\x8B\x15\x00\x00\x00\x00\x48\x83\xC2\x20\x48\x3B xxx????xxxxxx

//48 8B 15 ? ? ? ? 48 83 C2 20 48 3B  mov     rdx, cs:?s_Instance@GameObjectManager@@2PEAV1@EA
*/

int ObscuredInt::getValue()
{
	return this->value - this->offset;
}

void ObscuredInt::setValue(int value)
{
	this->value = this->offset + value;
}

#define PATTERN_PLAYERCONTROLLER (char*)"\x48\x8B\x05\x00\x00\x00\x00\x48\x8B\x88\x00\x00\x00\x00\x44\x88\x71\x20"
#define MASK_PLAYERCONTROLLER (char*)"xxx????xxx????xxxx"

void initGameSDK()
{
	playerController_c = (PlayerController_c*)absoluteAddress(findPattern(PATTERN_PLAYERCONTROLLER, MASK_PLAYERCONTROLLER, modGameAssemblyDll),3);
	printf("playerController_c : %p\n", playerController_c);
	cheatManager.onStart();
}

PlayerController_fields* getLocalPlayer()
{
	return playerController_c->klass->static_fields->LocalPlayer;
}