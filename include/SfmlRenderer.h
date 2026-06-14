#pragma once

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Player.h"
#include "Enemy.h"

class SfmlRenderer
{
public:
    static constexpr int TILE_SIZE = 32;

    SfmlRenderer();

    void draw(
        sf::RenderWindow& window,
        const Map& map,
        const Player& player,
        const std::vector<Enemy>& enemies,
        int currentFloor
    );
};