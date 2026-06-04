#include "../../headers/strategies/NormalAttack.h"
#include "../../headers/player/Player.h"

NormalAttack::NormalAttack()
{
}

NormalAttack::~NormalAttack()
{
}

void NormalAttack::attack(Player& player, Monster& monster)
{
    // Normal attack deals standard damage
    player.takeDamage(monster.getDamage());
}

