#ifndef TTT4D_UTILITY_H
#define TTT4D_UTILITY_H

namespace TTT4D::UTILITY
{
    bool playerturncheck(int turn)
    {
        return (turn % 2 == 0);
    }

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


#endif