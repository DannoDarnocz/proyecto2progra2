#ifndef POWERDECORATOR_H
#define POWERDECORATOR_H

#include "Power.h"

class PowerDecorator : public Power
{
protected:
    Power* wrappedPower;

public:
    PowerDecorator(Power* power);
    virtual ~PowerDecorator();

    Power* getWrappedPower() const;
    void setWrappedPower(Power* power);

    virtual void applyEffect(Player& player) override;
};

#endif
