//
// Created by Daniel on 09/06/2026.
//

#include <iostream>

#include "../../headers/content/PowerUp.h"
#include "../../headers/player/Player.h"
#include "../../headers/system/Logger.h"
#include "../../headers/exceptions/FileException.h"
#include "../../headers/system/GameHelper.h"

InteractResult PowerUp::interact(Player& player)
{
    Logger* logger=Logger::getInstance();
    int randomPowerUp = rand()%3;
    switch (randomPowerUp)
    {
        case 0:
            player.addHealthPowerUp();
            GameHelper::safelog("Player obtained a health power-up. Max HP increased +30%.");
            std::cout << "You got a health power-up! Your max HP has increased.\n";
            break;

        case 1:
            player.addDamagePowerUp();
            GameHelper::safelog("Player obtained a damage power-up. Damage increased +20%.");
            std::cout << "You got a damage power-up! Your damage has increased 20%.\n";
            break;

        default:
            player.addHealthPowerUp();
            player.addDamagePowerUp();
            GameHelper::safelog("Player obtained a health + damage power-up. Max HP (+30%) and damage (20%) increased.");
            std::cout << "You got a health and damage power-up! Max HP (+30%) and damage (20%) increased.\n";
            break;
    }
    return consumable ? InteractResult::CONSUMABLE : InteractResult::NOT_CONSUMABLE;
}

std::string PowerUp::toString()
{
    return "Random power-up";
}