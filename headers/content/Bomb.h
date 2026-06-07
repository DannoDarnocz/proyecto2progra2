//
// Created by Daniel on 03/06/2026.
//

#ifndef PROYECTO_II_BOMB_H
#define PROYECTO_II_BOMB_H
#include "Content.h"
class Player;

class Bomb : public Content
{
public:
    Bomb(bool isVisible = false, bool isConsumable = true):Content(isVisible, isConsumable){}; // not visible by default
    int interact(Player& player) override;
    std::string toString() override;
};

#endif //PROYECTO_II_BOMB_H