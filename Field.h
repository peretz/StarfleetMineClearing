#pragma once

#include <string>
#include <vector>

class Field
{
    public:
        Field(const std::string& fileName);

        void print();
        void dropView();

    private:
        std::vector<std::vector<int> > grid;

    private:
        int mapDisplayCharToDepth(char value); 
        char mapDepthToDisplayChar(int value); 
};
