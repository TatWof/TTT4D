#ifndef TTT_CHECKER_H
#define TTT_CHECKER_H

#include <array>
#include "board.h"
#include "TTT_processor.h"

using TTT4D::BOARD;

using TTT4D::PROCESSOR;

void checkfunc(bool& kill, int pos, int coef, BOARD& board, bool& win)
{
    std::array<int, 3> c;
    for (int i = 0; i < 3; i++) { c[i] = board[pos + i * coef]; }

    kill = win = (c[0] == 0 || c[1] == 0 || c[2] == 0) ? false : (c[0] == c[1] && c[0] == c[2]);

    return;
}

bool CHECK(BOARD& board)
{
    PROCESSOR<BOARD&, bool&> procker{checkfunc};
    bool temp{false};

    procker.DO__ER(board, temp);
    return temp;
}

#endif