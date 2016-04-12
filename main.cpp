//
// Created by alex on 4/12/16.
//
#include <iostream>

#include "Game.h"
#include "GameState.h"

constexpr unsigned int winWidth{800}, winHeight{600};

int main()
{
    std::cout << "Hello World" << std::endl;

    Game game;

    sf::Clock clock;

    sf::RenderWindow window{{winWidth, winHeight}, "Legend"};
    window.setFramerateLimit(60);

    while(window.isOpen())
    {
        sf::Time elapsed{clock.restart()};
        float dt{elapsed.asSeconds()};

        if(game.peekState())
        {
            continue;
        }

        game.peekState()->handleInput();
        game.peekState()->update(dt);

        window.clear(sf::Color::Black);

        game.peekState()->draw(dt);

        window.display();
    }

    return 0;
}