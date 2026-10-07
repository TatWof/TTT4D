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
            b[i] = 0;
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

                for (size_t j = 0; j < v.size(); j++)
                {
                    auto triple = v[j];
                    
                    for (size_t k = 0; k < 3; k++)
                    {
                        std::vector<int> t{triple[0], triple[1], triple[2]};
                        t.erase(t.begin() + k);
                        
                        if (i == triple[j])
                        {
                            culler(sign, i, t);
                        }
                    }
                }
            }
        }
        p = PLAY{-1,0};
    }

    void culler(int sign, int basepos, std::vector<int> postions)
    {
        if (board[postions[1]] == sign) 
        {
            p = PLAY{postions[2], sign};
            return;
        }
        if (board[postions[2]] == sign) 
        {
            p = PLAY{postions[1], sign};
            return;
        }
        
        switch (sign)
        {
            case 1: 
                cull1[postions[0]] = cull1[postions[1]] = true;
                evals[basepos] = ((playerturncheck(turn)) ? -1 : 1) * PUNISHMENT;
                break;
            case 2: 
                cull2[postions[0]] = cull2[postions[1]] = true;
                evals[basepos] = ((playerturncheck(turn)) ? -1 : 1) * PUNISHMENT;
                break;
            default: break;
        }
    }
};
    
}

#endif