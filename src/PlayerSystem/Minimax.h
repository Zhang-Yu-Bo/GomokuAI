#ifndef _MINIMAX_H_
#define _MINIMAX_H_

#include "../Common.h"
#include "../GameSystem/Board.h"
#include <vector>
#include <limits>

class MinimaxNode
{
public:
    MinimaxNode(Board *board, int blackOrWhite);
    MinimaxNode* Clone();
    ~MinimaxNode();

    bool IsSimulateEnd();
    int UpdateStepList();
    void Simulate(Common::Pos pos, int val);
    int CurrentScore();
    Common::Pos MaxScoreStep();
    void SetScoreByIndex(int index, int val);
    Common::Pos GetValidStepByIndex(int index);

private:
    Board *currentBoard;
    std::vector<Common::Pos> validStepList;
    std::vector<int> scoreList;
    int blackOrWhite;
};

#endif