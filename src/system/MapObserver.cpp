#include "../../headers/system/MapObserver.h"
#include "../../headers/world/Map.h"
#include "../../headers/player/Player.h"

MapObserver::MapObserver(Map* map)
    : map(map)
{
}

MapObserver::~MapObserver()
{
}

void MapObserver::onLevelUp(Player& player)
{
    // Unlock boss cell when player levels up
    if (map != nullptr) {
        auto currentDimension = map->getCurrentDimension();
        if (currentDimension != nullptr) {
            auto boss = currentDimension->getBoss();
            if (boss != nullptr) {
                boss->setVisible(true);
            }
        }
    }
}

