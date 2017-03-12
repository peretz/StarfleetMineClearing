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

std::string Script::getLine() const
{
    return lineQueue.front();
}

std::queue<std::string> Script::parseInstructions() const
{
    std::string activeLine = lineQueue.front();

    std::queue<std::string> instructionQueue;
    std::istringstream is(activeLine);
    std::string instruction;
    while(is >> instruction)
    {
        instructionQueue.push(instruction);
    }

    return instructionQueue;
}

void Script::nextLine()
{
    if (!ended())
    {
        lineQueue.pop();
    }
}

bool Script::ended()
{
    return lineQueue.empty();
}
