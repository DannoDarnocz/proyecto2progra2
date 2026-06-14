//
// Created by Daniel on 09/06/2026.
//

#ifndef PROYECTO_II_STATSDECORATOR_H
#define PROYECTO_II_STATSDECORATOR_H

#include <memory>

#include "IStats.h"
#include <vector>
class StatsDecorator:public IStats
{
protected:
    std::unique_ptr<IStats> wrappedStats;
public:
    StatsDecorator(std::unique_ptr<IStats> stats): wrappedStats(std::move(stats)) {}

    std::string toString() const override;
    std::string toStringOnlyAttack() const override;
    std::string toStringOnlyHealth() const override;

    int calcMaxHealth(int) const override;

    int calcDamage(int) const override;
    IStats& getWrappedStats();
};

#endif //PROYECTO_II_STATSDECORATOR_H