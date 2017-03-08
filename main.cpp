#include "Field.h"
#include <iostream>
#include <fstream>

int main(int argc, char*argv[])
{
    if (argc <= 1) // @TODO: Modify back to two.
    {
        std::cout << "Program " << argv[0] << " requires parameters." << std::endl;
    }
    else
    {
        Field field(argv[1]);
        field.print();

//        std::cout << "Script file; " << argv[2] << std::endl;
    }

    return 0;
}
