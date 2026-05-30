#include "../../headers/strategies/StunAttack.h"
#include "../../headers/player/Player.h"

StunAttack::StunAttack()
{
}

StunAttack::~StunAttack()
{
}

void StunAttack::attack(Player& player, int damage)
{
    // Stun attack deals reduced damage but can stun the player
    int stunDamage = damage * 0.75;
    player.dealDamage(stunDamage);
    // Additional stun effect would be implemented here
}

