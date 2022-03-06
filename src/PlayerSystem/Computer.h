#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "Player.h"
#include "Minimax.h"

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