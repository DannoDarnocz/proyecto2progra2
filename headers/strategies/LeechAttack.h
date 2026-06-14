//
// Created by axel on 10/6/2026.
//

#ifndef PROYECTO_II_LEECHATTACK_H
#define PROYECTO_II_LEECHATTACK_H

#include "AttackStrategy.h"

class LeechAttack : public AttackStrategy
{
public:
    LeechAttack();
    virtual ~LeechAttack();

    virtual void attack(Player& player, Monster& monster) override;
    std::string getName() const override { return "Leech Attack"; }
};

#endif //PROYECTO_II_LEECHATTACK_H