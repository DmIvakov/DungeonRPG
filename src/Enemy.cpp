#include "Enemy.h"

Enemy::Enemy(int x, int y)
    :
    Entity(x, y),
    hp(20),
    damage(5)
{
}

int Enemy::getHp() const
{
    return hp;
} 

int Enemy::getDamage() const
{
    return damage;
}