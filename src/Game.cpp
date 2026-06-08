#include <iostream>
#include <vector>

#include "Game.h"
#include "Renderer.h"

Game::Game()
    :
    map(40, 20),
    player(0, 0),
    isRunning(true),
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
    while(isRunning)
    {
        Renderer::draw(
            map,
            player,
            enemies,
            currentFloor
        );

        input();
    }
}

void Game::input()
{
    int dx = 0;
    int dy = 0; 

    unsigned char key;

    std::cin >> key;
 
    switch(key)
    {
        case 'w':
            dy = -1;
            break;

        case 's':
            dy = 1;
            break;

        case 'a':
            dx = -1;
            break;

        case 'd':
            dx = 1;
            break;

        case 'q':
            dx = -1;
            dy = -1;
            break;
        
        case 'e':
            dx = 1;
            dy = -1;
            break;
        
        case 'z':
            dx = -1;
            dy = 1;
            break;
        
        case 'x':
            dx = 1;
            dy = 1;
            break;

        case 127: // Delete key for exiting the game
            isRunning = false;
            break;
    }

    int newX = player.getX() + dx;
    int newY = player.getY() + dy;

    // Check if the player has reached the exit
    if(map.isExit(newX, newY))
    {
        currentFloor++;

        generator.generate(
            map,
            player,
            enemies
        );

        return;
    }


        
    // Check for enemy at the new position

    // Enemy* enemy = getEnemyAt(newX, newY);

    auto it = getEnemyIteratorAt(newX, newY);

    if(it != enemies.end())
    {
        enemies.erase(it);

        player.addExp(10);

        return;
    }

    // if(enemy != nullptr)
    // {
    //     enemy->takeDamage(
    //         player.getDamage()
    //     );

    //     player.addExp(10);

    //     return;
    // }



    // Check if the new position is walkable
    if(map.isWalkable(newX, newY))
    {
        player.move(dx, dy);
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
