#pragma once

#include <string>
#include <queue>

class Script
{
    public:
        Script(const std::string& fileName);

        std::string getLine();

        std::queue<std::string> parseInstructions();

        void nextLine();

        bool ended();

    private:
        std::queue<std::string> lineQueue;

};
