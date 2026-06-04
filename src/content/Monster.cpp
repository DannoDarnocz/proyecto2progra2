#include "../../headers/content/Monster.h"
#include "../../headers/player/Player.h"
#include "../../headers/strategies/AttackStrategy.h"

Monster::Monster(int hp, int damage, int level, AttackStrategy& strategy, std::string type, bool isBoss)
    : hp(hp), baseDamage(damage), level(level), attackStrategy(strategy),type(type), isBoss(isBoss)
{
}

Monster::~Monster()
{
}

std::string Monster::toString() const
{
    return type + " (HP: " + std::to_string(hp) + ", Damage: " + std::to_string(baseDamage) + ", Level: " + std::to_string(level) + ")";
}

int Monster::getHp() const
{
    return hp;
}

std::string Monster::getType() const
{
    return type;
}

void Monster::setHp(int hp)
{
    this->hp = hp;
}

int Monster::getBaseDamage() const
{
    return baseDamage;
}

void Monster::setDamage(int damage)
{
    this->baseDamage = damage;
}

int Monster::getDamage()
{
    return baseDamage+(level-1)*10;
}

int Monster::getLevel() const
{
    return level;
}

void Monster::setLevel(int level)
{
    this->level = level;
}

AttackStrategy& Monster::getAttackStrategy() const
{
    return attackStrategy;
}

void Monster::setAttackStrategy(AttackStrategy& strategy)
{
    attackStrategy = strategy;
}

void Monster::attackPlayer(Player& player)
{
    // delegate attack
    attackStrategy.attack(player,getDamage());
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
}

