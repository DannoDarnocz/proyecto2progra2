//
// Created by Daniel on 09/06/2026.
//

#ifndef PROYECTO_II_EXTRADAMAGESTATS_H
#define PROYECTO_II_EXTRADAMAGESTATS_H

#include "StatsDecorator.h"


class ExtraDamageStats : public StatsDecorator {
public:
    ExtraDamageStats(std::unique_ptr<IStats> stats)
        : StatsDecorator(std::move(stats)) {}

    int calcDamage(int level) const override;
    std::string toString() const override;
    std::string toStringOnlyHealth() const override;
    std::string toStringOnlyAttack() const override;
};

#endif //PROYECTO_II_EXTRADAMAGESTATS_H