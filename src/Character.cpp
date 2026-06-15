#include "Character.h"

Character::Character(int x, int y, int maxHp, int damage, int hp)
    :
    Entity(x, y),
    maxHp(maxHp),
    damage(damage),
    hp(hp == -1 ? maxHp : hp),
    facingRight(true),
    moving(false)
{
}

int Character::getHp() const
{
    return hp;
}

int Character::getMaxHp() const
{
    return maxHp;
}

int Character::getDamage() const
{
    return damage;
}


bool Character::isFacingRight() const
{
    return facingRight;
}

void Character::faceRight() 
{
    facingRight = true;
}

void Character::faceLeft() 
{
    facingRight = false;
}


bool Character::isMoving() const
{
    return moving;
}

void Character::makeMove()
{
    moving = true;
}

void Character::makeStop()
{
    moving = false;
}