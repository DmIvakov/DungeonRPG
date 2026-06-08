#pragma once

#include <vector>

#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelGenerator.h"

class Game
{
private:
    Map map;
    Player player;
    std::vector<Enemy> enemies;
    LevelGenerator generator;

    bool isRunning;
    int currentFloor;

    void input();
    
    std::vector<Enemy>::iterator getEnemyIteratorAt(
        int x, 
        int y
    );

    Enemy* getEnemyAt(
        int x,
        int y
    );
    
public:
    Game();

    void run();
};