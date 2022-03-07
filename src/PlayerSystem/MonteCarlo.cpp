#include "MonteCarlo.h"
#include "Computer.h"

MonteCarloNode::MonteCarloNode(MonteCarloGameState state)
{
    this->parent = NULL;
    this->children = std::vector<MonteCarloNode *>();
    this->numOfVisit = 0;
    this->numOfWins = 0;
    this->currentState = state;
}

MonteCarloNode::~MonteCarloNode()
{
    // this->currentState.~MonteCarloGameState();
    // this->children.erase(this->children.begin(), this->children.end());
}

bool MonteCarloNode::IsFullyExpanded()
{
    int numOfChildren = this->children.size();
    int numOfActions = this->currentState.currentBoard.GetValidSteps().size();

    if (numOfChildren > numOfActions) {
        // Assert
        std::cout << "Error at bool MonteCarloNode::IsFullyExpanded(), numOfChildren = " 
        << numOfChildren << ", numOfActions = " << numOfActions << std::endl;
    }

    return numOfChildren == numOfActions;
}

void MonteCarloNode::AddChild(MonteCarloNode *node)
{
    node->parent = this;
    this->children.push_back(node);
}

MonteCarloGameState::MonteCarloGameState(Board *board, int blackOrWhite)
{
    this->currentBoard = *board;
    this->blackOrWhite = blackOrWhite;
    this->actionHistory = std::vector<Common::Pos>();
}

MonteCarloGameState::~MonteCarloGameState()
{
    // this->currentBoard.~Board();
    // this->actionHistory.erase(this->actionHistory.begin(), this->actionHistory.end());
}

bool MonteCarloGameState::IsTermination()
{
    return this->currentBoard.CheckWhoWins(Common::BLACK) 
        || this->currentBoard.CheckWhoWins(Common::WHITE) 
        || this->currentBoard.GetValidSteps().size() == 0;
}

void MonteCarloGameState::RandomRollout()
{
    std::vector<Common::Pos> actionList = this->currentBoard.GetValidSteps();
    int numOfActions = actionList.size();
    Common::Pos actino = actionList.at(rand() % numOfActions);
    this->TakeAction(actino);
}

int MonteCarloGameState::Evaluate() {
    // 2 4 8 16 +Infinity
    int score = 0;
    int opponent = this->blackOrWhite == Common::BLACK ? Common::WHITE : Common::BLACK;
    
    for (int i = 0; i < this->currentBoard.Rows(); i++)
    {
        for (int j = 0; j < this->currentBoard.Cols(); j++)
        {
            Common::Pos pos(i , j);
            if (this->currentBoard.GetBoardVal(pos) != this->blackOrWhite)
                continue;
            
            // right
            int positive = this->currentBoard.CheckRightByPos(this->blackOrWhite, pos);
            int negitive = this->currentBoard.CheckRightByPos(opponent, pos);
            score += Common::WeightFunction(positive) - Common::WeightFunction(negitive);

            // bottom
            positive = this->currentBoard.CheckBottomByPos(this->blackOrWhite, pos);
            negitive = this->currentBoard.CheckBottomByPos(opponent, pos);
            score += Common::WeightFunction(positive) - Common::WeightFunction(negitive);
            
            // bottom right
            positive = this->currentBoard.CheckBottomRightByPos(this->blackOrWhite, pos);
            negitive = this->currentBoard.CheckBottomRightByPos(opponent, pos);
            score += Common::WeightFunction(positive) - Common::WeightFunction(negitive);

            // bottom left
            positive = this->currentBoard.CheckBottomLeftByPos(this->blackOrWhite, pos);
            negitive = this->currentBoard.CheckBottomLeftByPos(opponent, pos);
            score += Common::WeightFunction(positive) - Common::WeightFunction(negitive);
        }
    }
    return score;
    // if (this->currentBoard.CheckWhoWins(this->blackOrWhite))
    //     return 100;
    // else if (this->currentBoard.CheckWhoWins(opponent))
    //     return -100;
    // return 0;
}

