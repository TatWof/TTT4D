#ifndef TTT4D_BOARD_H
#define TTT4D_BOARD_H

#include <array>

namespace TTT4D
{

struct COORDS
{
    std::array<int, 4> c;
    
    int& operator[](int a)
    {
        return c[a];
    }
};

struct BOARD
{
    std::array<int, 81> b{};
    
    BOARD()
    {
        clear();
    }

    void clear()
    {
        for (size_t i = 0; i < 81; i++)
        b[i] = 0;  
    }
    
    int& operator[](int a)
    {
        return b[a];
    }
};

}

#endif