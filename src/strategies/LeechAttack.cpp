//
// Created by axel on 10/6/2026.
//

#include "../../headers/strategies/LeechAttack.h"
#include "../../headers/player/Player.h"
#include "../../headers/system/GameConstants.h"

LeechAttack::LeechAttack()
{
}

LeechAttack::~LeechAttack()
{
}

void LeechAttack::attack(Player& player, Monster& monster)
{
    int damage = strategyDamage(monster);
    player.takeDamage(damage);
    // Steals the damage done to the player and heals
    int healedHp = monster.getHp() + damage;
    if (healedHp > monster.getMaxHp()) {
        healedHp = monster.getMaxHp();
    }
    monster.setHp(healedHp);
}


int LeechAttack::strategyDamage(Monster& monster) {
    // Deals 50% of damage
 return monster.getDamage()*GameConstants::LEECH_DAMAGE;
}
