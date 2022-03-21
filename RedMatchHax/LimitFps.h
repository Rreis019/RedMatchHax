#pragma once
#include "BaseCheat.h"
#include <cstdint>

class LimitFps : public BaseCheat
{
public:
	void onGUI() override;
private:
	float limitFps = 0;
};

extern LimitFps limitFps;