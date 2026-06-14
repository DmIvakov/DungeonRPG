#include <iostream>
#include <vector>

#include "Game.h"
#include "SfmlRenderer.h"

Game::Game()
    :
    window(
        sf::VideoMode(
            sf::Vector2u(
                40 * 32,
                20 * 32
            )
        ),
        "Dungeon RPG"
    ),
    map(40, 20),
    player(0, 0),
    currentFloor(1)
{
    generator.generate(
        map,
        player,
        enemies
    );
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

        renderer.draw(
            window,
            map,
            player,
            enemies,
            currentFloor
        );
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
            int dx = 0;
            int dy = 0;

            switch(keyPressed->code)
            {
                case sf::Keyboard::Key::W:
                    dy = -1;
                    break;

                case sf::Keyboard::Key::S:
                    dy = 1;
                    break;

                case sf::Keyboard::Key::A:
                    dx = -1;
                    break;

                case sf::Keyboard::Key::D:
                    dx = 1;
                    break;

                case sf::Keyboard::Key::Q:
                    dy = -1;
                    dx = -1;
                    break;

                case sf::Keyboard::Key::E:
                    dy = -1;
                    dx = 1;
                    break;
                    
                case sf::Keyboard::Key::Z:
                    dy = 1;
                    dx = -1;
                    break;

                case sf::Keyboard::Key::X:
                    break;
                
                case sf::Keyboard::Key::C:
                    dy = 1;
                    dx = 1;
                    break;

                default:
                    break;
            }

            if(dx != 0 || dy != 0)
            {
                int newX = player.getX() + dx;
                int newY = player.getY() + dy;

                // Check for enemy at the new position

                // Enemy* enemy = getEnemyAt(newX, newY);

                auto it = getEnemyIteratorAt(newX, newY);

                if(it != enemies.end())
                {
                    enemies.erase(it);

                    player.addExp(10);

                    return;
                }

                if(map.isWalkable(newX, newY))
                {
                    player.move(dx, dy);

                    if(map.isExit(newX, newY))
                    {
                        currentFloor++;
                        generator.generate(
                            map,
                            player,
                            enemies
                        );
                    }
                }
            }
        }
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


Enemy* Game::getEnemyAt(
    int x,
    int y
)
{
    auto it = getEnemyIteratorAt(x, y);
    if (it != enemies.end())
    {
        return &(*it);
    }
    return nullptr;
}
