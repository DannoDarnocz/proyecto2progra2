#ifndef MONSTER_H
#define MONSTER_H

#include "Content.h"

class AttackStrategy;

class Monster : public Content
{
private:
    int hp;
    int damage;
    int level;
    AttackStrategy* attackStrategy;

public:
    Monster(int hp, int damage, int level, AttackStrategy* strategy);
    virtual ~Monster();

    int getHp() const;
    void setHp(int hp);

    int getDamage() const;
    void setDamage(int damage);

    int getLevel() const;
    void setLevel(int level);

    AttackStrategy* getAttackStrategy() const;
    void setAttackStrategy(AttackStrategy* strategy);

    void takeDamage(int amount);

    virtual void interact(Player& player) override;
};

#endif
