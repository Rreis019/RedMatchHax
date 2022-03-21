#include "Esp.h"
#include "CollectData.h"
#include "vec3.h"
#include "SDK.h"
#include "includes.h"
#include "GameSDK.h"
#include "Logger.h"
Esp esp;

void drawPlayer(uint64_t mainCamera,uint64_t player)
{
	vec3 footPos = getGameObjectPos((GameObject*)player);
	vec3 headPos;
	headPos.X = footPos.X;
	headPos.Y = footPos.Y;
	headPos.Z = footPos.Z;

	footPos.Y -= 1.0f;
	headPos.Y += 1.0f;

	vec3 w2sFootPos;
	vec3 w2sHeadPos;
	if (w2s((uint64_t)mainCamera, footPos, w2sFootPos)) {

		w2s((uint64_t)mainCamera, headPos, w2sHeadPos);

		int boxHeight = abs(w2sFootPos.Y - w2sHeadPos.Y);
		int boxWitdh = boxHeight / 1.5f;

		auto pDrawList = ImGui::GetWindowDrawList();

		if (esp.drawBox)
		{
			pDrawList->AddRect(ImVec2(w2sHeadPos.X - boxWitdh/2, w2sHeadPos.Y), ImVec2(w2sHeadPos.X-(boxWitdh / 2) + boxWitdh, w2sHeadPos.Y + boxHeight), ImColor(255, 0, 0));

		}

		if (esp.drawLines) {
			int windowWitdh = fnGetWindowWitdh();
			int windowHeight = fnGetWindowHeight();
			pDrawList->AddLine(ImVec2(windowWitdh/2, windowHeight), ImVec2(w2sFootPos.X, w2sFootPos.Y), ImColor(255, 0, 0),1.0F);

		}
	}
}

void Esp::onRender()
{

	void* mainCamera = fnGetMainCamera();
	for (int i = 0; i < collectData.players.size(); i++)
	{
		if (collectData.players[i] == (uint64_t)getLocalPlayer()) { continue; }
		__try
		{
			drawPlayer((uint64_t)mainCamera, collectData.players[i]);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) { continue; }
	}
}

void Esp::onGUI()
{
	ImGui::Checkbox("Enable##Esp", &this->enable);
	ImGui::Checkbox("Draw Box", &this->drawBox);
	ImGui::Checkbox("Draw Lines", &this->drawLines);
}