//
// Created by Daniel on 03/06/2026.
//
#include "Content.h"
#ifndef PROYECTO_II_BOMB_H
#define PROYECTO_II_BOMB_H

class Player;

class Bomb : public Content
{
public:
    Bomb(bool isVisible = false):Content(isVisible){}; // not visible by default
    void interact(Player& player) override;
    std::string toString() override;
};

#endif //PROYECTO_II_BOMB_H