//
// Created by Daniel on 06/06/2026.
//

#include "../../headers/content/Medkit.h"

#include <iostream>

#include "../../headers/player/Player.h"
#include "../../headers/system/Logger.h"
#include "../../headers/exceptions/FileException.h"
#include "../../headers/system/GameHelper.h"

InteractResult Medkit::interact(Player& player)
{
    player.setHp(player.calcMaxHealth()); // Heal the player fully
    std::cout << "Excellent! You found a Medkit and healed to 100% HP!" << std::endl;
    GameHelper::safelog("Restored full health with a medkit");
    return InteractResult::CONSUMABLE;  // Medkit is always consumable
}

std::string Medkit::toString()
{
    return "Medkit";
}
