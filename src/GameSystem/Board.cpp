#include "Board.h"

Board::Board(int rows, int cols)
{
    this->rowNum = rows;
    this->colNum = cols;

    this->boardVal = std::vector<int>(rows * cols, -1);

    // this->boardVal = new int [rows * cols] {
    //     0, 0, 1, 1, 0,
    //     1, 1, 0, 0, 1,
    //     0, 0, 1, 1, 0,
    //     1, 1, 0, 0, 1,
    //     0, 0, 1, 1, 0
    // };
}

Board::~Board()
{
    // this->boardVal.erase(this->boardVal.begin(), this->boardVal.end());
    // std::cout << "Yes\n";
}

int Board::Rows()
{
    return this->rowNum;
}

int Board::Cols()
{
    return this->colNum;
}

void Board::PrintBoard()
{
    system("cls");
    for (int i = 0; i < this->rowNum; i++)
    {
        for (int j = 0; j < this->colNum; j++)
        {
            if (this->boardVal[i * this->colNum + j] == Common::BLACK)
                std::cout << "X";
            else if (this->boardVal[i * this->colNum + j] == Common::WHITE)
                std::cout << "O";
            else
                std::cout << ".";
        }
        std::cout << std::endl;
    }
}

void Board::SetBoardVal(Common::Pos pos, int val)
{
    pos.rowY = Common::Clamp(pos.rowY, 0, this->rowNum - 1);
    pos.colX = Common::Clamp(pos.colX, 0, this->colNum - 1);
    val = Common::Clamp(val, Common::BLACK, Common::WHITE);
    this->boardVal[pos.rowY * this->colNum + pos.colX] = val;
}

int Board::GetBoardVal(Common::Pos pos)
{
    pos.rowY = Common::Clamp(pos.rowY, 0, this->rowNum - 1);
    pos.colX = Common::Clamp(pos.colX, 0, this->colNum - 1);
    return this->boardVal[pos.rowY * this->colNum + pos.colX];
}

std::vector<Common::Pos> Board::GetValidSteps() 
{
    std::vector<Common::Pos> list = std::vector<Common::Pos>();
    for (int i = 0; i < this->rowNum; i++) {
        for (int j = 0; j < this->colNum; j++) {
            int val = this->boardVal[i * this->colNum + j];
            if (val != Common::BLACK && val != Common::WHITE)
                list.push_back(Common::Pos(i, j));
        }
    }
    return list;
}

int Board::WhosTurn() {
    int numOfBlack = 0;
    int numOfWhite = 0;

    for (int i = 0; i < this->rowNum; i++) {
        for (int j = 0; j < this->colNum; j++) {
            if (this->boardVal[i * this->colNum + j] == Common::BLACK)
                numOfBlack++;
            if (this->boardVal[i * this->colNum + j] == Common::WHITE)
                numOfWhite++;
        }
    }
    return numOfBlack == numOfWhite ? Common::BLACK : Common::WHITE;
}

Board *Board::Clone()
{
    Board *copy = new Board(this->rowNum, this->colNum);
    copy->boardVal = this->boardVal;
    // Common::CopyArray(this->boardVal, copy->boardVal, this->rowNum * this->colNum);
    return copy;
}

int Board::MaxStepNum()
{
    return this->rowNum * this->colNum;
}

bool Board::CheckWhoWins(int val)
{
    val = Common::Clamp(val, Common::BLACK, Common::WHITE);

    for (int i = 0; i < this->rowNum; i++)
    {
        for (int j = 0; j < this->colNum; j++)
        {
            Common::Pos pos(i, j);
            if (this->GetBoardVal(pos) != val)
                continue;
            if (this->CheckRightByPos(val, pos) >= 5)
                return true;
            if (this->CheckBottomByPos(val, pos) >= 5)
                return true;
            if (this->CheckBottomRightByPos(val, pos) >= 5)
                return true;
            if (this->CheckBottomLeftByPos(val, pos) >= 5) 
                return true;
        }
    }

    return false;
}

int Board::CheckRightByPos(int val, Common::Pos pos)
{
    if (pos.colX + 4 >= this->colNum)
        return 0;
    int counter = 0;
    for (int i = 0; i < 5; i++)
    {
        if (this->GetBoardVal(pos) != val)
            return counter;
        counter++;
        pos.colX++;
    }
    return counter;
}

int Board::CheckBottomByPos(int val, Common::Pos pos)
{
    if (pos.rowY + 4 >= this->rowNum)
        return 0;
    int counter = 0;
    for (int i = 0; i < 5; i++)
    {
        if (this->GetBoardVal(pos) != val)
            return counter;
        counter++;
        pos.rowY++;
    }
    return counter;
}

int Board::CheckBottomRightByPos(int val, Common::Pos pos)
{
    if (pos.colX + 4 >= this->colNum || pos.rowY + 4 >= this->rowNum)
        return 0;
    int counter = 0;
    for (int i = 0; i < 5; i++)
    {
        if (this->GetBoardVal(pos) != val)
            return counter;
        counter++;
        pos.rowY++;
        pos.colX++;
    }
    return counter;
}

int Board::CheckBottomLeftByPos(int val, Common::Pos pos) {
    if (pos.colX - 4 < 0 || pos.rowY + 4 >= this->rowNum)
        return 0;
    int counter = 0;
    for (int i = 0; i < 5; i++)
    {
        if (this->GetBoardVal(pos) != val)
            return counter;
        counter++;
        pos.rowY++;
        pos.colX--;
    }
    return counter;
}