#include "Computer.h"

Computer::Computer(int blackOrWhite) : Player(blackOrWhite)
{
}

Computer::~Computer()
{
}

Common::Pos Computer::RequestKeyDown(Board *board)
{
    MinimaxNode *rootNode = new MinimaxNode(board, this->self);
    minimax(rootNode, 7, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 1);
    return rootNode->MaxScoreStep();
}

int Computer::minimax(MinimaxNode *node, int depth, int alpha, int beta, int maxOrMin)
{

    int stepListLength = node->UpdateStepList();
    if (depth == 0 || node->IsSimulateEnd())
    {
        return maxOrMin * node->CurrentScore();
    }

    if (maxOrMin == 1)
    {
        int maxScore = std::numeric_limits<int>::min();
        for (int i = 0; i < stepListLength; i++)
        {
            MinimaxNode *nextNode = node->Clone();
            nextNode->Simulate(node->GetValidStepByIndex(i), this->self);
            int score = minimax(nextNode, depth - 1, alpha, beta, -1);

            node->SetScoreByIndex(i, score);
            maxScore = score > maxScore ? score : maxScore;
            alpha = score > alpha ? score : alpha;

            if (beta <= alpha)
                break;
        }
        return maxScore;
    }
    else
    {
        int minScore = std::numeric_limits<int>::max();
        for (int i = 0; i < stepListLength; i++)
        {
            MinimaxNode *nextNode = node->Clone();
            nextNode->Simulate(node->GetValidStepByIndex(i), this->opponent);
            int score = minimax(nextNode, depth - 1, alpha, beta, 1);
            minScore = score < minScore ? score : minScore;
            beta = score < beta ? score : beta;

            if (beta <= alpha)
                break;
        }
        return minScore;
    }
}