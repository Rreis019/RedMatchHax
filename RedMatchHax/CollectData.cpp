#include "CollectData.h"
#include <Windows.h>
#include <stdio.h>
#include "SDK.h"
#include "Logger.h"



CollectData collectData = CollectData();

CollectData::CollectData()
{
	this->setToggle(true);
}

void CollectData::onUpdate()
{
	if (gameObjectManager == NULL) {
		PRINT("gameObjectManager == NULL");
		return;
	}

	if (GetTickCount() > tick + 1000) 
	{
		std::vector<uint64_t> tempPlayers = std::vector<uint64_t>();
		GameObject* lastTaggedGameObject = gameObjectManager->LastTaggedObject2->gameObject;
		BaseObject* nextNode = gameObjectManager->TaggedObject2;

		while (true)
		{
			GameObject* gameObject = nextNode->gameObject;

			if (!gameObject || gameObject == NULL) {break;}


			if (strstr(gameObject->name, "PlayerAvatar")) {
				tempPlayers.push_back((uint64_t)gameObject);

				//uint64_t PlayerController = 0x0;
				//PlayerController = getComponentByName(gameObject, (char*)"PlayerController");

			}
			if (gameObject == lastTaggedGameObject) {break;}
			nextNode = nextNode->nextObject;
		}


		tick = GetTickCount();
		players = tempPlayers;
		if (players.size() > 0) {
			vec3 pos = getGameObjectPos((GameObject*)players[0]);
		}
	}

}
