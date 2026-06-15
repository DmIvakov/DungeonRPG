#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Player.h"
#include "Enemy.h"

class SfmlRenderer
{
private:
    sf::Texture atlasTexture;
    
    std::unordered_map<TileType, sf::IntRect> tileRects;
    sf::IntRect playerRect;
    sf::IntRect enemyRect;

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