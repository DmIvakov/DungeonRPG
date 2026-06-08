#include "Map.h"

Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;

    tiles.resize(height);

    for(int y = 0; y < height; y++)
    {
        tiles[y].resize(width, TileType::Wall);
    }

    // for(int y = 1; y < height - 1; y++)
    // {
    //     for(int x = 1; x < width - 1; x++)
    //     {
    //         tiles[y][x] = TileType::Floor;
    //     }
    // }
}

int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}

bool Map::isWalkable(
    int x,
    int y
) const
{
    if(x < 0 || x >= width)
        return false;

    if(y < 0 || y >= height)
        return false;

    return tiles[y][x] != TileType::Wall;
}

bool Map::isExit(
    int x,
    int y
) const
{
    if(x < 0 || x >= width)
        return false;

    if(y < 0 || y >= height)
        return false;

    return tiles[y][x] == TileType::Exit;
}

void Map::setTile(
    int x,
    int y,
    TileType type
)
{
    if(x < 0 || x >= width)
        return;

    if(y < 0 || y >= height)
        return;

    tiles[y][x] = type;
}

void Map::fill(TileType type)
{
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            tiles[y][x] = type;
        }
    }
}