#include "../../headers/powers/PowerDecorator.h"
#include "../../headers/player/Player.h"

PowerDecorator::PowerDecorator(Power* power)
    : wrappedPower(power)
{
}

PowerDecorator::~PowerDecorator()
{
    delete wrappedPower;
}

Power* PowerDecorator::getWrappedPower() const
{
    return wrappedPower;
}

void PowerDecorator::setWrappedPower(Power* power)
{
    if (wrappedPower != nullptr) {
        delete wrappedPower;
    }
    wrappedPower = power;
}

void PowerDecorator::applyEffect(Player& player)
{
    if (wrappedPower != nullptr) {
        wrappedPower->applyEffect(player);
    }
}

