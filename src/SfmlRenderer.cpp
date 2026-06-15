#include <stdexcept>
#include "SfmlRenderer.h"

SfmlRenderer::SfmlRenderer()
    :
    animationSpeed(12)
{
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
    int ticks,
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
    tileSprite.setOrigin({ 0.f, 0.f });
    float scale = static_cast<float>(TILE_SIZE) / ORIGINAL_TILE_SIZE;
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
    tileSprite.setOrigin({ ORIGINAL_TILE_SIZE / 2, 0.f });

    // Enemies
    for(const Enemy& enemy : enemies)
    {
        int enemyBaseFrame = enemy.isMoving() ? 4 : 0;
        int enemyCurrentSubFrame = (ticks / animationSpeed) % 4;
        int enemyActualFrameIndex = enemyBaseFrame + enemyCurrentSubFrame;

        sf::IntRect animatedEnemyRect = enemyRect;
        animatedEnemyRect.position.x += enemyActualFrameIndex * ORIGINAL_TILE_SIZE;
        tileSprite.setTextureRect(animatedEnemyRect);

        if (enemy.isFacingRight()) {
            tileSprite.setScale({ scale, scale });
        } else {
            tileSprite.setScale({ -scale, scale });
        }

        float eX = enemy.getX() * TILE_SIZE + (TILE_SIZE / 2.f);
        float eY = enemy.getY() * TILE_SIZE - 2.f; 
        
        tileSprite.setPosition({eX, eY});
        window.draw(tileSprite, states); 
    }
    

    // Player
    int playerBaseFrame = player.isMoving() ? 4 : 0;
    int playerCurrentSubFrame = (ticks / animationSpeed) % 4; 

    int playerActualFrameIndex = playerBaseFrame + playerCurrentSubFrame;

    sf::IntRect animatedPlayerRect = playerRect;
    animatedPlayerRect.position.x += playerActualFrameIndex * ORIGINAL_TILE_SIZE;

    tileSprite.setTextureRect(animatedPlayerRect);
    
    if (player.isFacingRight()) {
        tileSprite.setScale({ scale, scale });
    } else {
        tileSprite.setScale({ -scale, scale });
    }

    float pX = player.getX() * TILE_SIZE + (TILE_SIZE / 2.f);
    float pY = player.getY() * TILE_SIZE - (28 - 16) * scale - 2.f; 


    tileSprite.setPosition({pX, pY});
    window.draw(tileSprite, states);

    // TODO: Refactor Enemy and Player animation : DRY
}
