#pragma once

#include <vector>

#include "Tile.h"

class Map
{
private:
    int width;
    int height;

public:
    std::vector<std::vector<TileType>> tiles;

    Map(int width, int height);

    int getWidth() const;
    int getHeight() const;

    bool isWalkable(int x, int y) const;
    bool isExit(int x, int y) const;
    
    void setTile(
        int x,
        int y,
        TileType type
    );

    void fill(TileType type);
};