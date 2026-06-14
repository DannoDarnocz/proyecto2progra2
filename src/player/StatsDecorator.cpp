//
// Created by Daniel on 09/06/2026.
//
#include "../../headers/player/StatsDecorator.h"
int StatsDecorator::calcMaxHealth(int level) const  {
    return wrappedStats->calcMaxHealth(level);
}

int StatsDecorator::calcDamage(int level) const {
    return wrappedStats->calcDamage(level);
}

IStats& StatsDecorator::getWrappedStats()
{
    return *wrappedStats;
};

std::string StatsDecorator::toString() const
{
    return wrappedStats->toString();
}
std::string StatsDecorator::toStringOnlyAttack() const
{
    return wrappedStats->toStringOnlyAttack();
}
std::string StatsDecorator::toStringOnlyHealth() const
{
    return wrappedStats->toStringOnlyHealth();
}