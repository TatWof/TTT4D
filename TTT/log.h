#ifndef TTT4D_LOG_H
#define TTT4D_LOG_H

#include <vector>

namespace TTT4D::LOG
{

struct PLAY
{
    int pos;
    int sign;
};

struct PLAYLOG
{
    std::vector<PLAY> log;

    PLAY& operator[](int i)
    {
        return log[i];
    }
};

}
#endif