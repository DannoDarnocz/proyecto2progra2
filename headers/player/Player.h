#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>

#include "../content/PowerUp.h"
#include <vector>

#include "IStats.h"

enum class PlayerDebuff
{
    NONE,
    WEAKNESS,
    HEALTH_LOCK
};

class Player
{
private:
    int hp;
    int level;
    std::unique_ptr<IStats> stats;
    PlayerDebuff debuff;
public:
    Player(int hp, int level);

    int getHp() const;
    void setHp(int hp); // sets hp without checking, unsafe

    void heal(int amount); // Heal the player by a certain amount
    void takeDamage(int amount); // Deals damage

    int calcDamage() const;
    int getLevel() const;
    void setLevel(int level);
    void levelUp();

    PlayerDebuff getDebuff() const;
    void setDebuff(PlayerDebuff debuff);

    void clearPowerUps();
    void addHealthPowerUp();
    void addDamagePowerUp();

    /*const std::vector<PowerUp*>& getActivePowers() const;
    void addPower(PowerUp* power);
    void removePower(PowerUp* power);*/
    int calcMaxHealth() const;

    std::string toString() const;
};

#endif
