#pragma once
#include "BaseCheat.h"
#include <stdint.h>

class Esp : public BaseCheat
{
public:
	void onRender() override;
	void onGUI() override;
public:
	bool drawBox = false;
	bool drawLines = false;
	bool showDistance = false;
};

extern Esp esp;