#pragma once

#include "Field.h"
#include "Script.h"
#include <string>

class Simulation
{
    public:
        Simulation
        (
            const std::string& filedFileName,
            const std::string& scriptFileName
        );

        void run();

    private:

        Field field;
        Script script;

        int numberOfVolleysFired;
        int numberOfMoves;
        const int initialNumberOfMines;

    private:
        void step(Coordinate& vessel);
        void printResult(Field::FieldStatus fieldStatus);
        int score();
};
