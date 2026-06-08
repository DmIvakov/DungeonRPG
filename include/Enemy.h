#pragma once

#include "Entity.h"

class Enemy : public Entity
{
private:
    int hp;
    int damage;

public:
    Enemy(int x, int y);

    int getHp() const;
    int getDamage() const;
};