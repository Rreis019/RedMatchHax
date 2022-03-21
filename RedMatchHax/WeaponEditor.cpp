#include "WeaponEditor.h"
#include "includes.h"
#include "GameSDK.h"

WeaponEditor weaponEditor;

void WeaponEditor::onUpdate()
{
	auto local = getLocalPlayer();
	if (local != NULL)
	{

		if (oShots.size() == 0) {
			for (int i = 0; i < local->items->count; i++) {
				Item* item = local->items->elements[i].item;
				oShots.push_back(item->info->shots);
				oFireRate.push_back(item->info->useDelay);
			}
		}


		for (int i = 0; i < local->items->count;i++) {
			Item* item = local->items->elements[i].item;

			if (unlimitedAmmo){
				local->items->elements[i].item->ammo.setValue(local->items->elements[i].item->info->magazineSize);
			}

			item->info->shots = oShots[i] * shotMultiplier;
			item->info->useDelay = oFireRate[i] * fireRateMultiplier;
			item->info->adsMovementSpreadMultiplier = spreadMultiplier;
			item->info->movementSpreadMultiplier = spreadMultiplier;

		}
	}
	

}

void WeaponEditor::onEnable()
{
	auto local = getLocalPlayer();

	if (local != NULL) {

		for (int i = 0; i < local->items->count; i++) {
			Item* item = local->items->elements[i].item;
			oShots.push_back(item->info->shots);
			oFireRate.push_back(item->info->useDelay);
		}

	}
}

void WeaponEditor::onDisable()
{
	auto local = getLocalPlayer();

	if (local != NULL && oShots.size() > 0) {

		for (int i = 0; i < local->items->count; i++) {
			Item* item = local->items->elements[i].item;
			item->info->shots = oShots[i];
			item->info->useDelay = oFireRate[i];
			item->info->adsMovementSpreadMultiplier = 1;
			item->info->movementSpreadMultiplier = 1;
		}
	}
	oShots.clear();
	oFireRate.clear();
}

void WeaponEditor::onGUI()
{
	if (ImGui::Checkbox("WeaponEditor", &this->enable))
	{
		enable ? this->onEnable() : this->onDisable();
	}


	ImGui::Checkbox("UnlimitedAmmo", &unlimitedAmmo);
	ImGui::SliderInt("ShotMultiplier", &shotMultiplier,0,10);
	ImGui::SliderInt("SpreadMultiplier", &spreadMultiplier,0,10);
	ImGui::SliderFloat("FireRateMultipliter", &fireRateMultiplier, 0, 2.0f);
}
