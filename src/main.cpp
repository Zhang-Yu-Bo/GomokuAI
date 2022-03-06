#include "./GameSystem/Game.h"

int main() {

    Game* game = new Game();
    game->Start();

    while(!game->IsEnd()) {
        game->Update();
    }
    std::cout << "Game Over" << std::endl;

    game->~Game();
    return 0;
}