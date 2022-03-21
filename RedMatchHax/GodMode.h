#pragma once
#include "BaseCheat.h"
#include <cstdint>

class GodMode : public BaseCheat
{
public:
	void onStart()  override;
	void onEnable() override;
	void onDisable() override;
	void onGUI() override;
private:
	uint64_t fnPlayerControllerDie = 0x0;
	unsigned char originalBytes[2] = { 0x0,0x0 };
	unsigned char modBytes[2] = { 0xC3,0x90 };
};

extern GodMode godMode;