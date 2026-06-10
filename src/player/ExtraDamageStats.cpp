//
// Created by Daniel on 09/06/2026.
//

#include "../../headers/player/ExtraDamageStats.h"

int ExtraDamageStats::calcDamage(int level) const
{
    return wrappedStats->calcDamage(level) * 1.2; // 20% more damage
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