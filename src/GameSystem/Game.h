#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include "Board.h"
#include "../PlayerSystem/Human.h"
#include "../PlayerSystem/Computer.h"
#include "../Common.h"

class Game {
public:
    // constructor & destructor
    Game(int rows = 5, int cols = 5);
    ~Game();

    // member function
    // true -> black, false -> white
    void Start(bool isFirst = true);
    bool IsEnd();
    void Update();

private:
    /* data */
    bool isGameEnd;
    Board* mBoard;
    Player** mPlayers;
    int stepNum;

    // black = 0, white = 1
    void requestPlayer(int who);
};

#endif