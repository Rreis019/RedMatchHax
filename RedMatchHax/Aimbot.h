#pragma once
#include "BaseCheat.h"
#include <stdint.h>
#include "vec2.h"

class Aimbot : public BaseCheat
{
public:
	void onUpdate() override;
	void onRender() override;
	void onGUI() override;
public:
	void getClosestEnemy();
	void aimTarget();
	float fov = 0;
	float moveSpeed = 1;
	bool showFov = false;
};

extern Aimbot aimbot;