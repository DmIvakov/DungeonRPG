#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"

class HudRenderer {
private:
    sf::Font font;
    sf::Text statsText;

public:
    HudRenderer();
    void draw(sf::RenderWindow& window, const Player& player, const std::vector<Enemy>& enemies, const int currentFloor);
};
