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

    sf::Clock clock;

    while(game.m_window.isOpen())
    {
        sf::Time elapsed{clock.restart()};
        float dt{elapsed.asSeconds()};

        if(game.peekState())
        {
            continue;
        }

        game.peekState()->handleInput();
        game.peekState()->update(dt);

        game.m_window.clear(sf::Color::Black);

        game.peekState()->draw(dt);

        game.m_window.display();
    }

    return 0;
}