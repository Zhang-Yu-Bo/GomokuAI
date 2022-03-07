#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <vector>
#include "../Common.h"

class Board {
public:
    Board() {
        
    }
    Board(int rows, int cols);
    ~Board();

    int Rows();
    int Cols();
    void PrintBoard();
    void SetBoardVal(Common::Pos pos, int val);
    int GetBoardVal(Common::Pos pos);
    std::vector<Common::Pos> GetValidSteps();
    int WhosTurn();
    Board* Clone();
    // deprecated
    int MaxStepNum();
    bool CheckWhoWins(int val);
    int CheckRightByPos(int val, Common::Pos pos);
    int CheckBottomByPos(int val, Common::Pos pos);
    int CheckBottomRightByPos(int val, Common::Pos pos);
    int CheckBottomLeftByPos(int val, Common::Pos pos);
private:
    int rowNum;
    int colNum;
    std::vector<int> boardVal;
};

#endif