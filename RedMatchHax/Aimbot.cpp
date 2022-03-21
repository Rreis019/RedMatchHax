#include "Aimbot.h"
#include "includes.h"
#include "GameSDK.h"
#include "SDK.h"
#include "vec3.h"
#include "CollectData.h"
#include "Menu.h"

Aimbot aimbot;
vec2 closestPos = vec2();
vec2 crosshair = vec2();
uint64_t target = NULL;

void Aimbot::onUpdate()
{
	crosshair = vec2(fnGetWindowWitdh() / 2, fnGetWindowHeight() / 2);
	getClosestEnemy();
	aimTarget();
}

void Aimbot::onRender()
{
	if (this->fov == 0 || this->showFov == false) { return; }
	auto pDrawList = ImGui::GetWindowDrawList();
	int windowWitdh = fnGetWindowWitdh();
	int windowHeight = fnGetWindowHeight();
	pDrawList->AddCircle(ImVec2(windowWitdh / 2, windowHeight / 2), this->fov, ImColor(1.0f, 0.0f, 0.0f, 1.0f), 12, 1.0f);
}

void Aimbot::onGUI()
{
	ImGui::Checkbox("Enable##Aimbot", &this->enable);
	ImGui::Checkbox("Show Fov", &this->showFov);
	ImGui::SliderFloat("Fov", &this->fov, 0, 360);
	ImGui::SliderFloat("Aimbot Speed", &this->moveSpeed, 0.1F, 4.0F);
}

void isClosestEnt(uint64_t mainCamera,uint64_t player,float &maxDistance)
{
	vec3 out;
	vec3 pos = getGameObjectPos((GameObject*)player);
	if (w2s(mainCamera, pos, out))
	{
		float distance = crosshair.distance(vec2(out.X, out.Y));
		if (distance < maxDistance) {
			target = player;
			maxDistance = distance;
			closestPos = vec2(out.X, out.Y);
		}
	}
}

void Aimbot::getClosestEnemy()
{
	uint64_t mainCamera = (uint64_t)fnGetMainCamera();
	float maxDistance = this->fov;
	target = NULL;
	
	for (int i = 0; i < collectData.players.size(); i++)
	{
		
		__try
		{
			if ((uint64_t)getLocalPlayer() == collectData.players[i]) { continue; }
			isClosestEnt(mainCamera, collectData.players[i], maxDistance);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) { continue; }
		
	}
	
}

void Aimbot::aimTarget()
{
	if (menu.isOpen || target == NULL) { return; }

	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	Input.mi.dx = (closestPos.X - fnGetWindowWitdh() / 2) * moveSpeed;
	Input.mi.dy = (closestPos.Y - fnGetWindowHeight() / 2) * moveSpeed;
	SendInput(1, &Input, sizeof(INPUT));
}