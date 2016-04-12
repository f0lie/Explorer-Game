//
// Created by alex on 4/12/16.
//
#include <iostream>

#include "Game.h"
#include "GameState.h"

// Mainly following this guide
// https://www.binpress.com/tutorial/creating-a-city-building-game-with-sfml/137
int main()
{
    std::cout << "Hello World" << std::endl;

    Game game{};
    game.run();

    return 0;
}