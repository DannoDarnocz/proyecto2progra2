/*#ifndef POWER_H
#define POWER_H
#include "Content.h"

class Player;
class Content;

class PowerUp : public Content
{
public:
    PowerUp(bool isVisible = true, bool isConsumable = true):Content(isVisible,isConsumable){}; // visible by default, consumable by default


    virtual void applyEffect(Player& player) = 0;
    int interact(Player& player) override;
};

#endif
*/