#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "Player.h"
#include <iostream>

class Human : public Player
{
public:
    Human(int blackOrWhite);
    ~Human();

    virtual Common::Pos RequestKeyDown(Board *board) override;

private:
};

#endif