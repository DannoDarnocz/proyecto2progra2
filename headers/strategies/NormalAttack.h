#ifndef NORMALATTACK_H
#define NORMALATTACK_H

#include "AttackStrategy.h"

class NormalAttack : public AttackStrategy
{
public:
    NormalAttack();
    virtual ~NormalAttack();

    virtual void attack(Player& player, Monster& monster) override;
    std::string getName() const override { return "Normal Attack"; }
};

#endif
