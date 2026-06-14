#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>

// Простая структура для врага
struct Enemy {
    sf::Vector2f position;
    bool isAlive = true;
};

int main() {
    sf::RenderWindow window(sf::VideoMode({480, 480}), "Dungeon RPG - Chapter 5 (MVP Battle)");
    window.setFramerateLimit(60);

    sf::Music music;
    if (music.openFromFile("assets/audio/DungeonRPG.ogg")) {
        music.setLooping(true);
        music.play();
    }

    sf::Texture atlasTexture;
    if (!atlasTexture.loadFromFile("assets/tileset/0x72_DungeonTilesetII_v1.7/0x72_DungeonTilesetII_v1.7.png")) {
        std::cout << "Failed to load tileset atlas!" << std::endl;
    }

    // Карта подземелья (10x10)
    const int MAP_WIDTH = 10;
    const int MAP_HEIGHT = 10;
    int dungeonMap[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    sf::Sprite tileSprite(atlasTexture);
    float tileSize = 48.f;
    sf::IntRect wallRect({16, 16}, {16, 16});
    sf::IntRect floorRect({16, 64}, {16, 16});

    // === ИНИЦИАЛИЗАЦИЯ ИГРОКА ===
    sf::Sprite playerSprite(atlasTexture);
    int startX = 128, startY = 196, width = 16, height = 28;
    playerSprite.setTextureRect(sf::IntRect({startX, startY}, {width, height}));
    playerSprite.setScale({3.f, 3.f});
    playerSprite.setOrigin({width / 2.f, static_cast<float>(height - 2)});

    sf::Vector2f playerPos = { 1.5f * tileSize, 1.5f * tileSize };
    playerSprite.setPosition(playerPos);

    float playerSpeed = 3.5f;
    sf::Clock animationClock;
    int currentFrame = 0;
    float frameDuration = 0.12f;

    // === ИНИЦИАЛИЗАЦИЯ ВРАГА (СКЕЛЕТ) ===
    Enemy skeleton;
    // Спавним скелета в правой комнате (координаты ячейки x=7, y=2)
    skeleton.position = { 7.5f * tileSize, 2.0f * tileSize };
    
    sf::Sprite enemySprite(atlasTexture);
    // Координаты скелета в атласе 0x72
    int enemyWidth = 16, enemyHeight = 28;
    enemySprite.setTextureRect(sf::IntRect({368, 80}, {16, 28}));

    enemySprite.setScale({3.f, 3.f});
    enemySprite.setOrigin({enemyWidth / 2.f, static_cast<float>(enemyHeight - 2)});
    enemySprite.setPosition(skeleton.position);
    // ====================================

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Движение и коллизии игрока
        bool isMoving = false;
        sf::Vector2f movement{0.f, 0.f};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { movement.y = -playerSpeed; isMoving = true; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { movement.y = playerSpeed; isMoving = true; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { movement.x = -playerSpeed; isMoving = true; playerSprite.setScale({-3.f, 3.f}); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { movement.x = playerSpeed; isMoving = true; playerSprite.setScale({3.f, 3.f}); }

        sf::Vector2f nextPos = playerPos + movement;

        // Твои выверенные настройки хитбокса
        float hWidth  = 12.f; 
        float hTop    = 6.f;  
        float hBottom = 6.f;  

        sf::Vector2f topLeft     = { nextPos.x - hWidth, nextPos.y - hTop };
        sf::Vector2f topRight    = { nextPos.x + hWidth, nextPos.y - hTop };
        sf::Vector2f bottomLeft  = { nextPos.x - hWidth, nextPos.y + hBottom };
        sf::Vector2f bottomRight = { nextPos.x + hWidth, nextPos.y + hBottom };

        auto isFloor = [&](sf::Vector2f point) {
            int tx = static_cast<int>(point.x / tileSize);
            int ty = static_cast<int>(point.y / tileSize);
            if (tx < 0 || tx >= MAP_WIDTH || ty < 0 || ty >= MAP_HEIGHT) return false;
            return dungeonMap[ty][tx] == 0;
        };

        if (isFloor(topLeft) && isFloor(topRight) && isFloor(bottomLeft) && isFloor(bottomRight)) {
            playerPos = nextPos;
            playerSprite.setPosition(playerPos);
        }

        // === ЛОГИКА БОЯ (ВАНШОТ) ===
        if (skeleton.isAlive) {
            // Считаем расстояние между центрами игрока и скелета по теореме Пифагора
            sf::Vector2f diff = playerPos - skeleton.position;
            float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
            
            // Если подошли вплотную (меньше 30 пикселей) — ВАНШОТ!
            if (distance < 30.f) {
                skeleton.isAlive = false;
                std::cout << "Skeleton was vanished in one shot!" << std::endl;
            }
        }
        // ===========================

        // Анимация игрока
        if (isMoving) {
            if (animationClock.getElapsedTime().asSeconds() >= frameDuration) {
                currentFrame = (currentFrame + 1) % 5;
                int frameX = startX + ((currentFrame + 4) * 16);
                playerSprite.setTextureRect(sf::IntRect({frameX, startY}, {width, height}));
                animationClock.restart();
            }
        } else {
            if (animationClock.getElapsedTime().asSeconds() >= frameDuration) {
                currentFrame = (currentFrame + 1) % 4;
                int frameX = startX + (currentFrame * 16);
                playerSprite.setTextureRect(sf::IntRect({frameX, startY}, {width, height}));
                animationClock.restart();
            }
        }

        window.clear(sf::Color(30, 30, 30));

        // Отрисовка карты
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                if (dungeonMap[y][x] == 1) tileSprite.setTextureRect(wallRect);
                else tileSprite.setTextureRect(floorRect);
                tileSprite.setPosition({x * tileSize, y * tileSize});
                tileSprite.setScale({3.f, 3.f});
                window.draw(tileSprite);
            }
        }

        // === УМНАЯ ОТРИСОВКА С СОРТИРОВКОЙ ГЛУБИНЫ (Y-Sorting) ===
        if (skeleton.isAlive) {
            // Если враг стоит ВЫШЕ игрока — сначала рисуем врага, потом игрока
            if (skeleton.position.y <= playerPos.y) {
                window.draw(enemySprite);
                window.draw(playerSprite);
            } 
            // Если враг стоит НИЖЕ игрока — сначала игрока, потом врага поверх
            else {
                window.draw(playerSprite);
                window.draw(enemySprite);
            }
        } else {
            // Если враг мертв — просто рисуем игрока
            window.draw(playerSprite);
        }

        window.display();
    }

    return 0;
}
