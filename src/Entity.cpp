#include "Entity.h"

Entity::Entity(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Entity::getX() const
{
    return x;
}

int Entity::getY() const
{
    return y;
}

void Entity::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Entity::move(int dx, int dy)
{
    x += dx;
    y += dy;
}