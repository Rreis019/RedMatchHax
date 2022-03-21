#include "Menu.h"
#include "includes.h"

//CHEATS
#include "Esp.h"
#include "WeaponEditor.h"
#include "GodMode.h"
#include "Aimbot.h"
#include "LimitFps.h"
#include "CheatManager.h"
#include "Logger.h"

ImFont* h1Text;
ImFont* h2Text;

#define TAB_WITDH 134
#define TAB_HEIGHT 35
#define TAB_SIZE ImVec2(TAB_WITDH,TAB_HEIGHT)

#define MENU_WITDH 435
#define MENU_HEIGHT 380

#define CONTENT_WITDH 402
#define CONTENT_HEIGHT 302

#define PADDING 16

#define DARK_BLUE ImVec4(0.160f, 0.176f, 0.243f,1.0f)
#define DARK_BLUE2 ImVec4(0.133f, 0.145f, 0.2f,1.0f)
#define LIGHT_BLUE ImVec4(0.180, 0.203, 0.286,1.0f)
#define LIGHT_BLUE2 ImVec4(0.360f, 0.419f, 0.752f,1.0f)
#define WHITE ImVec4(1.0f, 1.0f, 1.0f,1.0f)

Menu menu;

void Menu::onStart()
{
	ImGuiIO& io = ImGui::GetIO();
	h1Text = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 18);
	h2Text = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 14);
}

void Menu::onRender()
{
	if (!this->isOpen) { return; }

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 0.0f;
	style.WindowRounding = 1.0f;
	style.WindowPadding = ImVec2(PADDING, PADDING);
	style.ItemSpacing = ImVec2(0, 0);

	style.Colors[ImGuiCol_Button] = DARK_BLUE;
	style.Colors[ImGuiCol_ButtonHovered] = DARK_BLUE;
	style.Colors[ImGuiCol_ButtonActive] = DARK_BLUE;
	style.Colors[ImGuiCol_WindowBg] = DARK_BLUE;
	style.Colors[ImGuiCol_ChildBg] = LIGHT_BLUE;
	style.Colors[ImGuiCol_SliderGrab] = LIGHT_BLUE2;
	style.ChildBorderSize = 0.0f;
	
	style.FramePadding = ImVec2(5, 5);
	style.Colors[ImGuiCol_FrameBg] = DARK_BLUE;
	style.Colors[ImGuiCol_FrameBgActive] = DARK_BLUE;
	style.Colors[ImGuiCol_FrameBgHovered] = DARK_BLUE2;
	style.Colors[ImGuiCol_CheckMark] = WHITE;

	ImGui::SetNextWindowSize(ImVec2(MENU_WITDH, MENU_HEIGHT));

	ImGui::Begin("Teste", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize );



	ImGui::PushFont(h1Text);
	if (ImGui::Button("Aimbot##TabAim",TAB_SIZE)) { 
		this->currentTab = EAimbot;
	}
	ImGui::SameLine();

	if(ImGui::Button("Esp##TabEsp", TAB_SIZE)) {
		this->currentTab = EEsp;
	}
	ImGui::SameLine();
	
	if (ImGui::Button("Misc##TabMisc", TAB_SIZE)) {
		this->currentTab = EMisc;
	}

	ImGui::PopFont();
	ImGui::PushFont(h2Text);
	ImGui::Dummy(ImVec2(0, 9));

	style.Colors[ImGuiCol_Button] = LIGHT_BLUE2;
	style.Colors[ImGuiCol_ButtonHovered] = DARK_BLUE;
	style.Colors[ImGuiCol_ButtonActive] = LIGHT_BLUE2;
	style.ItemSpacing = ImVec2(10, 10);

	ImGui::BeginChild("Content", ImVec2(CONTENT_WITDH,CONTENT_HEIGHT),false);
	
	ImGui::SetCursorPos(ImVec2(15, 15));
		ImGui::BeginChild("MarginContent",ImVec2(CONTENT_WITDH-15,CONTENT_HEIGHT-15));

		if(currentTab == ECategory::EAimbot)
			drawAimTab();
		else if (currentTab == ECategory::EEsp)
			drawEspTab();
		else if (currentTab == ECategory::EMisc)
			drawMiscTab();

		ImGui::SetCursorPos(ImVec2(0,CONTENT_HEIGHT - 55));
		if (ImGui::Button("Eject", ImVec2(75, 25))) {
			isCheatRunning = false;
		}

		ImGui::EndChild();
	ImGui::EndChild();
	ImGui::PopFont();

	auto pDrawList = ImGui::GetWindowDrawList();
	ImVec2 pos = ImGui::GetWindowPos();
	pos.x += PADDING + currentTab * TAB_WITDH;
	pos.y += TAB_HEIGHT + 16;
	pDrawList->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.x+ TAB_WITDH, pos.y+3), (ImColor)LIGHT_BLUE2, 0.0f);

	ImGui::End();
}


void Menu::drawAimTab()
{
	aimbot.onGUI();
}
void Menu::drawEspTab()
{
	esp.onGUI();
}
void Menu::drawMiscTab()
{
	godMode.onGUI();
	weaponEditor.onGUI();
	limitFps.onGUI();
}