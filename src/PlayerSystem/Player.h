#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "../GameSystem/Board.h"
#include "../Common.h"
#include <cstdlib>
#include <ctime>

class Player
{
public:
    Player(int blackOrWhite);
    ~Player();

    virtual Common::Pos RequestKeyDown(Board *board);

protected:
    bool isAValidRequest(Board *board, Common::Pos pos);
    int self;
    int opponent;

};

#endif