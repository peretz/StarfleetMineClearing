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
    std::queue<std::string> instr;
    while(!script.ended())
    {
        // Step <x>
        std::cout << "Step " << stepCount++ << std::endl;
        std::cout << std::endl;

        // The current minefield
        std::cout << field << std::endl;
        std::cout << std::endl;

        // The current instruction
        std::cout << script.getLine() << std::endl;
        std::cout << std::endl;

        // @TODO: Add logic to update field
        // Move vessel
        // Shoot field

        // The resultant field
        field.dropView();
        std::cout << field << std::endl;
        std::cout << std::endl;

        script.nextLine();
    }

    // @TODO:
    // Ouput pass/fail message
}

//        if (instr.empty())
//        {
//            std::cout << std::endl;
//        }
//        else
//        {
//            while (!instr.empty())
//            {
//                std::cout << instr.front() << std::endl;
//                instr.pop();
//            }
//        }

