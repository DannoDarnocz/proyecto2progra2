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
    bool strategyDebuffPlayer;

public:
    Monster(int hp, int damage, int level, std::shared_ptr<AttackStrategy> strategy, std::string type, bool isBoss = false, bool modifyStrategy = false, bool strategyDebuffPlayer = false);
    virtual ~Monster();

    int getHp() const;
    void setHp(int hp);
    int getMaxHp() const;

    int getBaseDamage() const;
    void setDamage(int damage);

    int getDamage();

    int getLevel() const;
    void setLevel(int level);

    std::string getType() const;

    void attackPlayer(Player& player, int& amountDebuffs);
    AttackStrategy* getAttackStrategy() const;
    void setAttackStrategy(std::shared_ptr<AttackStrategy> strategy);
    std::string getAttackStrategyName() const;

    void takeDamage(int amount);

    std::string toString() override;

    InteractResult interact(Player& player) override;

    bool isBossQ();
    ContentType getContentType() const override { return ContentType::MONSTER; }
};

#endif
