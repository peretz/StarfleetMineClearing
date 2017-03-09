#pragma once

#include <string>
#include <vector>

class Field
{
    public:

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

        Field(const std::string& fileName);

        void print();
        void dropView();

    private:
        std::vector<std::vector<int> > grid;

    private:
        int mapDisplayCharToDepth(char value); 
        char mapDepthToDisplayChar(int value); 
};
