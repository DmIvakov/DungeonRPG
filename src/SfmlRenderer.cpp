#include "SfmlRenderer.h"

void SfmlRenderer::draw(
    sf::RenderWindow& window,
    const Map& map,
    const Player& player,
    const std::vector<Enemy>& enemies,
    int currentFloor
)
{
    window.clear();

    sf::RectangleShape tile(
        sf::Vector2f(
            TILE_SIZE,
            TILE_SIZE
        )
    );

    for(int y = 0; y < map.getHeight(); y++)
    {
        for(int x = 0; x < map.getWidth(); x++)
        {
            // ИСПРАВЛЕНО: Явное создание sf::Vector2f
            tile.setPosition(
                sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE)
            );

            switch(map.tiles[y][x])
            {
                case TileType::Wall:
                    tile.setFillColor(
                        sf::Color::White
                    );
                    break;

                case TileType::Floor:
                    tile.setFillColor(
                        sf::Color(50,50,50)
                    );
                    break;

                case TileType::Exit:
                    tile.setFillColor(
                        sf::Color::Yellow
                    );
                    break;
            }

            window.draw(tile);
        }
    }

    // Player
    tile.setFillColor(
        sf::Color::Green
    );

    // ИСПРАВЛЕНО: Явное создание sf::Vector2f
    tile.setPosition(
        sf::Vector2f(player.getX() * TILE_SIZE, player.getY() * TILE_SIZE)
    );

    window.draw(tile);

    // Enemies
    tile.setFillColor(
        sf::Color::Red
    );

    for(const Enemy& enemy : enemies)
    {
        // ИСПРАВЛЕНО: Явное создание sf::Vector2f
        tile.setPosition(
            sf::Vector2f(enemy.getX() * TILE_SIZE, enemy.getY() * TILE_SIZE)
        );

        window.draw(tile);
    }

    window.display();
}
