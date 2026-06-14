#pragma once

#include "Map.h"
#include "Player.h"
#include "Enemy.h"

class Renderer
{
public:
    static void draw(
        const Map& map,
        const Player& player,
        const std::vector<Enemy>& enemies,
        const int currentFloor
    );
};