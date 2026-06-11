//
// Created by axel on 10/6/2026.
//

#include "../../headers/strategies/LeechAttack.h"
#include "../../headers/player/Player.h"

LeechAttack::LeechAttack()
{
}

LeechAttack::~LeechAttack()
{
}

void LeechAttack::attack(Player& player, Monster& monster)
{
    // Deals 50% of damage
    int damage = monster.getDamage()*0.5;
    player.takeDamage(damage);
    // Steals the damage done to the player and heals
    monster.setHp(monster.getHp()+damage);
}

