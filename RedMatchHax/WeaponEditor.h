#pragma once
#include "BaseCheat.h"
#include <vector>
#include "vec3.h"

class WeaponEditor : public BaseCheat
{
public:
	void onUpdate() override;
	void onGUI() override;
	void onEnable() override;
	void onDisable() override;
private:
	bool unlimitedAmmo = false;
	int shotMultiplier = 1;
	int spreadMultiplier = 1;
	float fireRateMultiplier = 1.0f;

	std::vector<int> oShots;
	std::vector<float> oFireRate;
};

extern WeaponEditor weaponEditor;