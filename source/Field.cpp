#include "Field.h"
#include <fstream>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <stdlib.h>

Field::Field(const std::string& fileName):
    fieldStatus(fieldStatusNoMines)
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

    updateFieldStatus();
}

Coordinate Field::getCenter()
{
    Coordinate temp;
    temp.y = static_cast<int>(grid.size() / 2);
    temp.x = static_cast<int>(grid[0].size() / 2);

    return temp;
}

void Field::clearCoordinate(int x, int y)
{
    grid[y][x] = mapDisplayCharToDepth('.');
}

void Field::dropView()
{
    const int ySize = grid.size();
    const int xSize = grid[0].size();
    for(int i = 0; i < ySize; ++i)
    {
        for(int j = 0; j < xSize; ++j)
        {
            if (grid[i][j] >= mineClosest)
            {
               --grid[i][j];
            }
        }
    }

    updateFieldStatus();
}

Field::FieldStatus Field::getStatus()
{
    return fieldStatus;
}

int Field::mapDisplayCharToDepth(char value) const
{
    if (value == '.')
    { 
        return mineEmptyCell;
    }
    else if ((value >= 'a') && (value <= 'z'))
    {
        return (value - 'a') + 1;
    }
    else if ((value >= 'A') && (value <= 'Z'))
    {
        return (value - 'A') + 27;
    }
    else
    {
        // std::cout << "mapDisplayCharToDepth: " << value << std::endl;
        assert(value == '*');
        return 0;
    }
}

char Field::mapDepthToDisplayChar(int value) const
{
    if (value == mineEmptyCell)
    {
        return '.';
    }
    else if ((value >= mineClosest) && (value <= 26))
    {
        return (value + 'a') - 1;
    }
    else if ((value >= 27) && (value <= mineFarthest))
    {
        return (value + 'A') - 27;
    }
    else 
    {
        std::cout << "mapDepthToDisplayChar: " << value << std::endl;
        assert(!value);
        return '*';
    }
}

void Field::updateFieldStatus()
{
    fieldStatus = fieldStatusNoMines;

    const int ySize = grid.size();
    const int xSize = grid[0].size();
    for(int y = 0; y < ySize; ++y)
    {
        if (fieldStatus == fieldStatusMineMissed)
        {
            break;
        }

        for(int x = 0; x < xSize; ++x)
        {
            if (grid[y][x] == mineMissed)
            {
                fieldStatus = fieldStatusMineMissed;
                break;
            }

            if (grid[y][x] >= mineClosest && grid[y][x] <= mineFarthest)
            {
                fieldStatus = fieldStatusMined;
            }
        }
    }
}

// @TODO: Clean up method and document vector math used.
std::string printView(const Coordinate& coordinate, const Field& field)
{
    int xMaxDelta = 0;
    int yMaxDelta = 0;

    const int ySize = field.grid.size();
    const int xSize = field.grid[0].size();
    for(int y = 0; y < ySize; ++y)
    {
        for(int x = 0; x < xSize; ++x)
        {
            if (field.grid[y][x] >= Field::mineClosest)
            {
                const int tempX = abs(x - coordinate.x);
                xMaxDelta = std::max(xMaxDelta, tempX);

                const int tempY = abs(y - coordinate.y);
                yMaxDelta = std::max(yMaxDelta, tempY);
            }
        }
    }

    const int yViewOrigin = coordinate.y - yMaxDelta;
    const int xViewOrigin = coordinate.x - xMaxDelta;
    const int yViewEnd = coordinate.y + yMaxDelta;
    const int xViewEnd = coordinate.x + xMaxDelta;

    std::string os;
    for(int y = yViewOrigin; y <= yViewEnd; ++y)
    {
        // @TODO: Optimize inner loop so that if it is out of bounds
        // you add all the '.' that are needed.
        for(int x = xViewOrigin; x <= xViewEnd; ++x)
        {
            if ((y < 0 || y >= ySize) || (x < 0 || x >= xSize))
            {
                os += '.';
            }
            else
            {
                os += field.mapDepthToDisplayChar(field.grid[y][x]); 
            }
        }
        os += '\n';
    }

    return os;
}
