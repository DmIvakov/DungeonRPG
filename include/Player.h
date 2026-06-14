#pragma once

#include "Character.h"

class Player : public Character
{
private:
    int level;
    int exp;

public:
    Player(int x, int y);

    int getLevel() const;
    int getExp() const;
    void addExp(int amount);
};