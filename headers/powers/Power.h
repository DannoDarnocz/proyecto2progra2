#ifndef POWER_H
#define POWER_H

class Player;

class Power
{
public:
    Power();
    virtual ~Power();

    virtual void applyEffect(Player& player) = 0;
};

#endif
