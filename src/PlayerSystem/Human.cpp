#include "Human.h"

Human::Human(int blackOrWhite) : Player(blackOrWhite)
{
}

Human::~Human()
{
}

Common::Pos Human::RequestKeyDown(Board *board)
{
    Common::Pos pos(0, 0);
    while (true)
    {
        std::cout << "=================" << std::endl;
        std::cout << "Please input the position(row, col): ";
        std::cin >> pos.rowY >> pos.colX;

        if (this->isAValidRequest(board, pos))
            return pos;

        std::cout << "(" << pos.rowY << ", " << pos.colX << ") is not valid." << std::endl;
    }
}