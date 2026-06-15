#include <cmath>

#include "Entity.h"

Entity::Entity(int x, int y)
    :
    x(x), 
    y(y), 
    visualX(static_cast<float>(x)),
    visualY(static_cast<float>(y)), 
    visualSpeed(15.f),
    facingRight(true), 
    moving(false)
{
}

int Entity::getX() const
{
    return x;
}

int Entity::getY() const
{
    return y;
}

float Entity::getVisualX() const
{
    return visualX;
}

float Entity::getVisualY() const
{
    return visualY;
}


void Entity::updateVisual(float deltaTime) {
    visualX += (x - visualX) * visualSpeed * deltaTime;
    visualY += (y - visualY) * visualSpeed * deltaTime;
}

void Entity::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
    visualX = x;
    visualY = y;
}

void Entity::move(int dx, int dy)
{
    x += dx;
    y += dy;
}


bool Entity::isFacingRight() const
{
    return facingRight;
}

void Entity::faceRight() 
{
    facingRight = true;
}

void Entity::faceLeft() 
{
    facingRight = false;
}

bool Entity::isMoving() const
{
    return std::fabs(x - visualX) > 0.01f || std::fabs(y - visualY) > 0.01f;
}


void Entity::makeMove()
{
    moving = true;
}

void Entity::makeStop()
{
    moving = false;
}