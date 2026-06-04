#ifndef POISONATTACK_H
#define POISONATTACK_H

#include "AttackStrategy.h"

class HealthLockAttack : public AttackStrategy
{
public:
    HealthLockAttack();
    virtual ~HealthLockAttack();

    virtual void attack(Player& player, Monster& monster) override;
};

#endif
