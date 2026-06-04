#include "../../headers/strategies/HealthLockAttack.h"
#include "../../headers/player/Player.h"

HealthLockAttack::HealthLockAttack()
{
}

HealthLockAttack::~HealthLockAttack()
{
}

void HealthLockAttack::attack(Player& player, Monster& monster)
{
    // Deals 80% of damage
    player.takeDamage(monster.getDamage()*0.8);
    // Locks health regen for next DEFEND action
    player.setDebuff(PlayerDebuff::HEALTH_LOCK);
}

