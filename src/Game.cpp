#include <iostream>
#include <unordered_map>

#include "Game.h"
#include "SfmlRenderer.h"

Game::Game()
    :
    window(
        sf::VideoMode(
            sf::Vector2u(
                40 * 32,
                20 * 32 + 48
            )
        ),
        "Dungeon RPG"
    ),
    map(40, 20),
    player(0, 0),
    currentFloor(1),
    hudRenderer()
{
    generator.generate(
        map,
        player,
        enemies
    );

    window.setFramerateLimit(60);
}

void Game::run()
{
    sf::Music music;
    if (music.openFromFile("assets/audio/DungeonRPG.ogg")) {
        music.setLooping(true);
        music.play();
    }

    while(window.isOpen())
    {
        input();

        window.clear();

        renderer.draw(
            window,
            map,
            player,
            enemies,
            currentFloor
        );

        hudRenderer.draw(
            window,
            player,
            enemies,
            currentFloor
        );

        window.display();
    }
}

void Game::input()
{
    while(const std::optional event =
        window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if(const auto* keyPressed =
            event->getIf<sf::Event::KeyPressed>())
        {
            auto [dx, dy] = parseKeyPressedToCoord(*keyPressed);
            
            // TODO: Implement "Skip Turn / Wait" mechanic. Currently ignoring {0, 0} ('X' key).
            if (dx != 0 || dy != 0) processInteraction(dx, dy); 
        }
    }
}

std::pair<int, int> Game::parseKeyPressedToCoord(
    const sf::Event::KeyPressed& keyEvent
) const
{
    static const std::unordered_map<sf::Keyboard::Key, std::pair<int, int>> moveMap = {
        {sf::Keyboard::Key::W, {0, -1}},
        {sf::Keyboard::Key::S, {0, 1}},
        {sf::Keyboard::Key::A, {-1, 0}},
        {sf::Keyboard::Key::D, {1, 0}},
        {sf::Keyboard::Key::Q, {-1, -1}},
        {sf::Keyboard::Key::E, {1, -1}},
        {sf::Keyboard::Key::Z, {-1, 1}},
        {sf::Keyboard::Key::C, {1, 1}},
        {sf::Keyboard::Key::X, {0, 0}}
    };

    auto it = moveMap.find(keyEvent.code);
    if (it != moveMap.end()) {
        return it->second; 
    }

    return {0, 0}; 

}

void Game::processInteraction(int dx, int dy)
{
    int newX = player.getX() + dx;
    int newY = player.getY() + dy;

    // Enemy interaction
    auto enemyIt = getEnemyIteratorAt(newX, newY);
    if (enemyIt != enemies.end())
    {
        std::cout << "Player attacks enemy at (" << newX << ", " << newY << ")" << std::endl;

        // one shot
        enemies.erase(enemyIt);
        player.addExp(10);
        
        return; 
    }

    // Movement interaction
    if (!map.isWalkable(newX, newY))
    {
        return; 
    }

    player.move(dx, dy);


    // Exit interaction 
    if (map.isExit(newX, newY))
    {
        currentFloor++;
        generator.generate(map, player, enemies);
        std::cout << "Player moved to floor " << currentFloor << std::endl;
    }   
}

std::vector<Enemy>::iterator Game::getEnemyIteratorAt(
    int x, 
    int y
)
{
    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        if (it->getX() == x && it->getY() == y)
        {
            return it;
        }
    }
    return enemies.end();
}