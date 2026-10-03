#ifndef SAVER_H
#define SAVER_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "board.h"

using TTT4D::BOARD;

namespace TTT4D::SAVER
{
    bool WRITETO(std::string filename, BOARD& b)
    {
        std::ofstream file{};
        std::stringstream ss;
        file.open(filename);
        if (!file.is_open()) return false;

        for (size_t i = 0; i < 81; i++)
        {
            ss << b[i] << " ";
        }

        file << ss.str() << std::endl;
        return true;
    }

    bool LOAD(std::string filename, BOARD& b)
    {
        std::ifstream file{};
        std::string buffer;
        std::istringstream ss;
        file.open(filename);
        if (!file.is_open()) return false;

        std::getline(file, buffer);
        ss.str(buffer);

        for (size_t i = 0; i < 81; i++)
        {
            std::getline(ss, buffer, ' ');
            b[i] = std::stoi(buffer);
        }
        return true;
    }
}


#endif