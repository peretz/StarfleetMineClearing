#include "Simulation.h"
#include <iostream>
#include <queue>
#include <assert.h>

Simulation::Simulation
(
    const std::string& fieldFileName,
    const std::string& scriptFileName
):
    field(fieldFileName),
    script(scriptFileName),
    numberOfVolleysFired(0),
    numberOfMoves(0),
    initialNumberOfMines(field.getNumberOfMines())
{
}

void Simulation::run()
{
    int stepCount = 1;
    Coordinate vessel = field.getCenter();
    std::queue<std::string> instr;

    Field::FieldStatus fieldStatus = field.getStatus();
    while(!script.ended() && fieldStatus == Field::fieldStatusMined)
    {
        // Step <x>
        std::cout << "Step " << stepCount++ << std::endl;
        std::cout << std::endl;

        // The current minefield
        std::cout << field.getView(vessel);
        std::cout << std::endl;

        // The current instruction
        std::cout << script.getLine() << std::endl;
        std::cout << std::endl;

        // Execute one step of the simulation
        step(vessel);

        // The resultant field
        std::cout << field.getView(vessel);
        std::cout << std::endl;
        
        script.nextLine();
        fieldStatus = field.getStatus();
    }

    printResult(fieldStatus);
}

void Simulation::step(Coordinate& vessel)
{
    std::queue<std::string> instructions = script.parseInstructions();
    
    while (!instructions.empty())
    {
        // @TODO: Add logic for convert characters to lower case.
        std::string currentInstruction = instructions.front();
        instructions.pop();

        if (currentInstruction == "north")
        {
            vessel.y--;
            numberOfMoves++;
        }
        else if (currentInstruction == "south")
        {
            vessel.y++;
            numberOfMoves++;
        }
        else if (currentInstruction == "east")
        {
            vessel.x++;
            numberOfMoves++;
        }
        else if (currentInstruction == "west")
        {
            vessel.x--;
            numberOfMoves++;
        }
        else if (currentInstruction == "alpha")
        {
            // (-1, -1), (-1, 1), (1, -1), (1, 1)
            field.clearMine(vessel.x-1, vessel.y+1);
            field.clearMine(vessel.x-1, vessel.y-1);
            field.clearMine(vessel.x+1, vessel.y+1);
            field.clearMine(vessel.x+1, vessel.y-1);
            numberOfVolleysFired++;
        }
        else if (currentInstruction == "beta")
        {
            // (-1, 0), (0, -1), (0, 1), (1, 0)
            field.clearMine(vessel.x-1, vessel.y);
            field.clearMine(vessel.x, vessel.y+1);
            field.clearMine(vessel.x, vessel.y-1);
            field.clearMine(vessel.x+1, vessel.y);
            numberOfVolleysFired++;
        }
        else if (currentInstruction == "gamma")
        {
            // (-1, 0), (0, 0), (1, 0)
            field.clearMine(vessel.x-1, vessel.y);
            field.clearMine(vessel.x, vessel.y);
            field.clearMine(vessel.x+1, vessel.y);
            numberOfVolleysFired++;
        }
        else 
        { 
            assert(currentInstruction == "delta");

            // (0, -1), (0, 0), (0, 1)
            field.clearMine(vessel.x, vessel.y+1);
            field.clearMine(vessel.x, vessel.y);
            field.clearMine(vessel.x, vessel.y-1);
            numberOfVolleysFired++;
        }
    }

    field.dropView();
}

void Simulation::printResult(Field::FieldStatus fieldStatus)
{
    if 
    (
        (fieldStatus == Field::fieldStatusMineMissed) ||
        ((fieldStatus == Field::fieldStatusMined) && script.ended())
    )
    {
        std::cout << "fail (0)" << std::endl;
    }
    else if( (fieldStatus == Field::fieldStatusNoMines) && (!script.ended()) )
    {
        std::cout << "pass (1)" << std::endl;
    }
    else
    {
        assert((fieldStatus == Field::fieldStatusNoMines) && (script.ended()));

        std::cout << "pass (" << score() << ")" << std::endl;
    }

}

int Simulation::score()
{
    const int adjustsedNumOfVolleysScore = std::min(5*numberOfVolleysFired, 5*initialNumberOfMines);
    const int adjustedNumOfMovesScore = std::min(2*numberOfMoves, 3*initialNumberOfMines);
    return (10 * initialNumberOfMines - adjustsedNumOfVolleysScore - adjustedNumOfMovesScore);
}

