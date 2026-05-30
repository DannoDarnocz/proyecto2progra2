#ifndef STUNATTACK_H
#define STUNATTACK_H

#include "AttackStrategy.h"

class StunAttack : public AttackStrategy
{
public:
    StunAttack();
    virtual ~StunAttack();

    virtual void attack(Player& player, int damage) override;
};

#endif
