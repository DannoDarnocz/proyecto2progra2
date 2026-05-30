#include "../../headers/content/Monster.h"
#include "../../headers/player/Player.h"
#include "../../headers/strategies/AttackStrategy.h"
#include "../../headers/combat/Combat.h"

Monster::Monster(int hp, int damage, int level, AttackStrategy* strategy)
    : hp(hp), damage(damage), level(level), attackStrategy(strategy)
{
}

Monster::~Monster()
{
    delete attackStrategy;
}

int Monster::getHp() const
{
    return hp;
}

void Monster::setHp(int hp)
{
    this->hp = hp;
}

int Monster::getDamage() const
{
    return damage;
}

void Monster::setDamage(int damage)
{
    this->damage = damage;
}

int Monster::getLevel() const
{
    return level;
}

void Monster::setLevel(int level)
{
    this->level = level;
}

AttackStrategy* Monster::getAttackStrategy() const
{
    return attackStrategy;
}

void Monster::setAttackStrategy(AttackStrategy* strategy)
{
    if (attackStrategy != nullptr) {
        delete attackStrategy;
    }
    attackStrategy = strategy;
}

void Monster::takeDamage(int amount)
{
    hp -= amount;
    if (hp < 0) {
        hp = 0;
    }
}

void Monster::interact(Player& player)
{
    // Start combat with the player
    Combat combat(player, *this);
    combat.run();
}

