#pragma once
#include "BaseCheat.h"
#include <vector>

class CollectData : public BaseCheat
{
public:
	CollectData();
	void onUpdate() override;
	std::vector<uint64_t> players = std::vector<uint64_t>();
private:
	int tick = 0;
};


extern CollectData collectData;