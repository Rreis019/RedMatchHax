#pragma once
#include "BaseCheat.h"
#include <vector>

class CheatManager
{
public:
	void init();
	void destroy();
	void onStart();
	void onUpdate();
	void onRender();
private:
	std::vector<BaseCheat*> modules;
};

extern CheatManager cheatManager;
extern bool isCheatRunning;