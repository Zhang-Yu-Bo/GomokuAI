#include "Computer.h"

Computer::Computer(int blackOrWhite) : Player(blackOrWhite)
{
}

Computer::~Computer()
{
}

Common::Pos Computer::RequestKeyDown(Board *board)
{
    Common::Pos response(0, 0);

    // MinimaxNode *rootNode = new MinimaxNode(board, this->self);
    // minimax(rootNode, 7, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 1);
    // response = rootNode->MaxScoreStep();

    MonteCarloGameState rootState = MonteCarloGameState(board, this->self);
    MonteCarloNode *rootNode = new MonteCarloNode(rootState);
    MonteCarloNode *best = monteCarloTreeSearch(rootNode, 5000);
    response = best->currentState.actionHistory.at(0);

    return response;
}