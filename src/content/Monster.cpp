#include "../../headers/content/Monster.h"

#include <iostream>

#include "../../headers/player/Player.h"
#include "../../headers/strategies/AttackStrategy.h"
#include "../../headers/strategies/HealthLockAttack.h"
#include "../../headers/strategies/WeakenerAttack.h"

Monster::Monster(int hp, int damage, int level, std::shared_ptr<AttackStrategy> strategy, std::string type, bool isBoss, bool modifyStrategy)
    : Content(true), hp(hp), baseDamage(damage), level(level), attackStrategy(strategy),type(type), isBoss(isBoss), modifyStrategy(modifyStrategy)
{
    this->maxHp = this->hp;
}

Monster::~Monster()
{
}

std::string Monster::toString()
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

AttackStrategy* Monster::getAttackStrategy() const
{
    return attackStrategy.get();
}

void Monster::setAttackStrategy(std::shared_ptr<AttackStrategy> strategy)
{
    attackStrategy = strategy;
}

void Monster::attackPlayer(Player& player)
{
    // delegate attack
    if (attackStrategy) { attackStrategy->attack(player,*this); }
}

void Monster::takeDamage(int amount)
{
    hp -= amount;
    if (hp < 0) { hp = 0; }
    if (!modifyStrategy && hp <= maxHp/2) {
        modifyStrategy = true;
        int roll = rand() % 2;
        if (roll==0) {
            setAttackStrategy(std::make_shared<WeakenerAttack>());
        } else {
            setAttackStrategy(std::make_shared<HealthLockAttack>());
        }
    }
}

int Monster::interact(Player& player)
{
    // Return 2 to indicate this is a monster
    std::cout << "A wild " << type << " appears! Prepare for battle!\n";
    return 2;
}

bool Monster::isBossQ() {
    return isBoss;
}

