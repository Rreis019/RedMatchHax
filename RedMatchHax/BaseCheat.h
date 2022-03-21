#pragma once
#include <stdio.h>

class BaseCheat
{
public:
	virtual void onStart(){}
	virtual void onUpdate(){}
	virtual void onRender(){}
	virtual void onGUI(){}

	void toggle();
	void setToggle(bool value);
	bool isToggled();
protected:
	bool enable = false;
	virtual void onEnable() {}
	virtual void onDisable() {}
};
