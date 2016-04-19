#include <SFML/Graphics.hpp>
#include <memory>

#include "include/Game.h"
#include "include/GameStateStart.h"

int main()
{
    Game game;

    game.pushState(std::make_unique<GameStateStart>(&game));
    game.run();

    return 0;
}
