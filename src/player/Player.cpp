#include "../../headers/player/Player.h"
#include "../../headers/content/PowerUp.h"
#include <algorithm>

Player::Player(int hp, int level)
    : hp(hp), level(level)
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

void Player::takeDamage(int amount)
{
    hp -= amount;
    if (hp < 0) {
        hp = 0;
    }
}

int Player::calcMaxHealth() const
{
    return 100+(level-1)*15;
}


void Player::heal(int amount)
{
    hp += amount;
    if (hp < Player::calcMaxHealth()) {
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



PlayerDebuff Player::getDebuff() const
{
    return debuff;
}

void Player::setDebuff(PlayerDebuff debuff)
{
    this->debuff = debuff;
}

const std::vector<PowerUp*>& Player::getActivePowers() const
{
    return activePowers;
}

void Player::addPower(PowerUp* power)
{
    if (power != nullptr) {
        activePowers.push_back(power);
    }
}

void Player::removePower(PowerUp* power)
{
    auto it = std::find(activePowers.begin(), activePowers.end(), power);
    if (it != activePowers.end()) {
        activePowers.erase(it);
    }
}


