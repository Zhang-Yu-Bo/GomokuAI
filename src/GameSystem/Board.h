#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include "../Common.h"

class Board {
public:
    Board(int rows, int cols);
    ~Board();

    int Rows();
    int Cols();
    void PrintBoard();
    void SetBoardVal(Common::Pos pos, int val);
    int GetBoardVal(Common::Pos pos);
    Board* Clone();
    int MaxStepNum();
    bool CheckBoard(int val);
    int CheckRightByPos(int val, Common::Pos pos);
    int CheckBottomByPos(int val, Common::Pos pos);
    int CheckBottomRightByPos(int val, Common::Pos pos);
    int CheckBottomLeftByPos(int val, Common::Pos pos);
private:
    int rowNum;
    int colNum;
    int* boardVal;
};

#endif