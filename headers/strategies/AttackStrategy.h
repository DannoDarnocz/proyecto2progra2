#ifndef ATTACKSTRATEGY_H
#define ATTACKSTRATEGY_H

#include "../../headers/content/Monster.h"

class AttackStrategy
{
public:
    AttackStrategy();
    virtual ~AttackStrategy();

    virtual void attack(Player& player, Monster& monster) = 0;
    virtual std::string getName() const = 0;
};

#endif
