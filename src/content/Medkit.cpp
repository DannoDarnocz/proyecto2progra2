//
// Created by Daniel on 06/06/2026.
//

#include "../../headers/content/Medkit.h"

#include <iostream>

#include "../../headers/player/Player.h"

int Medkit::interact(Player& player) // TODO: implement logger through parameter to specify what was obtained
{
    player.setHp(player.calcMaxHealth()); // Heal the player fully
    std::cout << "Excellent! You found a Medkit and healed to 100% HP!" << std::endl;
    return 1;  // Medkit is always consumable
}

std::string Medkit::toString()
{
    return "Medkit";
}
