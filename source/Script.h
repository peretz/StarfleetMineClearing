#pragma once

#include <string>
#include <queue>

class Script
{
    public:
        Script(const std::string& fileName);

        bool nextLine(std::queue<std::string>& instructionQueue);

    private:
        std::queue<std::string> lineQueue;

};
