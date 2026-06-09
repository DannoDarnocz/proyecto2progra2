//
// Created by Daniel on 06/06/2026.
//

#ifndef PROYECTO_II_MEDKIT_H
#define PROYECTO_II_MEDKIT_H
#include "Content.h"


class Medkit : public Content
{
public:
    Medkit(bool isVisible = false, bool isConsumable = true):Content(isVisible,isConsumable){}; // visible by default, consumable by default
    std::string toString() override;
    int interact(Player& player) override;
};

#endif //PROYECTO_II_MEDKIT_H