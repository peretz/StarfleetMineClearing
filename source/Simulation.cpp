#include "Simulation.h"
#include <iostream>
#include <queue>

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

        // @TODO: Add logic to update field
        // Move vessel
        // Shoot field
        step();

        // The resultant field
        field.dropView();
        std::cout << printView(vessel, field);
        std::cout << std::endl;

        script.nextLine();
    }

    // @TODO:
    // Ouput pass/fail message
}

void Simulation::step()
{
    std::queue<std::string> instructions = script.parseInstructions();
    
    while (!instructions.empty())
    {
        std::string currentInstuction = instructions.front();
        instructions.pop();

        //executeInstruction(currentInstuction);
    }
}
