//
// Created by Daniel on 03/06/2026.
//

#include "../../headers/content/Bomb.h"
#include "../../headers/system/Logger.h"
#include "../../headers/exceptions/FileException.h"

#include <iostream>

#include "../../headers/player/Player.h"
#include "../../headers/system/GameConstants.h"
#include "../../headers/system/GameHelper.h"

InteractResult Bomb::interact(Player& player)
{
    // Bomb explodes and deals 30% damage (never kills the player)
    player.takeDamage(player.getHp()*GameConstants::BOMB_DAMAGE);
    if (player.getHp() < 1) { player.setHp(1); }  // HP always stays in 1 to prevent death of the player
    std::cout << "Boom! The bomb explodes and deals 30% damage to you!" << std::endl;

    GameHelper::safelog("Dug into a bomb.");

    return InteractResult::CONSUMABLE;
}

std::string Bomb::toString()
{
    return "Bomb";
}