void MonteCarloGameState::TakeAction(Common::Pos pos) {
    int val = this->currentBoard.WhosTurn();
    this->currentBoard.SetBoardVal(pos, val);
    this->actionHistory.push_back(pos);
}

MonteCarloGameState MonteCarloGameState::Clone()
{
    return MonteCarloGameState(this->currentBoard.Clone(), this->blackOrWhite);
}

MonteCarloNode *Selection(MonteCarloNode *node)
{
    while (!node->currentState.IsTermination())
    {
        if (node->IsFullyExpanded())
            node = BestChild(node, true);
        else
            return Expansion(node);
    }
    return node;
}

int Simulation(MonteCarloNode *node)
{
    MonteCarloGameState state = node->currentState.Clone();
    while (!state.IsTermination())
    {
        state.RandomRollout();
    }
    return state.Evaluate();
}

MonteCarloNode *Expansion(MonteCarloNode *node)
{
    int numOfChildren = node->children.size();
    std::vector<Common::Pos> actionList = node->currentState.currentBoard.GetValidSteps();
    int numOfActions = actionList.size();

    if (numOfChildren >= numOfActions) {
        // Assert
        std::cout << "Error at MonteCarloNode *&Expansion(MonteCarloNode *node), numOfChildren = " 
        << numOfChildren << ", numOfActions = " << numOfActions << std::endl;

        node->currentState.currentBoard.PrintBoard();
        std::cout << "11111111111111\n";
        for (int i = 0; i < node->currentState.currentBoard.Rows();i++){
            for (int j = 0; j < node->currentState.currentBoard.Cols(); j++) {
                std::cout << node->currentState.currentBoard.GetBoardVal(Common::Pos(i, j)) << ", ";
            }
            std::cout << "\n";
        }
    }

    MonteCarloNode *newChild = new MonteCarloNode(node->currentState.Clone());
    newChild->currentState.TakeAction(actionList.at(numOfChildren));
    node->AddChild(newChild);

    return newChild;
}

MonteCarloNode *BestChild(MonteCarloNode *node, bool isExploration)
{
    float bestUCB = std::numeric_limits<float>::min();
    MonteCarloNode *bestNode = NULL;
    float C = isExploration ? 1 / sqrtf(2.0f) : 0.0f;

    int numOfChildren = node->children.size();
    for (int i = 0; i < numOfChildren; i++) {
        MonteCarloNode* child = node->children.at(i);

        float average = (float)child->numOfWins / (float)child->numOfVisit;
        float rightTerm = 2.0f * logf(node->numOfVisit) / (float)child->numOfVisit;
        float UCB = average + C * sqrtf(rightTerm);

        if (UCB > bestUCB) {
            bestUCB = UCB;
            bestNode = child;
        }
    }

    if (bestNode == NULL) {
        std::cout << "Error at MonteCarloNode *&BestChild(MonteCarloNode *node, bool isExploration), " 
        << "There is no best node." << std::endl;
        // bestNode = node->children.at(node->children.size() - 1);
    }

    return bestNode;
}

void Backpropagate(MonteCarloNode *node, int numOfWins)
{
    while (node != NULL)
    {
        node->numOfVisit++;
        node->numOfWins += numOfWins;
        node = node->parent;
    }
}

MonteCarloNode *Computer::monteCarloTreeSearch(MonteCarloNode *&rootNode, int computationBudget)
{
    srand(time(NULL));
    std::cout << "<<<<<<<<<<<\b\b\b\b\b\b\b\b\b\b\b";
    int tenPercent = computationBudget / 10;
    for (int i = 0; i < computationBudget; i++)
    {
        MonteCarloNode *expandNode = Selection(rootNode);
        int numOfWins = Simulation(expandNode);
        Backpropagate(expandNode, numOfWins);

        if (i % tenPercent == 0) {
            std::cout << " ";
        }
    }
    return BestChild(rootNode, true);
}