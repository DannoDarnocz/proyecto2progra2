#include "../../headers/player/Player.h"
#include "../../headers/powers/Power.h"
#include <algorithm>

Player::Player(int hp, int level)
    : hp(hp), level(level), positionX(0), positionY(0), hasKey(false)
{
}

Player::~Player()
{
    for (auto power : activePowers) {
        delete power;
    }
}

int Player::getHp() const
{
    return hp;
}

void Player::setHp(int hp)
{
    this->hp = hp;
}

void Player::dealDamage(int amount)
{
    hp -= amount;
    if (hp < 0) {
        hp = 0;
    }
}

int Player::getLevel() const
{
    return level;
}

void Player::setLevel(int level)
{
    this->level = level;
}

void Player::levelUp()
{
    level++;
}

const std::vector<Power*>& Player::getActivePowers() const
{
    return activePowers;
}

void Player::addPower(Power* power)
{
    if (power != nullptr) {
        activePowers.push_back(power);
    }
}

void Player::removePower(Power* power)
{
    auto it = std::find(activePowers.begin(), activePowers.end(), power);
    if (it != activePowers.end()) {
        activePowers.erase(it);
    }
}

bool Player::hasKeyItem() const
{
    return hasKey;
}

void Player::setKey(bool hasKey)
{
    this->hasKey = hasKey;
}


