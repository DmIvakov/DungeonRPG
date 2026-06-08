#include "Renderer.h"

#include <iostream>

using namespace std;

void Renderer::draw(
    const Map& map,
    const Player& player,
    const std::vector<Enemy>& enemies,
    int currentFloor
)
{
    // Clear the console and move the cursor to the top-left corner
    std::cout << "\x1B[2J\x1B[H";

    for(int y = 0; y < map.getHeight(); y++)
    {
        for(int x = 0; x < map.getWidth(); x++)
        {
            // Check if the player is at this position
            if(
                x == player.getX()
                &&
                y == player.getY()
            )
            {
                cout << 'P';
                continue;
            }


            // Check if there's an enemy at this position
            bool enemyFound = false;

            for(const Enemy& enemy : enemies)
            {
                if(
                    enemy.getX() == x
                    &&
                    enemy.getY() == y
                )
                {
                    std::cout << 'M';
                    enemyFound = true;
                    break;
                }
            }

            if(enemyFound)
            {
                continue;
            }

            // Render the tile
            switch(map.tiles[y][x])
            {
                case TileType::Wall:
                    cout << '#';
                    break;

                case TileType::Floor:
                    cout << '.';
                    break;

                case TileType::Exit:
                    cout << 'E';
                    break;
            }
        }

        cout << '\n';
    }

    // Display player stats and current floor
    cout << '\n';

    cout << "Floor: " << currentFloor << '\n';
    cout << "Level: " << player.getLevel() << '\n';
    cout << "Exp: " << player.getExp() << '\n';
    cout << "HP: " << player.getHp() << '\n';
    cout << "Damage: " << player.getDamage() << '\n';
    cout << "Enemies: " << enemies.size() << '\n';
}