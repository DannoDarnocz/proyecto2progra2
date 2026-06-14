#include "../../headers/strategies/HealthLockAttack.h"
#include "../../headers/player/Player.h"
#include "../../headers/system/GameConstants.h"

HealthLockAttack::HealthLockAttack()
{
}

HealthLockAttack::~HealthLockAttack()
{
}

void HealthLockAttack::attack(Player& player, Monster& monster)
{
    // Deals 80% of damage
    player.takeDamage(strategyDamage(monster));
    // Locks health regen for next DEFEND action
    player.setDebuff(PlayerDebuff::HEALTH_LOCK);
}

int HealthLockAttack::strategyDamage(Monster& monster)
{
    return monster.getDamage()*GameConstants::HEALTH_LOCK_DAMAGE;
}

