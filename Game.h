//
// Created by alex on 4/12/16.
//

#ifndef LEGEND_OF_THE_SWAMP_GAME_H
#define LEGEND_OF_THE_SWAMP_GAME_H

#include <stack>
#include <memory>

#include <SFML/Graphics.hpp>

class GameState;

class Game
{
public:
    Game();

    std::stack<std::unique_ptr<GameState>> m_states;

    sf::RenderWindow m_window;

    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);
    GameState* peekState();

    void run();
};


#endif //LEGEND_OF_THE_SWAMP_GAME_H
