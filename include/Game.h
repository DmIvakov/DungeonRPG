#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelGenerator.h"
#include "SfmlRenderer.h"

class Game
{
private:
    sf::RenderWindow window;

    Map map;
    Player player;

    std::vector<Enemy> enemies;

    LevelGenerator generator;
    SfmlRenderer renderer;

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