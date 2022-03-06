#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "Player.h"
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

class Computer : public Player
{
public:
    Computer(int blackOrWhite);
    ~Computer();

    virtual Common::Pos RequestKeyDown(Board *board) override;

private:
    /**
     * @brief minimax alogrithm, reference: https://pastebin.com/rZg1Mz9G
     *
     * @param node game simulate state
     * @param depth iteration times
     * @param alpha -Infinity
     * @param beta +Infinity
     * @param maxOrMin max stage == 1, min stage == -1
     * @return int max score
     */
    int minimax(MinimaxNode *node, int depth, int alpha, int beta, int maxOrMin);
};

#endif