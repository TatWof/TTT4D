#ifndef TTT_PROCESSOR_H
#define TTT_PROCESSOR_H

#include "board.h"
#include <stddef.h>
#include <array>
#include <sstream>
#include <functional>
#include <exception>

namespace TTT4D
{


template <typename... ARGS>
class PROCESSOR
{
    private:
    using dofunction = std::function<void(bool&, int, int, ARGS...)>;

    bool kill{false};

    void DO_BASE(int pos, int coef, ARGS... args)
    {
        func(kill, pos, coef, args...);

        if (kill) throw 0; // starts kill sequence
    }
    
    void DO_X(int pos, ARGS... args)          { DO_BASE(pos, 1, args...); }
    void DO_Y(int pos, ARGS... args)          { DO_BASE(pos, 3, args...); }
    void DO_Z(int pos, ARGS... args)          { DO_BASE(pos, 9, args...); }
    void DO_W(int pos, ARGS... args)          { DO_BASE(pos, 27, args...); }
    
    void DO_XY00(int pos, ARGS... args)       { DO_BASE(pos, 4, args...); }
    void DO_XY02(int pos, ARGS... args)       { DO_BASE(pos, 2, args...); }
    
    void DO_XZ00(int pos, ARGS... args)       { DO_BASE(pos, 10, args...); }
    void DO_XZ02(int pos, ARGS... args)       { DO_BASE(pos, 8, args...); }
    
    void DO_XW00(int pos, ARGS... args)       { DO_BASE(pos, 28, args...); }
    void DO_XW02(int pos, ARGS... args)       { DO_BASE(pos, 26, args...); }
    
    void DO_YZ00(int pos, ARGS... args)       { DO_BASE(pos, 12, args...); }
    void DO_YZ06(int pos, ARGS... args)       { DO_BASE(pos, 6, args...); }
    
    void DO_YW00(int pos, ARGS... args)       { DO_BASE(pos, 30, args...); }
    void DO_YW06(int pos, ARGS... args)       { DO_BASE(pos, 24, args...); }
    
    void DO_ZW00(int pos, ARGS... args)       { DO_BASE(pos, 36, args...); }
    void DO_ZW18(int pos, ARGS... args)       { DO_BASE(pos, 18, args...); }
    
    void DO_XYZ00(int pos, ARGS... args)      { DO_BASE(pos, 13, args...); }
    void DO_XYZ02(int pos, ARGS... args)      { DO_BASE(pos, 11, args...); }
    void DO_XYZ06(int pos, ARGS... args)      { DO_BASE(pos, 7, args...); }
    void DO_XYZ08(int pos, ARGS... args)      { DO_BASE(pos, 5, args...); }
    
    void DO_XYW00(int pos, ARGS... args)      { DO_BASE(pos, 31, args...); }
    void DO_XYW02(int pos, ARGS... args)      { DO_BASE(pos, 29, args...); }
    void DO_XYW06(int pos, ARGS... args)      { DO_BASE(pos, 25, args...); }
    void DO_XYW08(int pos, ARGS... args)      { DO_BASE(pos, 23, args...); }
    
    void DO_XZW00(int pos, ARGS... args)      { DO_BASE(pos, 37, args...); }
    void DO_XZW02(int pos, ARGS... args)      { DO_BASE(pos, 35, args...); }
    void DO_XZW18(int pos, ARGS... args)      { DO_BASE(pos, 19, args...); }
    void DO_XZW20(int pos, ARGS... args)      { DO_BASE(pos, 17, args...); }
    
    void DO_YZW00(int pos, ARGS... args)      { DO_BASE(pos, 39, args...); }
    void DO_YZW06(int pos, ARGS... args)      { DO_BASE(pos, 33, args...); }
    void DO_YZW18(int pos, ARGS... args)      { DO_BASE(pos, 21, args...); }
    void DO_YZW24(int pos, ARGS... args)      { DO_BASE(pos, 15, args...); }
    
