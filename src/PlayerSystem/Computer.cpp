#include "Computer.h"

SimulateNode::SimulateNode(Board *board, int blackOrWhite)
{
    this->currentBoard = board;
    this->validStepList = std::vector<Common::Pos>();
    this->scoreList = std::vector<int>();
    this->blackOrWhite = blackOrWhite;
}

SimulateNode *SimulateNode::Clone()
{
    int val = this->blackOrWhite == Common::BLACK ? Common::WHITE : Common::BLACK;
    SimulateNode *copy = new SimulateNode(this->currentBoard->Clone(), val);
    return copy;
}

SimulateNode::~SimulateNode()
{
    this->currentBoard->~Board();
    delete this->currentBoard;
    this->validStepList.erase(this->validStepList.begin(), this->validStepList.end());
    this->scoreList.erase(this->scoreList.begin(), this->scoreList.end());
}

// Warning: it should call UpdateStepList before call this function
//          or that may be occour some error
bool SimulateNode::IsSimulateEnd()
{
    return this->currentBoard->CheckBoard(Common::BLACK) 
        || this->currentBoard->CheckBoard(Common::WHITE) 
        || this->validStepList.size() == 0;
}

int SimulateNode::UpdateStepList()
{
    for (int i = 0; i < this->currentBoard->Rows(); i++)
    {
        for (int j = 0; j < this->currentBoard->Cols(); j++)
        {
            Common::Pos pos(i, j);
            if (this->currentBoard->GetBoardVal(pos) == -1)
            {
                this->scoreList.push_back(0);
                this->validStepList.push_back(pos);
            }
        }
    }
    return this->validStepList.size();
}

void SimulateNode::Simulate(Common::Pos pos, int val)
{
    if (this->currentBoard->GetBoardVal(pos) != -1)
    {
        // Assert
        std::cout << "Error at void SimulateNode::Simulate(Common::Pos pos, int val)" << std::endl;
        return;
    }

    this->currentBoard->SetBoardVal(pos, val);
}

int SimulateNode::CurrentScore()
{
    // 2 4 8 16 +Infinity
    int score = 0;
    
    for (int i = 0; i < this->currentBoard->Rows(); i++)
    {
        for (int j = 0; j < this->currentBoard->Cols(); j++)
        {
            Common::Pos pos(i , j);
            if (this->currentBoard->GetBoardVal(pos) != this->blackOrWhite)
                continue;
            
            // right
            int rightScore = this->currentBoard->CheckRightByPos(this->blackOrWhite, pos);
            if (rightScore >= 5)
                return std::numeric_limits<int>::max();
            score += Common::WeightFunction(rightScore);

            // bottom
            int bottomScore = this->currentBoard->CheckBottomByPos(this->blackOrWhite, pos);
            if (bottomScore >= 5)
                return std::numeric_limits<int>::max();
            score += Common::WeightFunction(bottomScore);
            
            // bottom right
            int bottomRightScore = this->currentBoard->CheckBottomRightByPos(this->blackOrWhite, pos);
            if (bottomRightScore >= 5)
                return std::numeric_limits<int>::max();
            score += Common::WeightFunction(bottomRightScore);

            // bottom left
            int bottomLeftSocre = this->currentBoard->CheckBottomLeftByPos(this->blackOrWhite, pos);
            if (bottomLeftSocre >= 5)
                return std::numeric_limits<int>::max();
            score += Common::WeightFunction(bottomLeftSocre);
        }
    }
    return score;
}

Common::Pos SimulateNode::MaxScoreStep()
{
    if (this->scoreList.size() > 0 && this->scoreList.size() == this->validStepList.size())
    {
        int max = std::numeric_limits<int>::min();
        int index = 0;
        for (int i = 0; i < this->scoreList.size(); i++)
        {
            if (this->scoreList.at(i) > max)
            {
                max = this->scoreList.at(i);
                index = i;
            }
        }
        return this->validStepList.at(index);
    }
    // Assert
    std::cout << "Error at SimulateNode::MaxScoreStep()" << std::endl;
    return Common::Pos(0, 0);
}

void SimulateNode::SetScoreByIndex(int index, int val)
{
    this->scoreList.at(index) = val;
}

Common::Pos SimulateNode::GetValidStepByIndex(int index) {
    if (index >= this->validStepList.size()) {
        // Assert
        std::cout << "Error at SimulateNode::GetValidStepByIndex(int index)" << std::endl;
        return Common::Pos(0, 0);
    }

    return this->validStepList.at(index);
}

Computer::Computer(int blackOrWhite) : Player(blackOrWhite)
{
}

Computer::~Computer()
{
}

Common::Pos Computer::RequestKeyDown(Board *board)
{
    SimulateNode *rootNode = new SimulateNode(board, this->self);
    minimax(rootNode, 7, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 1);
    return rootNode->MaxScoreStep();
}

int Computer::minimax(SimulateNode *node, int depth, int alpha, int beta, int maxOrMin)
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
            SimulateNode *nextNode = node->Clone();
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
            SimulateNode *nextNode = node->Clone();
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