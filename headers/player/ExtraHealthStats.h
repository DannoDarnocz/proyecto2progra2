//
// Created by Daniel on 09/06/2026.
//

#ifndef PROYECTO_II_EXTRAHEALTHSTATS_H
#define PROYECTO_II_EXTRAHEALTHSTATS_H
#include "StatsDecorator.h"


class ExtraHealthStats : public StatsDecorator {
public:
    ExtraHealthStats(std::unique_ptr<IStats> stats)
        : StatsDecorator(std::move(stats)) {}

    int calcMaxHealth(int level) const override;
    std::string toString() const override;
    std::string toStringOnlyHealth() const override;
    std::string toStringOnlyAttack() const override;
};

#endif //PROYECTO_II_EXTRAHEALTHSTATS_H