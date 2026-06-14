#include "../../headers/strategies/WeakenerAttack.h"
#include "../../headers/player/Player.h"
#include "../../headers/system/GameConstants.h"

WeakenerAttack::WeakenerAttack()
{
}

WeakenerAttack::~WeakenerAttack()
{
}

void WeakenerAttack::attack(Player& player, Monster& monster)
{
    player.takeDamage(strategyDamage(monster));
    // Locks health regen for next DEFEND action
    player.setDebuff(PlayerDebuff::WEAKNESS);
}

int WeakenerAttack::strategyDamage(Monster& monster)
{
    // Deals 80% of damage
    return monster.getDamage()*GameConstants::WEAKENER_DAMAGE;
}

