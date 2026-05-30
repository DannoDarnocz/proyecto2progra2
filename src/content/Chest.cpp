#include "../../headers/content/Chest.h"
#include "../../headers/player/Player.h"
#include <algorithm>

Chest::Chest()
{
}

Chest::~Chest()
{
    for (auto item : items) {
        delete item;
    }
}

void Chest::addItem(Item* item)
{
    if (item != nullptr) {
        items.push_back(item);
    }
}

void Chest::removeItem(Item* item)
{
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
    }
}

const std::vector<Item*>& Chest::getItems() const
{
    return items;
}

void Chest::interact(Player& player)
{
    // Give items to player
    for (auto item : items) {
        player.addToInventory(item);
    }
    items.clear();
}


