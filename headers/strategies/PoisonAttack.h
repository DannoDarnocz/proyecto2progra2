#ifndef POISONATTACK_H
#define POISONATTACK_H

#include "AttackStrategy.h"

class PoisonAttack : public AttackStrategy
{
public:
    PoisonAttack();
    virtual ~PoisonAttack();

    virtual void attack(Player& player, int damage) override;
};

#endif
