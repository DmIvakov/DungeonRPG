#pragma once

#include <vector>

#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Room.h"

class LevelGenerator
{
private:
    void createTunnel(
        Map& map,
        int start,
        int end,
        int constantCoord,
        bool isHorizontal
    );

    bool isOccupied(
        int x,
        int y,
        const std::vector<Enemy>& enemies
    );
    
    void spawnEnemies(
        const std::vector<Room>& rooms,
        std::vector<Enemy>& enemies,
        int count,
        int exitX,
        int exitY
    );

public:
    void generate(
        Map& map,
        Player& player,
        std::vector<Enemy>& enemies
    );
};