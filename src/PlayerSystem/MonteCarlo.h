#ifndef _MONTE_CARLO_H_
#define _MONTE_CARLO_H_

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "../GameSystem/Board.h"

class MonteCarloGameState
{
public:
    MonteCarloGameState() {

    }
    MonteCarloGameState(Board *board, int blackOrWhite);
    ~MonteCarloGameState();

    bool IsTermination();
    void RandomRollout();
    int Evaluate();
    void TakeAction(Common::Pos pos);
    MonteCarloGameState Clone();

    int blackOrWhite;
    Board currentBoard;
    std::vector<Common::Pos> actionHistory;

};

class MonteCarloNode
{
public:
    MonteCarloNode(MonteCarloGameState state);
    ~MonteCarloNode();

    bool IsFullyExpanded();
    void AddChild(MonteCarloNode *node);

    MonteCarloNode *parent;
    std::vector<MonteCarloNode *> children;
    int numOfVisit;
    int numOfWins;
    
    MonteCarloGameState currentState;

private:
};

MonteCarloNode *Selection(MonteCarloNode *node);
MonteCarloNode *Expansion(MonteCarloNode *node);
int Simulation(MonteCarloNode *node);
void Backpropagate(MonteCarloNode *node, int numOfWins);
MonteCarloNode *BestChild(MonteCarloNode *node, bool isExploration);

#endif