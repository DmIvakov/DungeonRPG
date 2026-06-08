#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
    int hp;
    int level;
    int exp;
    int damage;

public:
    Player(int x, int y);

    int getHp() const;
    int getLevel() const;
    int getExp() const;
    int getDamage() const;
    void addExp(int amount);
};