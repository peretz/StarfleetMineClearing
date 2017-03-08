#include "Field.h"
#include <fstream>
#include <iostream>
#include <assert.h>

Field::Field(const std::string& fileName)
{
    std::string line;
    std::ifstream fieldFile(fileName);
    if (fieldFile.is_open())
    {
        while(getline(fieldFile,line))
        {
            std::vector<int> grid_line(line.size(), 0);
            for(int i = 0; i < line.size(); ++i)
            {
                grid_line[i] = mapDisplayCharToDepth(line[i]);
            }

            grid.push_back(grid_line);
        }
        
        fieldFile.close();
    }
}

void Field::print()
{
    const int ySize = grid.size();
    const int xSize = grid[0].size();
    for(int i = 0; i < ySize; ++i)
    {
        for(int j = 0; j < xSize; ++j)
        {
            std::cout << mapDepthToDisplayChar(grid[i][j]);
        }
        std::cout << std::endl;
    }
}

int Field::mapDisplayCharToDepth(char value)
{
    if (value == '.')
    {
        return 0;
    }
    else if ((value >= 'a') && (value <= 'z'))
    {
        return (value - 'a') + 1;
    }
    else if ((value >= 'A') && (value <= 'Z'))
    {
        return (value - 'A') + 27;
    }
    else if (value == '*')
    {
        return -1;
    }
    else
    {
        assert(false);
    }
}

char Field::mapDepthToDisplayChar(int value)
{
    if (value == 0)
    {
        return '.';
    }
    else if ((value >= 1) && (value <= 26))
    {
        return (value + 'a') - 1;
    }
    else if ((value >= 27) && (value <= 52))
    {
        return (value + 'A') - 27;
    }
    else if (value == -1)
    {
        return '*';
    }
    else
    {
        assert(false);
    }
}
