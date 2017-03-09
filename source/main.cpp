#include "Field.h"
#include "Script.h"
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
        Field field(argv[1]);
        Script script(argv[2]);

        char step = 'N';
        std::queue<std::string> instr;
        while(script.nextLine(instr))
        {
//            std::cout << field << std::endl;
//            field.dropView();
//            std::cout << field << std::endl;

            if (instr.empty())
            {
                std::cout << std::endl;
            }
            else
            {
                while (!instr.empty())
                {
                    std::cout << instr.front() << std::endl;
                    instr.pop();
                }
            }
        }

//        std::cout << "Script file; " << argv[2] << std::endl;
    }

    return 0;
}
