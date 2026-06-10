//
// Created by Daniel on 09/06/2026.
//

#ifndef PROYECTO_II_BASESTATS_H
#define PROYECTO_II_BASESTATS_H
#include <string>

#include "IStats.h"

class BaseStats:public IStats
{
    public:
    int calcMaxHealth(int) const override;
    int calcDamage(int) const override;
    std::string toString() const override;
    std::string toStringOnlyAttack() const override;
    std::string toStringOnlyHealth() const override;
};

#endif //PROYECTO_II_BASESTATS_H