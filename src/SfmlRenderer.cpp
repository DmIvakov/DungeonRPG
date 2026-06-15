#include <stdexcept>
#include "SfmlRenderer.h"

SfmlRenderer::SfmlRenderer() {
    if (!atlasTexture.loadFromFile("assets/tileset/0x72_DungeonTilesetII_v1.7/0x72_DungeonTilesetII_v1.7.png")) {
        throw std::runtime_error("Failed to load tileset atlas!");
    }

    tileRects[TileType::Floor] = sf::IntRect({16, 64}, {16, 16});
    tileRects[TileType::Wall] = sf::IntRect({16, 16}, {16, 16});
    tileRects[TileType::Exit] = sf::IntRect({48, 96}, {16, 16});

    playerRect = sf::IntRect({128, 100}, {16, 28});
    enemyRect  = sf::IntRect({368, 88}, {16, 16}); 
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

    // Tiles
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

    tileSprite.setColor(sf::Color::White);

     

    // Enemies
    tileSprite.setTextureRect(enemyRect);

    for(const Enemy& enemy : enemies)
    {
        float eX = enemy.getX() * TILE_SIZE;
        float eY = enemy.getY() * TILE_SIZE - 2.f; // not sure why this number, but it does work
                                                    // I guess it's due to scale(x), so we need shift 2 times more than it was in tiles
        tileSprite.setPosition({eX, eY});
        window.draw(tileSprite, states); 
    }

    // Player
    tileSprite.setTextureRect(playerRect);
    
    float pX = player.getX() * TILE_SIZE;
    float pY = player.getY() * TILE_SIZE - 26.f; // same here
                                                 // tile is 16x16, scale x2, but Player's is 16x28
                                                 // 28 - 16 = 12; => 12 x 2 = 24; => 24 + 2 = 28;  // our number 2 from the code above (ambiguously :D)  
                                                 // ^-tile's height                       ^- the 2 here is just a magic number that works    
    tileSprite.setPosition({pX, pY});
    window.draw(tileSprite, states);
}
