#include "../../headers/player/Player.h"
#include "../../headers/content/PowerUp.h"
#include "../../headers/player/ExtraHealthStats.h"
#include "../../headers/player/ExtraDamageStats.h"
#include "../../headers/player/BaseStats.h"
#include <algorithm>

#include "../../headers/system/GameConstants.h"

Player::Player(int hp, int level)
    : hp(hp), level(level)
{
    // Initialize stats with default BaseStats to avoid null pointer dereference
    stats = std::make_unique<BaseStats>();
    debuff = PlayerDebuff::NONE;
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

int Player::calcDamage() const
{
    return stats->calcDamage(level);
}

int Player::calcMaxHealth() const
{
    return stats->calcMaxHealth(level);
}

std::string Player::toString() const
{
    std::string s;

    s = "HP="
    + std::to_string(hp)
    + " | Level=" + std::to_string(level);

    // if no active powerups, just use "no active powerups"
    if (dynamic_cast<BaseStats*>(stats.get())) {
        s+= " | No active powerups";
    }
    else
    {
        s+= " | Active powerups: " + stats->toString();
    }

    s = s + " | Debuff: " + (debuff == PlayerDebuff::NONE ? "None" : (debuff == PlayerDebuff::WEAKNESS ? "Weakness" : "Health Lock"));
    return s;
}


void Player::heal(int amount)
{
    hp += amount;
    if (hp > Player::calcMaxHealth()) {
        hp = Player::calcMaxHealth();
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

void Player::clearPowerUps()
{
    // automatically deletes pointer
    stats = std::make_unique<BaseStats>();
    //restores hp to normal max after battle
    if (hp>calcMaxHealth())
    {
        hp=calcMaxHealth();
    }
}

void Player::addHealthPowerUp() {
    // create new decorator for its own stats
    stats = std::make_unique<ExtraHealthStats>(std::move(stats));

    // automatically adjust +30 hp
    heal(GameConstants::HEALTH_POWERUP_HEAL_AMOUNT);
}

void Player::addDamagePowerUp() {
    // create new decorator for its own stats
    stats = std::make_unique<ExtraDamageStats>(std::move(stats));
}


