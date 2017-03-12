/*
    This class is in charge of receiving two files, a field file and a
    script file, and using these two files it runs a simulation of the 
    program.

    Also, this class is in charge of printing the results of running the
    simulation.
*/

#pragma once

#include "Field.h"
#include "Script.h"
#include <string>

class Simulation
{
    public:
        Simulation
        (
            const std::string& fieldFileName,
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
