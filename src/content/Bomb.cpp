//
// Created by Daniel on 03/06/2026.
//

#include "../../headers/content/Bomb.h"

#include <iostream>

#include "../../headers/player/Player.h"

void Bomb::interact(Player& player)
{
    // Bomb explodes and deals 30% damage (never kills the player)
    player.takeDamage(player.getHp()*0.3);
    if (player.getHp() < 1) { player.setHp(1); }  // HP always stays in 1 to prevent death of the player
    std::cout << "Boom! The bomb explodes and deals 30% damage to you!" << std::endl;
}

std::string Bomb::toString()
{
    return "Bomb";
}
