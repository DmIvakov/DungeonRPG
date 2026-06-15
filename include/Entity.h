#pragma once

class Entity
{
protected:
    int x;
    int y;

    float visualX;
    float visualY;

    float visualSpeed;

    bool facingRight;
    bool moving;

public:
    Entity(int x, int y);

    int getX() const;
    int getY() const;

    float getVisualX() const;
    float getVisualY() const;

    void updateVisual(float deltaTime);

    void setPosition(int x, int y);
    void move(int dx, int dy);

    bool isFacingRight() const;
    void faceRight();
    void faceLeft();

    bool isMoving() const;
    void makeMove();
    void makeStop();
};