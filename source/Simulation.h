#pragma once

#include "Field.h"
#include "Script.h"
#include <string>

class Simulation
{
    public:
        Simulation
        (
            const std::string& filedFileName,
            const std::string& scriptFileName
        );

        void run();

    private:

        Field field;
        Script script;

    private:
        void step();

//        int score();
};
