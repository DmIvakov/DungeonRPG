#pragma once

#include <vector>
#include <utility>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelGenerator.h"
#include "SfmlRenderer.h"
#include "HudRenderer.h"

class Game
{
private:
    sf::RenderWindow window;
    int ticks;

    Map map;
    Player player;

    std::vector<Enemy> enemies;

    LevelGenerator generator;
    SfmlRenderer renderer;
    HudRenderer hudRenderer;

    int currentFloor;

    void input();

    std::pair<int, int> parseKeyPressedToCoord(
        const sf::Event::KeyPressed& keyEvent
    ) const;

    void processInteraction(
        int dx, 
        int dy
    );
    
    std::vector<Enemy>::iterator getEnemyIteratorAt(
        int x,
        int y
    );

public:
    static constexpr int MAP_WIDTH = 40;
    static constexpr int MAP_HEIGHT = 20;
    static constexpr int HUD_HEIGHT = 48;

    Game();

    void run();
};