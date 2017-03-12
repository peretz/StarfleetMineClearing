#include "Field.h"
#include <fstream>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <stdlib.h>

Field::Field(const std::string& fileName):
    fieldStatus(fieldStatusNoMines),
    numberOfMines(0)
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

Coordinate Field::getCenter() const
{
    Coordinate temp;
    temp.y = static_cast<int>(grid.size() / 2);
    temp.x = static_cast<int>(grid[0].size() / 2);

    return temp;
}

int Field::getNumberOfMines() const
{
    return numberOfMines;
}

Field::FieldStatus Field::getStatus() const
{
    return fieldStatus;
}

// Vector math to transform the internal grid matrix to a vessel view.
//
// 1) We know the location of the ship (Xs, Yx) in terms of the origin (0,0).
// Also, we know the location of each mine (Xmi, Ymi) in termos of the origin.
// Given this relationship we can deduce the difference between the ship and
// each mine (Xdelta, Ydelta) as:
//
// Xdelta = -Xs + Xmi
// Ydelta = -Ys + Ymi
//
// 2) We are interested in the vessel being in the middle of its view. Because of this,
// we need to iterate through each mine and find the largest absolute Xdelta and Ydelta
// (xMaxDelta, yMaxDelta).
//
// xMaxDelta = max(abs(Xdeltai))
// yMaxDelta = max(abs(Ydeltai))
//
// where Xdeltai is iterating through all X coordinates for the mines and Ydeltai is 
// iterating through all Y coordinates.
//
// 3) To obtain the origin of the view (xViewOrigin, yViewOrigin) and the end point of the view
// (xViewEnd, yViewEnd), we can use vector math and the (xMaxDelta, yMaxDelta) coordinate
// we deduce in point 2).
//
// xViewOrigin = Xs - xMaxDelta
// yViewOrigin = Ys - yMaxDelta
//
// xViewEnd = Xs + xMaxDelta
// yViewEnd = Ys + yMaxDelta
//
// These last two coordinates represent the view from the perspective of the coordinate passed
// to the printView() method, which can be outside the dimensions original set for the field
// grid.
//
// @TODO: Clean up/refactor method.
std::string Field::getView(const Coordinate& coordinate) const
{
    int xMaxDelta = 0;
    int yMaxDelta = 0;

    const int ySize = grid.size();
    const int xSize = grid[0].size();
    for(int y = 0; y < ySize; ++y)
    {
        for(int x = 0; x < xSize; ++x)
        {
            if 
            (
                (grid[y][x] >= mineClosest && grid[y][x] <= mineFarthest) ||
                (grid[y][x] == mineMissed)
            )
            {
                // Step 1 and 2: Obtain max distance so that all mines are in
                // the coordinate view and the coordinate is still in the middle
                // of the view.
                const int tempX = abs(x - coordinate.x);
                xMaxDelta = std::max(xMaxDelta, tempX);

                const int tempY = abs(y - coordinate.y);
                yMaxDelta = std::max(yMaxDelta, tempY);
            }
        }
    }

    // Step 3: Computer coordinates to represent view.
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
                os += mapDepthToDisplayChar(grid[y][x]); 
            }
        }
        os += '\n';
    }

    return os;
}

void Field::clearMine(int x, int y)
{
    const int ySize = grid.size();
    const int xSize = grid[0].size();
    if ((y >= 0 && y < ySize) && (x >= 0 && x < xSize))
    {
        grid[y][x] = mapDisplayCharToDepth('.');
    }
}

void Field::dropView()
{
    const int ySize = grid.size();
    const int xSize = grid[0].size();
    for(int y = 0; y < ySize; ++y)
    {
        for(int x = 0; x < xSize; ++x)
        {
            if (grid[y][x] >= mineClosest && grid[y][x] <= mineFarthest)
            {
               --grid[y][x];
            }
        }
    }

    updateFieldStatus();
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
        // std::cout << "mapDepthToDisplayChar: " << value << std::endl;
        assert(value == mineMissed);
        return '*';
    }
}

void Field::updateFieldStatus()
{
    fieldStatus = fieldStatusNoMines;
    numberOfMines = 0;

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
                numberOfMines++;
            }
        }
    }
}
