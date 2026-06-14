#pragma once

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Player.h"
#include "Enemy.h"

class SfmlRenderer
{
private:
    static constexpr int TILE_SIZE = 32;

public:
    void draw(
        sf::RenderWindow& window,
        const Map& map,
        const Player& player,
        const std::vector<Enemy>& enemies,
        int currentFloor
    );
};