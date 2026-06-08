#pragma once

class Entity
{
protected:
    int x;
    int y;

public:
    Entity(int x, int y);

    int getX() const;
    int getY() const;

    void setPosition(int x, int y);
    void move(int dx, int dy);
};