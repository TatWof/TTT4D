#ifndef TTT_PRECOMPUTE_H
#define TTT_PRECOMPUTE_H

#include <fstream>
#include <string>
#include <exception>
#include <iostream>
#include "TTT_processor.h"

#define TRITUPLES "trituple.txt"

using TTT4D::PROCESSOR;

namespace TTT4D::PRECOMPUTE
{
    void trituplefunc(bool& kill, int pos, int coef, std::ofstream& file)
    {
        file << pos << " " << pos + coef << " " << pos + coef * 2 << "\n";
    }

    void tritupler()
    {
        PROCESSOR<std::ofstream&> procker{trituplefunc};
        std::ofstream file;

        file.open("trituple.txt");

        procker.DO__ER(file);
        file.close();
    }

    void trituple_extracter(std::vector<std::array<int, 3>>& vec)
    {
        std::ifstream file{TRITUPLES};
        std::stringstream ss;
        std::string temp;
        std::array<int, 3> arr;

        while (!file.is_open()) 
        {
            file.close();
            tritupler();
            file.open(TRITUPLES);
        }

        while (file.good())
        {
            std::getline(file, temp);
            ss << temp;

            for (size_t i = 0; i < 3; i++)
            {   
                std::getline(ss, temp, ' ');
                arr[i] = std::stoi(temp);
            }
            vec.push_back(arr);
        }
        file.close();
    }

    std::vector<std::array<int, 3>> trituple_match(int pos, std::vector<std::array<int, 3>>& vec)
    {
        std::vector<std::array<int, 3>> temp;
        
        for (size_t i = 0; i < vec.size(); i++)
        {
            if (vec[i][0] == pos || vec[i][1] == pos || vec[i][2] == pos)
            {
                temp.push_back(vec[i]);
            }
        }

        return temp;
        
    }

    char checksum(std::string filename)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) std::cerr << filename << " not found\n";

        unsigned char checksum;
        char byte;

        while (file.get(byte))
        {
            checksum ^= static_cast<unsigned char>(byte);
        }
        file.close();
        return checksum;
    }


} 



#endif


