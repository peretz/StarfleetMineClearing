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
        
        enum FieldStatus
        {
            fieldStatusMined,
            fieldStatusMineMissed,
            fieldStatusNoMines
        };

        Field(const std::string& fileName);

        Coordinate getCenter();

        int getNumberOfMines();

        void clearCoordinate(int x, int y);

        void dropView();

        FieldStatus getStatus();

    private:
        // Using -2 so there is a gap between -2 and 0
        // and we can assert if the grid drops again
        // after reaching the same level.
        enum Mine
        {
            mineEmptyCell = -2,
            mineMissed = 0,
            mineClosest = 1, 
            mineFarthest = 52 
        };

        FieldStatus fieldStatus;
        int numberOfMines;

        std::vector<std::vector<int> > grid;

    private:
        friend std::string printView(const Coordinate& coordinate, const Field& field);

        int mapDisplayCharToDepth(char value) const; 
        char mapDepthToDisplayChar(int value) const; 

        void updateFieldStatus();
};
