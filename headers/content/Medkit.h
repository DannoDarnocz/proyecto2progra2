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
    InteractResult interact(Player& player) override;
    ContentType getContentType() const override { return ContentType::MEDKIT; }
};

#endif //PROYECTO_II_MEDKIT_H