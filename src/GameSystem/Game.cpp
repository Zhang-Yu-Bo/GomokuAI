#include "Game.h"

Game::Game(int rows, int cols)
{
    this->isGameEnd = false;
    this->mBoard = new Board(rows, cols);
    this->mPlayers = new Player *[2];
    this->stepNum = 0;
}

Game::~Game()
{
    this->mBoard->~Board();
    this->mPlayers[0]->~Player();
    this->mPlayers[1]->~Player();
    delete[] this->mPlayers;
}

void Game::Start(bool isFirst)
{
    this->mPlayers[Common::BLACK] = isFirst ? (Player*)(new Human(Common::BLACK)) : (Player*)(new Computer(Common::BLACK));
    this->mPlayers[Common::WHITE] = isFirst ? (Player*)(new Computer(Common::WHITE)) : (Player*)(new Human(Common::WHITE));
    // this->mPlayers[Common::BLACK] = new Computer(Common::BLACK);
    // this->mPlayers[Common::WHITE] = new Computer(Common::WHITE);
    this->stepNum = 0;
    this->isGameEnd = false;

    this->mBoard->PrintBoard();
}

bool Game::IsEnd()
{
    if (this->isGameEnd)
        return true;
    
    // check black
    this->isGameEnd = this->mBoard->CheckWhoWins(Common::BLACK);
    if (this->isGameEnd) {
        std::cout << "Black Wins."  << std::endl;
        return true;
    }

    // check white
    this->isGameEnd = this->mBoard->CheckWhoWins(Common::WHITE);
    if (this->isGameEnd) {
        std::cout << "White Wins."  << std::endl;
        return true;
    }

    // check tie
    this->isGameEnd = this->stepNum >= this->mBoard->MaxStepNum();
    if (this->isGameEnd) {
        std::cout << "Tie."  << std::endl;
        return true;
    }

    return false;
}

void Game::Update()
{
    this->requestPlayer(Common::BLACK);
    if (this->IsEnd())
        return;
    
    this->requestPlayer(Common::WHITE);
}

void Game::requestPlayer(int who)
{
    Common::Pos pos = this->mPlayers[who]->RequestKeyDown(this->mBoard->Clone());
    this->stepNum++;
    this->mBoard->SetBoardVal(pos, who);
    this->mBoard->PrintBoard();
    std::cout << "Step number: " << this->stepNum << std::endl;
}
