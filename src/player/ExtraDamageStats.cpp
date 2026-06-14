//
// Created by Daniel on 09/06/2026.
//

#include "../../headers/player/ExtraDamageStats.h"

#include "../../headers/system/GameConstants.h"

int ExtraDamageStats::calcDamage(int level) const
{
    return wrappedStats->calcDamage(level) * GameConstants::EXTRA_DAMAGE_MULTIPLIER; // 20% more damage
}

std::string ExtraDamageStats::toString() const
{
    return "+20% more damage, " + wrappedStats->toString();
}

std::string ExtraDamageStats::toStringOnlyHealth() const // only return stats that increase health
{
    return "" + wrappedStats->toStringOnlyHealth();
}

std::string ExtraDamageStats::toStringOnlyAttack() const  // only return stats that increase attack (this doesn't because it's only extra health)
{
    return "+20% more damage, " + wrappedStats->toStringOnlyAttack();
}