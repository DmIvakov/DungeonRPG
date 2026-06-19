#include "Player.h"

Player::Player(int x, int y)
     :
    Character(x, y, 100, 10),
    level(1),
    exp(0)
{
}

int Player::getLevel() const
{
    return level;
}

int Player::getExp() const
{
    return exp;
}

void Player::addExp(int amount)
{
    exp += amount;

    if (exp >= level * 100)
    {
        exp -= level * 100;
        level++;
        maxHp += 10;
        hp = maxHp;
        damage += 2;
    }
}
