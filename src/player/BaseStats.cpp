//
// Created by Daniel on 09/06/2026.
//

#include "../../headers/player/BaseStats.h"

#include "../../headers/system/GameConstants.h"

int BaseStats::calcMaxHealth(int lvl) const
{
    return GameConstants::BASE_PLAYER_HP+(lvl-1)*GameConstants::PLAYER_HP_PER_LEVEL;
}
int BaseStats::calcDamage(int lvl) const
{
    return GameConstants::BASE_PLAYER_DAMAGE+(lvl-1)*GameConstants::PLAYER_DAMAGE_PER_LEVEL;
}

std::string BaseStats::toString() const
{
    return "";
}

std::string BaseStats::toStringOnlyHealth() const
{
    return "";
}

std::string BaseStats::toStringOnlyAttack() const
{
    return "";
}