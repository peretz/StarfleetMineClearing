#include "Simulation.h"
#include <iostream>
#include <fstream>

int main(int argc, char*argv[])
{
    if (argc <= 2)
    {
        std::cout << "Program " << argv[0] << " requires parameters." << std::endl;
    }
    else
    {
        Simulation simulation(argv[1], argv[2]);
        simulation.run();
    }

    return 0;
}
