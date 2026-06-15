#include <stdexcept>
#include "SfmlRenderer.h"

SfmlRenderer::SfmlRenderer() {
    if (!atlasTexture.loadFromFile("assets/tileset/0x72_DungeonTilesetII_v1.7/0x72_DungeonTilesetII_v1.7.png")) {
        throw std::runtime_error("Failed to load tileset atlas!");
    }

    tileRects[TileType::Floor] = sf::IntRect({16, 64}, {16, 16});
    tileRects[TileType::Wall] = sf::IntRect({16, 16}, {16, 16});
    tileRects[TileType::Exit] = sf::IntRect({48, 96}, {16, 16});
}

void SfmlRenderer::draw(
    sf::RenderWindow& window,
    const Map& map,
    const Player& player,
    const std::vector<Enemy>& enemies,
    int currentFloor
)
{
    sf::RenderStates states;
    // states.transform.translate({ 0.f, 48.f });


    // for tiles
    sf::Sprite tileSprite(atlasTexture);
    float scale = static_cast<float>(TILE_SIZE) / 16.f;
    tileSprite.setScale({scale, scale});


    for(int y = 0; y < map.getHeight(); y++)
    {
        for(int x = 0; x < map.getWidth(); x++)
        {
            tileSprite.setPosition(
                sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE)
            );

            TileType currentType = map.tiles[y][x];

            tileSprite.setTextureRect(tileRects[currentType]);

            // make walls a bit darker
            if (currentType == TileType::Wall) {
                tileSprite.setColor(sf::Color(155, 155, 155)); 
            } else {
                tileSprite.setColor(sf::Color::White); 
            }

            window.draw(tileSprite, states); 
        }
    }


    // for player and enemies 
    sf::RectangleShape tile(
        sf::Vector2f(
            TILE_SIZE,
            TILE_SIZE
        )
    );

    // Player
    tile.setFillColor(
        sf::Color::Green
    );

    tile.setPosition(
        sf::Vector2f(player.getX() * TILE_SIZE, player.getY() * TILE_SIZE)
    );

    window.draw(tile, states); 

    // Enemies
    tile.setFillColor(
        sf::Color::Red
    );

    for(const Enemy& enemy : enemies)
    {
        tile.setPosition(
            sf::Vector2f(enemy.getX() * TILE_SIZE, enemy.getY() * TILE_SIZE)
        );

        window.draw(tile, states); 
    }
}
