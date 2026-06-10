//
// Created by Daniel on 09/06/2026.
//

#ifndef PROYECTO_II_ISTATS_H
#define PROYECTO_II_ISTATS_H

class IStats
{
public:
    virtual ~IStats() = default;
    virtual int calcMaxHealth(int) const = 0;
    virtual int calcDamage(int) const= 0;
    virtual std::string toString() const= 0;
    virtual std::string toStringOnlyAttack() const= 0;
    virtual std::string toStringOnlyHealth() const= 0;
};

#endif //PROYECTO_II_ISTATS_H