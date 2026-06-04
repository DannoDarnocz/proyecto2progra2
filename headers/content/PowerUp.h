#ifndef POWER_H
#define POWER_H

class Player;
class Content;

class PowerUp
{
public:
    PowerUp();
    virtual ~PowerUp();

    virtual void applyEffect(Player& player) = 0;
};

#endif