    void DO_XYZW00(int pos, ARGS... args)     { DO_BASE(pos, 40, args...); }
    void DO_XYZW02(int pos, ARGS... args)     { DO_BASE(pos, 38, args...); }
    void DO_XYZW06(int pos, ARGS... args)     { DO_BASE(pos, 34, args...); }
    void DO_XYZW08(int pos, ARGS... args)     { DO_BASE(pos, 32, args...); }
    
    void DO_XYZW18(int pos, ARGS... args)     { DO_BASE(pos, 22, args...); }
    void DO_XYZW20(int pos, ARGS... args)     { DO_BASE(pos, 20, args...); }
    void DO_XYZW24(int pos, ARGS... args)     { DO_BASE(pos, 16, args...); }
    void DO_XYZW26(int pos, ARGS... args)     { DO_BASE(pos, 14, args...); }
    
    
    void DO_1D(ARGS... args)
    {
        for (size_t i = 0; i < 27; i++)
        {            
            DO_X(i * 3, args...);
        }
        for (size_t j = 0; j < 9; j++)
            for (size_t i = 0; i < 3; i++)
            {    
                DO_Y(j * 9 + i, args...);
            }
        for (size_t j = 0; j < 3; j++)
            for (size_t i = 0; i < 9; i++)
            {
            
                DO_Z(j * 27 + i, args...);
            }
        for (size_t i = 0; i < 27; i++)
        {
        
            DO_W(i, args...);
        }
        
        
    }
    void DO_2D(ARGS... args)
    {
        
        for (size_t i = 0; i < 9; i++)
        {
        
            
            DO_XY00(i * 9, args...);
            DO_XY02(i * 9 + 2, args...);
            DO_ZW00(i * 1, args...);
            DO_ZW18(i * 1 + 18, args...);
            
        }
        
        for (size_t i = 0; i < 3; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
            
                DO_XZ00(i * 27 + j * 3, args...);
                DO_XZ02(i * 27 + j * 3 + 2, args...);
                
                DO_XW00(i * 9 + j * 3, args...);
                DO_XW02(i * 9 + j * 3 + 2, args...);
                
                DO_YZ00(i * 27 + j * 1, args...);
                DO_YZ06(i * 27 + j * 1 + 6, args...);
                
                DO_YW00(i * 9 + j * 1, args...);
                DO_YW06(i * 9 + j * 1 + 6, args...);
            }
        }
    }
    void DO_3D(ARGS... args)
    {
        for (size_t i = 0; i < 3; i++)
        {
        
            DO_XYZ00(i * 27 + 0, args...);
            DO_XYZ02(i * 27 + 2, args...);
            DO_XYZ06(i * 27 + 6, args...);
            DO_XYZ08(i * 27 + 8, args...);
            
            DO_XYW00(i * 9 + 0, args...);
            DO_XYW02(i * 9 + 2, args...);
            DO_XYW06(i * 9 + 6, args...);
            DO_XYW08(i * 9 + 8, args...);
            
            DO_XZW00(i * 3 + 0, args...);
            DO_XZW02(i * 3 + 2, args...);
            DO_XZW18(i * 3 + 18, args...);
            DO_XZW20(i * 3 + 20, args...);
            
            DO_YZW00(i * 1 + 0, args...);
            DO_YZW06(i * 1 + 6, args...);
            DO_YZW18(i * 1 + 18, args...);
            DO_YZW24(i * 1 + 24, args...);
            
        }
        
    }
    void DO_4D(ARGS... args)
    {
    
        DO_XYZW00(0, args...);
        DO_XYZW02(2, args...);
        DO_XYZW06(6, args...);
        DO_XYZW08(8, args...);
        
        DO_XYZW18(18, args...);
        DO_XYZW20(20, args...);
        DO_XYZW24(24, args...);
        DO_XYZW26(26, args...);
    }
    

    public:
    dofunction func;

    PROCESSOR() {}
    PROCESSOR(dofunction func) : func{func}
    {}

    void DO__ER(ARGS... args)
    {
        try
        {
            DO_1D(args...);
            DO_2D(args...);
            DO_3D(args...);
            DO_4D(args...);
        }
        catch(...) {}
    }
};
}



#endif  