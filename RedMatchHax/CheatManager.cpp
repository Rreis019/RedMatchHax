#include "CheatManager.h"

//MODULES
#include "CollectData.h"
#include "Esp.h"
#include "WeaponEditor.h"
#include "GodMode.h"
#include "Aimbot.h"
#include "Logger.h"

CheatManager cheatManager;
bool isCheatRunning = true;

void CheatManager::init()
{
	modules.push_back(&weaponEditor);
	modules.push_back(&collectData);
	modules.push_back(&godMode);
	modules.push_back(&esp);
	modules.push_back(&aimbot);
	cheatManager.onStart();
}
void CheatManager::destroy()
{
	for (auto m : modules) {
		m->setToggle(false);
	}

	modules.clear();
}

void CheatManager::onStart()
{
	for (int i = 0; i < modules.size(); i++) {
		modules[i]->onStart();
	}
}
void CheatManager::onUpdate()
{
	for (int i = 0; i < modules.size(); i++) {
		if (!modules[i]->isToggled()) { continue; }
		modules[i]->onUpdate();
	}
}

void CheatManager::onRender()
{
	for (int i = 0; i < modules.size(); i++) {
		
		if (!modules[i]->isToggled()) { continue; }
		modules[i]->onRender();
	}
}