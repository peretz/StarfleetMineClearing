/*
    This class allows you to load, manipulate and access the mines in
    the *.field file.
*/

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

        // Returns the center coordinate of your field. This center
        // coordinate is based on the sizes of your field at
        // initialization.
        Coordinate getCenter() const;

        // Returns the total number of active mines in the field.
        int getNumberOfMines() const;

        // Clears a mine in the specific (x, y) coordinate.
        void clearMine(int x, int y);

        enum FieldStatus
        {
            fieldStatusMined,
            fieldStatusMineMissed,
            fieldStatusNoMines
        };

        // Returns the status of your field.
        FieldStatus getStatus() const;

        // Returns a string with a squared view of the field using
        // the coordinate parameter as the center point of it.
        //
        // The view is large enough to include all the mines in the field.
        std::string getView(const Coordinate& center) const;

        // Moves all mines one step closer to the viewer's perspective.
        void dropView();

    private:

        int numberOfMines;
        FieldStatus fieldStatus;

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

        std::vector<std::vector<int> > grid;

    private:

        int mapDisplayCharToDepth(char value) const; 

        char mapDepthToDisplayChar(int value) const; 

        void updateFieldStatus();
};
