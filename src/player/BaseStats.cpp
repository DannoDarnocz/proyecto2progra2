//
// Created by Daniel on 09/06/2026.
//

#include "../../headers/player/BaseStats.h"
int BaseStats::calcMaxHealth(int lvl) const
{
    return 100+(lvl-1)*15;
}
int BaseStats::calcDamage(int lvl) const
{
    return 15+(lvl-1)*10;
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