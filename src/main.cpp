#include <SFML/Graphics.hpp>
#include <memory>

#include "include/Game.h"
#include "include/GameStateStart.h"

/*
 * Mainly following this guide
 * https://www.binpress.com/tutorial/creating-a-city-building-game-with-sfml/137
 */
int main()
{
    Game game;

    game.pushState(std::make_unique<GameStateStart>(&game));
    game.run();

    return 0;
}
