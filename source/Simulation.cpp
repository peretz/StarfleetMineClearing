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
    script(scriptFileName)
{
}

void Simulation::run()
{
    int stepCount = 1;
    Coordinate vessel = field.getCenter();
    std::queue<std::string> instr;
    while(!script.ended())
    {
        // Step <x>
        std::cout << "Step " << stepCount++ << std::endl;
        std::cout << std::endl;

        // The current minefield
        std::cout << printView(vessel, field);
        std::cout << std::endl;

        // The current instruction
        std::cout << script.getLine() << std::endl;
        std::cout << std::endl;

        // Execute one step of the simulation
        step(vessel);

        // The resultant field
        std::cout << printView(vessel, field);
        std::cout << std::endl;

        script.nextLine();
    }

    // @TODO:
    // Ouput pass/fail message
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
        }
        else if (currentInstruction == "south")
        {
            vessel.y++;
        }
        else if (currentInstruction == "east")
        {
            vessel.x++;
        }
        else if (currentInstruction == "west")
        {
            vessel.x--;
        }
        else if (currentInstruction == "alpha")
        {
            // (-1, -1), (-1, 1), (1, -1), (1, 1)
            field.clearCoordinate(vessel.x-1, vessel.y+1);
            field.clearCoordinate(vessel.x-1, vessel.y-1);
            field.clearCoordinate(vessel.x+1, vessel.y+1);
            field.clearCoordinate(vessel.x+1, vessel.y-1);
        }
        else if (currentInstruction == "beta")
        {
            // (-1, 0), (0, -1), (0, 1), (1, 0)
            field.clearCoordinate(vessel.x-1, vessel.y);
            field.clearCoordinate(vessel.x, vessel.y+1);
            field.clearCoordinate(vessel.x, vessel.y-1);
            field.clearCoordinate(vessel.x+1, vessel.y);
        }
        else if (currentInstruction == "gamma")
        {
            // (-1, 0), (0, 0), (1, 0)
            field.clearCoordinate(vessel.x-1, vessel.y);
            field.clearCoordinate(vessel.x, vessel.y);
            field.clearCoordinate(vessel.x+1, vessel.y);
        }
        else 
        { 
            assert(currentInstruction == "delta");

            // (0, -1), (0, 0), (0, 1)
            field.clearCoordinate(vessel.x, vessel.y+1);
            field.clearCoordinate(vessel.x, vessel.y);
            field.clearCoordinate(vessel.x, vessel.y-1);
        }
    }

    field.dropView();
}
