#ifndef TTT4D_AGENT_H
#define TTT4D_AGENT_H

#include <vector>
#include <array>
#include <random>
#include "precompute.h"
#include "board.h"
#include "log.h"
#include "utility.h"

using TTT4D::BOARD;
using TTT4D::LOG::PLAY;
using TTT4D::UTILITY::playerturncheck;

namespace TTT4D
{
    #define PUNISHMENT 1

struct AGENT
{
    BOARD board;
    int turn;
    int alpha, beta;
    
    PLAY p{-1, 0};
    std::array<bool, 81> cull1, cull2;
    std::array<int, 162> evals{};

    AGENT(BOARD board, int turn) : AGENT(board, turn, -10000, +10000) {}
    
    
    AGENT(BOARD board, int turn, int alpha, int beta) 
        : board{board}, turn{turn}, alpha{alpha}, beta{beta} 
        { for (size_t i = 0; i < 81; i++) cull1[i] = cull2[i] = false; }

    int THINK()
    {
        int value{0};
        
        optimize(board);
        
        if (p.pos != -1)
        {
            (UTILITY::playerturncheck(turn)) ? value += 1 : value += -1;
            return value;
        }

        for (size_t i = 0; i < 81; i++)
        {
            BOARD b = board;
            if (!cull1[i])
            {
                b[i] = 1;
                AGENT a{b, turn + 1, alpha, beta};
                evals[i] = a.THINK();
                if (UTILITY::playerturncheck(turn))  
                    if (evals[i] >= beta) return evals[i]; else alpha = std::max(alpha, evals[i]);
                else 
                    if (evals[i] <= alpha) return evals[i]; else beta = std::min(beta, evals[i]);
            }
            if (!cull2[i])
            {
                b[i] = 2;
                AGENT a{b, turn + 1, alpha, beta};
                evals[i + 81] = a.THINK();
                if (UTILITY::playerturncheck(turn))  
                    if (evals[i] >= beta) return evals[i]; else alpha = std::max(alpha, evals[i]);
                else 
                    if (evals[i] <= alpha) return evals[i]; else beta = std::min(beta, evals[i]);
            }
        }
        
        int valsum{};
        int x;
        int extrema;
        
        for (size_t i = 0; i < evals.size(); i++)
        {
            if (UTILITY::playerturncheck(turn))
            {
                if (evals[i] > extrema) 
                {
                    extrema = evals[i]; x = i;
                }
            }
            else
            {
                if (evals[i] < extrema) 
                {
                    extrema = evals[i]; x = i;
                }
            }
            valsum += evals[i];
        }

        if (x < 81) p = PLAY{x, 1};
        else        p = PLAY{x - 81, 2};

        return valsum;
    }
    
    void optimize(BOARD& b)
    {
        std::vector<std::array<int, 3>> vec;
        PRECOMPUTE::trituple_extracter(vec);

        if(turn == 0) 
        {
            p = PLAY{0, ((rand() % 2) ? 1 : 2)};
        }

        for (size_t i = 0; i < 81; i++)
        {
            int sign = board[i];
            
            if (sign != 0)
            {
                if (cull1[i] || cull2[i]) continue;

                auto v = PRECOMPUTE::trituple_match(i, vec);

                for (size_t i = 0; i < v.size(); i++)
                {
                    auto triple = v[i];
                    
                    if (i == triple[0])
                    {
                        if (board[triple[1]] == sign) p = PLAY{triple[2], sign};
                        if (board[triple[2]] == sign) p = PLAY{triple[1], sign};
                        if (board[triple[1]] == 0 && board[triple[2]] == 0)
                        switch (sign)
                        {
                        case 1: 
                            cull1[triple[1]] = cull1[triple[2]] = true;
                            evals[triple[0]] = ((playerturncheck(turn)) ? -1 : 1) * PUNISHMENT; 
                            break;
                        case 2: 
                            cull2[triple[1]] = cull2[triple[2]] = true;
                            evals[triple[0] + 81] = ((playerturncheck(turn)) ? -1 : 1) * PUNISHMENT; 
                            break;
                        default: break;
                        }
                        
                    }
                    else if(i == triple[1])
                    {
                        if (board[triple[0]] == sign) p = PLAY{triple[2], sign};
                        if (board[triple[2]] == sign) p = PLAY{triple[0], sign};
                        if (board[triple[0]] == 0 && board[triple[2]] == 0)
                        switch (sign)
                        {
                        case 1: 
                            cull1[triple[0]] = cull1[triple[2]] = true;
                            evals[triple[1]] = ((playerturncheck(turn)) ? -1 : 1) * PUNISHMENT; 
                            break;
                        case 2: 
                            cull2[triple[0]] = cull2[triple[2]] = true;
                            evals[triple[1] + 81] = ((playerturncheck(turn)) ? -1 : 1) * PUNISHMENT; 
                            break;
                        default: break;
                        }
                    }
                    else if (i == triple[2])
                    {
                        if (board[triple[0]] == sign) p = PLAY{triple[1], sign};
                        if (board[triple[1]] == sign) p = PLAY{triple[0], sign};
                        if (board[triple[0]] == 0 && board[triple[1]] == 0)
                        switch (sign)
                        {
                        case 1: 
                            cull1[triple[0]] = cull1[triple[1]] = true;
                            evals[triple[2]] = ((playerturncheck(turn)) ? -1 : 1) * PUNISHMENT; 
                            break;
                        case 2: 
                            cull2[triple[0]] = cull2[triple[1]] = true;
                            evals[triple[2] + 81] = ((playerturncheck(turn)) ? -1 : 1) * PUNISHMENT;
                            break;
                        default: break;
                        }
                    }
                }
            }
        }
        p = PLAY{-1,0};
    }
};
    
}

#endif