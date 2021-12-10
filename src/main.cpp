
#include "game.hpp"

int main()
{
    utils::PathPrefix();
    Game game;
    game.LoadIcon();
    game.LoadLevel("resources/levels/level1.ab");
    game.Start();

    return 0;
}