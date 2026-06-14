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
    // Deals 80% of damage
    player.takeDamage(monster.getDamage()*GameConstants::WEAKENER_DAMAGE);
    // Locks health regen for next DEFEND action
    player.setDebuff(PlayerDebuff::WEAKNESS);
}

