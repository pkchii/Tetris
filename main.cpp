
#include "game.h"

int main(int argc, char** argv)
{
    Game* game = new Game;
    if (game->gameInitialize()) {
        while (game->currentState != exit_game) {
            game->run();
        }
    }
    game->exit();
    return 0;
}