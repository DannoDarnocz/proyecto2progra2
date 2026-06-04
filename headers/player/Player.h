#ifndef PLAYER_H
#define PLAYER_H

#include "../content/PowerUp.h"
#include <vector>

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
    std::vector<PowerUp*> activePowers;
    PlayerDebuff debuff;
public:
    Player(int hp, int level);
    ~Player();

    int getHp() const;
    void setHp(int hp);

    void heal(int amount); // Heal the player by a certain amount
    void takeDamage(int amount); // Deals damage

    int getLevel() const;
    void setLevel(int level);
    void levelUp();

    PlayerDebuff getDebuff() const;
    void setDebuff(PlayerDebuff debuff);

    const std::vector<PowerUp*>& getActivePowers() const;
    void addPower(PowerUp* power);
    void removePower(PowerUp* power);
    int calcMaxHealth() const;
};

#endif
