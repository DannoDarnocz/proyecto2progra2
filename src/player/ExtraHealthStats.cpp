//
// Created by Daniel on 09/06/2026.
//

#include "../../headers/player/ExtraHealthStats.h"

#include "../../headers/system/GameConstants.h"

int ExtraHealthStats::calcMaxHealth(int level) const{
    return wrappedStats->calcMaxHealth(level) * GameConstants::EXTRA_HEALTH_MULTIPLIER; // 30% more max health
}

std::string ExtraHealthStats::toString() const
{
    return "+30% max health, " + wrappedStats->toString();
}

std::string ExtraHealthStats::toStringOnlyHealth() const // only return stats that increase health
{
    return "+30% max health, " + wrappedStats->toStringOnlyHealth();
}

std::string ExtraHealthStats::toStringOnlyAttack() const  // only return stats that increase attack (this doesn't because it's only extra health)
{
    return "" + wrappedStats->toStringOnlyAttack();
}