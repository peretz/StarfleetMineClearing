#include "Script.h"
#include <fstream>
#include <sstream>

Script::Script(const std::string& fileName)
{
    std::ifstream fieldFile(fileName);
    if (fieldFile.is_open())
    {
        std::string line;
        while(getline(fieldFile,line))
        {
            lineQueue.push(line);
        }
        
        fieldFile.close();
    }
}

bool Script::nextLine(std::queue<std::string>& instructionQueue)
{
    if (lineQueue.empty()) return false;

    std::string activeLine = lineQueue.front();
    lineQueue.pop();

    std::istringstream is(activeLine);
    std::string instruction;
    while(is >> instruction)
    {
        instructionQueue.push(instruction);
    }

    return true;
}

