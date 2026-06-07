#ifndef MONSTER_H
#define MONSTER_H

#include <memory>

#include "Content.h"

class AttackStrategy;

class Monster : public Content
{
private:
    int hp;
    int baseDamage;
    int level;
    int maxHp;
    std::string type;
    std::shared_ptr<AttackStrategy> attackStrategy;
    bool isBoss;
    bool modifyStrategy;

public:
    Monster(int hp, int damage, int level, std::shared_ptr<AttackStrategy> strategy, std::string type, bool isBoss = false, bool modifyStrategy = false);
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
    AttackStrategy* getAttackStrategy() const;
    void setAttackStrategy(std::shared_ptr<AttackStrategy> strategy);
    std::string getAttackStrategyName() const;

    void takeDamage(int amount);

    std::string toString() override;

    int interact(Player& player) override;

    bool isBossQ();
};

#endif
