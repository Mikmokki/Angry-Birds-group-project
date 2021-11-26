#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "game.hpp"

int main()
{
    Game game = Game();
    game.LoadLevel("");
    game.Start();

    return 0;
}