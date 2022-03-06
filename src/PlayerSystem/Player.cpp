#include "Player.h"

Player::Player(int blackOrWhite)
{
    srand(time(NULL));
    this->self = blackOrWhite;
    this->opponent = blackOrWhite == Common::BLACK ? Common::WHITE : Common::BLACK;
}

Player::~Player()
{
}

Common::Pos Player::RequestKeyDown(Board *board)
{
    Common::Pos pos(0, 0);
    while (true) {
        pos.rowY = rand() % board->Rows();
        pos.colX = rand() % board->Cols();

        if (this->isAValidRequest(board, pos))
            return pos;
    }
}

bool Player::isAValidRequest(Board *board, Common::Pos pos)
{
    return board->GetBoardVal(pos) == -1;
}