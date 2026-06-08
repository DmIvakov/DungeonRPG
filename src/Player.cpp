#include "Player.h"

Player::Player(int x, int y)
     :
    Entity(x, y),
    hp(100),
    level(1),
    exp(0),
    damage(10)
{
}

int Player::getHp() const
{
    return hp;
}

int Player::getLevel() const
{
    return level;
}

int Player::getExp() const
{
    return exp;
}

int Player::getDamage() const
{
    return damage;
}

void Player::addExp(int amount)
{
    exp += amount;

    if (exp >= level * 100)
    {
        exp -= level * 100;
        level++;
        hp += 10;
        damage += 2;
    }
}