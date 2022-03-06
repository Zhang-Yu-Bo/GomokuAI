#include "Minimax.h"

MinimaxNode::MinimaxNode(Board *board, int blackOrWhite)
{
    this->currentBoard = board;
    this->validStepList = std::vector<Common::Pos>();
    this->scoreList = std::vector<int>();
    this->blackOrWhite = blackOrWhite;
}

MinimaxNode *MinimaxNode::Clone()
{
    int val = this->blackOrWhite == Common::BLACK ? Common::WHITE : Common::BLACK;
    MinimaxNode *copy = new MinimaxNode(this->currentBoard->Clone(), val);
    return copy;
}

MinimaxNode::~MinimaxNode()
{
    this->currentBoard->~Board();
    delete this->currentBoard;
    this->validStepList.erase(this->validStepList.begin(), this->validStepList.end());
    this->scoreList.erase(this->scoreList.begin(), this->scoreList.end());
}

// Warning: it should call UpdateStepList before call this function
//          or that may be occour some error
bool MinimaxNode::IsSimulateEnd()
{
    return this->currentBoard->CheckBoard(Common::BLACK) 
        || this->currentBoard->CheckBoard(Common::WHITE) 
        || this->validStepList.size() == 0;
}

int MinimaxNode::UpdateStepList()
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

void MinimaxNode::Simulate(Common::Pos pos, int val)
{
    if (this->currentBoard->GetBoardVal(pos) != -1)
    {
        // Assert
        std::cout << "Error at void MinimaxNode::Simulate(Common::Pos pos, int val)" << std::endl;
        return;
    }

    this->currentBoard->SetBoardVal(pos, val);
}

int MinimaxNode::CurrentScore()
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

Common::Pos MinimaxNode::MaxScoreStep()
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
    std::cout << "Error at MinimaxNode::MaxScoreStep()" << std::endl;
    return Common::Pos(0, 0);
}

void MinimaxNode::SetScoreByIndex(int index, int val)
{
    this->scoreList.at(index) = val;
}

Common::Pos MinimaxNode::GetValidStepByIndex(int index) {
    if (index >= this->validStepList.size()) {
        // Assert
        std::cout << "Error at MinimaxNode::GetValidStepByIndex(int index)" << std::endl;
        return Common::Pos(0, 0);
    }

    return this->validStepList.at(index);
}