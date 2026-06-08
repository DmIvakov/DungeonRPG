    #include "Room.h"

    Room::Room(int x, int y, int width, int height)
        : 
        x(x),
        y(y), 
        width(width), 
        height(height)
    {
    }

    int Room::centerX() const
    {
        return x + width / 2;
    }

    int Room::centerY() const
    {
        return y + height / 2;
    }

    bool Room::intersects(const Room& other) const
    {
        int leftA = x;
        int rightA = x + width;
        int topA = y;
        int bottomA = y + height;

        int leftB = other.x;
        int rightB = other.x + other.width;
        int topB = other.y;
        int bottomB = other.y + other.height;

        // True if rectangles overlap (excludes mere touching edges)
        return (leftA < rightB) && (rightA > leftB) && (topA < bottomB) && (bottomA > topB);
    }

    std::vector<std::pair<int,int>> Room::getCells() const
    {
        std::vector<std::pair<int,int>> cells;
        cells.reserve(static_cast<size_t>(width) * static_cast<size_t>(height));

        for (int j = y; j < y + height; ++j) {
            for (int i = x; i < x + width; ++i) {
                cells.emplace_back(i, j);
            }
        }

        return cells;
    }