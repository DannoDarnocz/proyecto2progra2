//
// Created by Daniel on 06/06/2026.
//

#include "../../headers/content/Medkit.h"

#include <iostream>

#include "../../headers/player/Player.h"
#include "../../headers/system/Logger.h"
#include "../../headers/exceptions/FileException.h"

int Medkit::interact(Player& player)
{
    player.setHp(player.calcMaxHealth()); // Heal the player fully
    std::cout << "Excellent! You found a Medkit and healed to 100% HP!" << std::endl;
    Logger* logger = Logger::getInstance(); //get logger instance
    try
    {
        logger->log("Restored full health with a medkit");
    }
    catch (FileException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 1;  // Medkit is always consumable
}

std::string Medkit::toString()
{
    return "Medkit";
}
