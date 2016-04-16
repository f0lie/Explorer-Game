#include <iostream>

#include "Game.h"
#include "GameStateStart.h"

/*
 * Mainly following this guide
 * https://www.binpress.com/tutorial/creating-a-city-building-game-with-sfml/137
 */
int main()
{
    std::cout << "Hello World" << std::endl;

    Game game{};

    game.pushState(std::make_unique<GameStateStart>(&game));
    game.run();

    return 0;
}