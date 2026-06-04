#ifndef MONSTER_H
#define MONSTER_H

#include "Content.h"

class AttackStrategy;

class Monster : public Content
{
private:
    int hp;
    int baseDamage;
    int level;
    std::string type;
    AttackStrategy& attackStrategy;
    bool isBoss;

public:
    Monster(int hp, int damage, int level, AttackStrategy& strategy, std::string type, bool isBoss = false);
    virtual ~Monster();

    int getHp() const;
    void setHp(int hp);

    int getBaseDamage() const;
    void setDamage(int damage);


    int getDamage();

    int getLevel() const;
    void setLevel(int level);

    std::string getType() const;

    void attackPlayer(Player& player);
    AttackStrategy& getAttackStrategy() const;
    void setAttackStrategy(AttackStrategy& strategy);

    void takeDamage(int amount);

    std::string toString() const;

    virtual void interact(Player& player) override;
};

#endif
