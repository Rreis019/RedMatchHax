#include "LimitFps.h"
#include "includes.h"
#include "SDK.h"

LimitFps limitFps;

void LimitFps::onGUI()
{
	ImGui::SliderFloat("", &limitFps, -1, 300); ImGui::SameLine();
	if (ImGui::Button("Limit Fps"))
	{
		if (limitFps == 0) { limitFps = -1; }
		fnSetTargetFrameRate(limitFps);
	}
}