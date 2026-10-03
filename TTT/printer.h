#ifndef PRINTER_H
#define PRINTER_H

#include <sstream>
#include <iomanip>
#include "board.h"

using TTT4D::BOARD;

namespace TTT4D::PRINTER
{

    enum class PRINTMODE
    {
        DEBUGMODE,
        XYMODE,
        XZMODE,
        XWMODE,
        YZMODE,
        YWMODE,
        ZWMODE
    };

    std::string verticaldiv()
    {
        return " ----------------     ----------------     ----------------";
    }
    
    std::stringstream print_board_splice(BOARD& board, PRINTMODE mode)
    {
        std::stringstream ss;
        int pos;
        for (size_t a = 0; a < 3; a++)
        {
            ss << std::endl << verticaldiv() << std::endl;
            for (size_t b = 0; b < 3; b++)
            {
                for (size_t c = 0; c < 3; c++)
                {
                    ss << " | ";
                    
                    for (size_t d = 0; d < 3; d++)
                    {
                        switch (mode)
                        {
                        case PRINTMODE::XYMODE: pos = UTILITY::coord_to_pos(d,b,c,a); break;

                        case PRINTMODE::XZMODE: pos = UTILITY::coord_to_pos(d,c,b,a); break;

                        case PRINTMODE::XWMODE: pos = UTILITY::coord_to_pos(d,a,c,b); break;

                        case PRINTMODE::YZMODE: pos = UTILITY::coord_to_pos(c,b,d,a); break;

                        case PRINTMODE::YWMODE: pos = UTILITY::coord_to_pos(c,d,a,b); break;

                        case PRINTMODE::ZWMODE: pos = UTILITY::coord_to_pos(c,a,d,b); break;

                        case PRINTMODE::DEBUGMODE: pos = UTILITY::coord_to_pos(d,c,b,a); break;
                        
                        default: pos = UTILITY::coord_to_pos(d,b,c,a); break;
                        }
                        
                        ss << std::setw(2) << board[pos] << " | ";
                    }
                    ss << "   ";
                }
                ss << std::endl << verticaldiv() << std::endl;
            }
        }
        return ss;
    }


    std::stringstream print_boardXY(BOARD& b)
    {
        return print_board_splice(b, PRINTMODE::XYMODE);
    }

    std::stringstream print_boardZW(BOARD& b)
    {
        return print_board_splice(b, PRINTMODE::ZWMODE);
    }
};


#endif