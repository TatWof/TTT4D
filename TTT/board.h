#ifndef BOARD_H
#define BOARD_H

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

namespace UTILITY
{
    
    inline int coord_to_pos(int x, int y, int z, int w)
    {
        return x * 1 + y * 3 + z * 9 + w * 27;
    }
    
    COORDS pos_to_coord(int pos)
    {
        std::array<int, 4> coords;
        int val = pos;
        
        for (size_t i = 3; i >= 0 ; i)
        {
            int temp{};
            int coef{1};
            for (size_t k = 0; k < i; k++) coef *= 3;
            
            for (size_t j = 0; j < 3; j++)
            {
                temp = val - coef * (coords[i] + j);
                if (temp < 0) break;
                val = temp;
                coords[i] = j;
                
            }
            if (val == 0) break;
        }
        
        return COORDS{coords}; 
    }
    
}
}

#endif