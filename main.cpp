#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char*argv[])
{
    if (argc <= 1) // @TODO: Modify back to two.
    {
        std::cout << "Program " << argv[0] << " requires parameters." << std::endl;
    }
    else
    {
        std::cout << "Field file; " << argv[1] << std::endl;
        std::string line;
        std::ifstream fieldFile(argv[1]);
        if (fieldFile.is_open())
        {
            while(getline(fieldFile,line))
            {
                for(int i = 0; i < line.size(); ++i)
                {
                    std::cout << line[i] <<  "/";
                }
                std::cout << std::endl;
            }
            
            fieldFile.close();
        }


//        std::cout << "Script file; " << argv[2] << std::endl;
    }

    return 0;
}
