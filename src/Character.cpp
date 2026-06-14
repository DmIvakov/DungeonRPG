#include "Character.h"

Character::Character(int x, int y, int maxHp, int damage, int hp)
    :
    Entity(x, y),
    maxHp(maxHp),
    damage(damage),
    hp(hp == -1 ? maxHp : hp)
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