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
        char step = 'N';
        do {
            field.print();
            std::cout << std::endl;
            field.dropView();
            field.print();
            std::cout << std::endl;

            std::cout << "Should we continue (Y/N)?" << std::endl;
            std::cin >> step;
        } while (step == 'Y');

//        std::cout << "Script file; " << argv[2] << std::endl;
    }

    return 0;
}
