/*#ifndef POWERDECORATOR_H
#define POWERDECORATOR_H

#include "PowerUp.h"

class PowerUpDecorator : public PowerUp
{
protected:
    PowerUp* wrappedPower;

public:
    PowerUpDecorator(PowerUp* power);
    virtual ~PowerUpDecorator();

    PowerUp* getWrappedPower() const;
    void setWrappedPower(PowerUp* power);

    virtual void applyEffect(Player& player) override;
};

#endif*/
