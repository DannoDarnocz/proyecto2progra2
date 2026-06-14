#ifndef STUNATTACK_H
#define STUNATTACK_H

#include "AttackStrategy.h"

class WeakenerAttack : public AttackStrategy
{
public:
    WeakenerAttack();
    virtual ~WeakenerAttack();

    virtual void attack(Player& player, Monster& monster) override;
    std::string getName() const override { return "Weakener Attack"; }
};

#endif
