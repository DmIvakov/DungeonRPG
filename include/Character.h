#pragma once

#include "Entity.h"

class Character : public Entity {
protected:
    int hp;
    int maxHp;
    int damage;

    bool facingRight;
    bool moving;
public:
    Character(int x, int y, int maxHp, int damage, int hp = -1);

    int getHp() const;
    int getMaxHp() const;
    int getDamage() const;

    bool isFacingRight() const;
    void faceRight();
    void faceLeft();

    bool isMoving() const;
    void makeMove();
    void makeStop();
};