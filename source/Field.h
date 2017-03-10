#pragma once

#include <string>
#include <vector>
#include <sstream>

struct Coordinate 
{
    int x;
    int y;
};

class Field
{
    public:
        Field(const std::string& fileName);

        Coordinate getMiddleCoordinate();

        void dropView();

    private:
        // Using -2 so there is a gap between -2 and 0
        // and we can assert if the grid drops again
        // after reaching the same level.
        enum Mine
        {
            mineEmptyCell = -2,
            mineSameAsView = 0,
            mineClosest = 1, 
            mineFarthest = 52 
        };

        friend std::string printView(const Coordinate& coordinate, const Field& field);

        std::vector<std::vector<int> > grid;

    private:
        int mapDisplayCharToDepth(char value) const; 
        char mapDepthToDisplayChar(int value) const; 
};
