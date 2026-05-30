#ifndef PLAYER_H
#define PLAYER_H

#include "../powers/Power.h"
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
    std::vector<Power*> activePowers;
    bool hasKey;
    PlayerDebuff debuff;
public:
    Player(int hp, int level);
    ~Player();

    int getHp() const;
    void setHp(int hp);
    void dealDamage(int amount);

    int getLevel() const;
    void setLevel(int level);
    void levelUp();

    const std::vector<Power*>& getActivePowers() const;
    void addPower(Power* power);
    void removePower(Power* power);

    bool hasKeyItem() const;
    void setKey(bool hasKey);
};

#endif
