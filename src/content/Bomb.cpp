//
// Created by Daniel on 03/06/2026.
//

#include "../../headers/content/Bomb.h"
#include "../../headers/system/Logger.h"
#include "../../headers/exceptions/FileException.h"

#include <iostream>

#include "../../headers/player/Player.h"

int Bomb::interact(Player& player)
{
    // Bomb explodes and deals 30% damage (never kills the player)
    player.takeDamage(player.getHp()*0.3);
    if (player.getHp() < 1) { player.setHp(1); }  // HP always stays in 1 to prevent death of the player
    std::cout << "Boom! The bomb explodes and deals 30% damage to you!" << std::endl;

    Logger* logger = Logger::getInstance(); //get logger instance
    try
    {
        logger->log("Dug into a bomb.");
    }
    catch (FileException& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 1;  // Return 1 if consumable, 0 if not
}

std::string Bomb::toString()
{
    return "Bomb";
}
