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

        Coordinate getCenter() const;

        int getNumberOfMines() const;

        FieldStatus getStatus() const;

        std::string getView(const Coordinate& coordinate) const;

        void clearCoordinate(int x, int y);

        void dropView();

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

        int numberOfMines;
        FieldStatus fieldStatus;

        std::vector<std::vector<int> > grid;

    private:

        int mapDisplayCharToDepth(char value) const; 
        char mapDepthToDisplayChar(int value) const; 

        void updateFieldStatus();
};
