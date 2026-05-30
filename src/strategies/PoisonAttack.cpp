#include "../../headers/strategies/PoisonAttack.h"
#include "../../headers/player/Player.h"

PoisonAttack::PoisonAttack()
{
}

PoisonAttack::~PoisonAttack()
{
}

void PoisonAttack::attack(Player& player, int damage)
{
    // Poison attack deals extra damage over time
    // Deal 150% of normal damage
    int poisonDamage = damage * 1.5;
    player.dealDamage(poisonDamage);
}

