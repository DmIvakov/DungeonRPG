#pragma once

#include <vector>
#include <utility>

class Room
{
public:
    int x;
    int y;

    int width;
    int height;

    Room(
        int x,
        int y,
        int width,
        int height
    );

    int centerX() const;
    int centerY() const;

    bool intersects(const Room& other) const;

    std::vector<std::pair<int,int>> getCells() const;
};