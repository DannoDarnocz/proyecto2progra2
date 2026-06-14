#include "../../headers/strategies/NormalAttack.h"
#include "../../headers/player/Player.h"

NormalAttack::NormalAttack()
{
}

NormalAttack::~NormalAttack()
{
}

int NormalAttack::strategyDamage(Monster& monster)
{
    // Normal attack deals standard damage
    return monster.getDamage();
}

void NormalAttack::attack(Player& player, Monster& monster)
{
    player.takeDamage(strategyDamage(monster));
}

