#ifndef TTT4D_FILEIO_H
#define TTT4D_FILEIO_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include "board.h"

using TTT4D::BOARD;
using std::string;

namespace TTT4D::FILEIO
{
    bool _WRITE(string filename, std::stringstream& buffer)
    {
        std::ofstream file{};
        file.open(filename);
        if (!file.is_open()) return false;

        file << buffer.str();
        return true;
    }

    bool _READ(string filename, std::stringstream& buffer)
    {
        std::ifstream file{};
        file.open(filename);
        if (!file.is_open()) return false;

        buffer << file.rdbuf();
        return true;
    }
    
    
    bool SAVEBOARD(std::string filename, BOARD& b)
    {
        std::stringstream ss;

        for (size_t i = 0; i < 81; i++)
        {
            ss << b[i] << " ";
        }

        return _WRITE(filename, ss);
    }

    bool LOADBOARD(std::string filename, BOARD& b)
    {
        std::stringstream buffer;
        std::string str;

        if (!_READ(filename, buffer)) return false;
        
        std::getline(buffer, str);
        buffer.str(str);

        for (size_t i = 0; i < 81; i++)
        {
            std::getline(buffer, str, ' ');
            b[i] = std::stoi(str);
        }
        return true;
    }
}


#endif