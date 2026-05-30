#include "../../headers/strategies/NormalAttack.h"
#include "../../headers/player/Player.h"

NormalAttack::NormalAttack()
{
}

NormalAttack::~NormalAttack()
{
}

void NormalAttack::attack(Player& player, int damage)
{
    // Normal attack deals standard damage
    player.dealDamage(damage);
}

