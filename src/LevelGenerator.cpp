#include <random>
#include <vector>

#include "LevelGenerator.h"
#include "Room.h"


void LevelGenerator::createTunnel(Map& map, int start, int end, int constantCoord, bool isHorizontal) 
{
    int minCoord = std::min(start, end);
    int maxCoord = std::max(start, end);

    for (int i = minCoord; i <= maxCoord; ++i) 
    {
        if (isHorizontal) {
            map.setTile(i, constantCoord, TileType::Floor);
        } else {
            map.setTile(constantCoord, i, TileType::Floor);
        }
    }
}

bool LevelGenerator::isOccupied(
    int x,
    int y,
    const std::vector<Enemy>& enemies
)
{
    for(const Enemy& enemy : enemies)
    {
        if(
            enemy.getX() == x
            &&
            enemy.getY() == y
        )
        {
            return true;
        }
    }

    return false;
}

void LevelGenerator::spawnEnemies(
    const std::vector<Room>& rooms,
    std::vector<Enemy>& enemies,
    int count,
    int exitX,
    int exitY
)
{
    if(rooms.size() < 2)
    {
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> roomDist(
        1,
        static_cast<int>(rooms.size()) - 1
    );

    for(int i = 0; i < count; i++)
    {
        bool placed = false;

        while(!placed)
        {
            const Room& room =
                rooms[roomDist(gen)];

            std::uniform_int_distribution<> xDist(
                room.x,
                room.x + room.width - 1
            );

            std::uniform_int_distribution<> yDist(
                room.y,
                room.y + room.height - 1
            );

            int x = xDist(gen);
            int y = yDist(gen);

            if(isOccupied(x, y, enemies))
            {
                continue;
            }

            if(x == exitX && y == exitY)
            {
                continue;
            }

            enemies.emplace_back(x, y);

            placed = true;
        }
    }
}

void LevelGenerator::generate(
    Map& map,
    Player& player,
    std::vector<Enemy>& enemies
)
{
    map.fill(TileType::Wall);
    enemies.clear(); // not sure if it should be here, maybe it should be in Game method that calls this one

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<Room> rooms;

    // Generate rooms
    for(int i = 0; i < 10; i++)
    {
        std::uniform_int_distribution<> widthDist(5, 10);
        std::uniform_int_distribution<> heightDist(4, 8);

        int roomWidth = widthDist(gen);
        int roomHeight = heightDist(gen);

        std::uniform_int_distribution<> xDist(
            1,
            map.getWidth() - roomWidth - 2
        );

        std::uniform_int_distribution<> yDist(
            1,
            map.getHeight() - roomHeight - 2
        );

        Room room(
            xDist(gen),
            yDist(gen),
            roomWidth,
            roomHeight
        );

        bool intersects = false;

        for(const Room& existing : rooms)
        {
            if(room.intersects(existing))
            {
                intersects = true;
                break;
            }
        }

        if(intersects)
        {
            continue;
        }

        rooms.push_back(room);
    }

    for(const Room& room : rooms)
    {
        for(auto cell : room.getCells())
        {
            map.setTile(
                cell.first,
                cell.second,
                TileType::Floor
            );
        }
    }

    // Connect rooms with tunnels
    for (size_t i = 1; i < rooms.size(); ++i) 
    {
        int prevX = rooms[i - 1].centerX();
        int prevY = rooms[i - 1].centerY();
        int currX = rooms[i].centerX();
        int currY = rooms[i].centerY();

        // Randomly decide the order of tunnel creation
        std::uniform_int_distribution<> coinFlip(0, 1);
        if (coinFlip(gen) == 0) 
        {
            // horizontal first, then vertical
            createTunnel(map, prevX, currX, prevY, true);
            createTunnel(map, prevY, currY, currX, false);
        } 
        else 
        {
            // vertical first, then horizontal
            createTunnel(map, prevY, currY, prevX, false);
            createTunnel(map, prevX, currX, currY, true);
        }
    }

    if(!rooms.empty())
    {
        // Place player in the center of the first room
        player.setPosition(
            rooms[0].centerX(),
            rooms[0].centerY()
        );

        // Place exit in the center of the last room
        map.setTile(rooms.back().centerX(), rooms.back().centerY(), TileType::Exit); 

        // Spawn enemies
        spawnEnemies(
            rooms,
            enemies,
            8,
            rooms.back().centerX(),
            rooms.back().centerY()
        );
    }
}