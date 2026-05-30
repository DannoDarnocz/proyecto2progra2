#ifndef ATTACKSTRATEGY_H
#define ATTACKSTRATEGY_H

class Player;

class AttackStrategy
{
public:
    AttackStrategy();
    virtual ~AttackStrategy();

    virtual void attack(Player& player, int damage) = 0;
};

#endif
