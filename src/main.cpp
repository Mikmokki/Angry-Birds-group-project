
#include "game.hpp"

int main()
{

    Game game = Game();
    game.LoadLevel("../resources/levels/level1.ab");
    game.Start();

    return 0;
}