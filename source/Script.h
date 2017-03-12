/*
    This class allows you to load, control and access the instructions in
    the *.script file. Accessing the instructions is done in a line
    basis, but you can go futher an parse the instructions within
    that line.
*/

#pragma once

#include <string>
#include <queue>

class Script
{
    public:
        Script(const std::string& fileName);

        // Returns a string with the active line in the script.
        std::string getLine() const;

        // Parses the instructions in the active line.
        std::queue<std::string> parseInstructions() const;

        // If there are still more lines in the script,
        // it will move to the next line.
        void nextLine();

        // Check if the script has completed.
        bool ended();

    private:
        std::queue<std::string> lineQueue;

};
