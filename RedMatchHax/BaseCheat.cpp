#include "BaseCheat.h"

void BaseCheat::toggle()
{
	enable = !enable;
	enable == true ? onEnable() : onDisable();
}

void BaseCheat::setToggle(bool value) {
	enable = value;
	enable == true ? onEnable() : onDisable();
}

bool BaseCheat::isToggled() {
	return enable;
}