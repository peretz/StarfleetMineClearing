#include "Field.h"
#include <fstream>
#include <iostream>

Field::Field(const std::string& fileName)
{
    std::string line;
    std::ifstream fieldFile(fileName);
    if (fieldFile.is_open())
    {
        while(getline(fieldFile,line))
        {
            for(int i = 0; i < line.size(); ++i)
            {
                std::cout << line[i];
            }
            std::cout << std::endl;
        }
        
        fieldFile.close();
    }

}

void Field::printGrid()
{
}
