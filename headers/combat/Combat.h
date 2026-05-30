#ifndef COMBAT_H
#define COMBAT_H

#include "../player/Player.h"
#include <chrono>

class Monster;

class Combat
{
private:
    Player& player;
    Monster& monster;

public:
    Combat(Player& player, Monster& monster);
    ~Combat();

    Player& getPlayer() const;
    Monster& getMonster() const;

    void executeTurn();
    void run();

private:
    std::chrono::milliseconds measureResponseTime();
    void applyDamageBasedOnSpeed(int baseDamage, int responseTime);
};

#endif

