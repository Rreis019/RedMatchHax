#pragma once

enum ECategory {
	EAimbot = 0,
	EEsp = 1,
	EMisc = 2
};

class Menu
{
public:
	bool isOpen = false;
	void onStart();
	void onRender();
private:
	void drawAimTab();
	void drawEspTab();
	void drawMiscTab();
	ECategory currentTab = ECategory::EAimbot;
};
extern Menu menu;