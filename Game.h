//
// Created by alex on 4/12/16.
//

#ifndef LEGEND_OF_THE_SWAMP_GAME_H
#define LEGEND_OF_THE_SWAMP_GAME_H

#include <stack>
#include <memory>

#include <SFML/Graphics.hpp>

class GameState;

class Game {
public:
    std::stack<std::unique_ptr<GameState>> m_states;

    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);
    GameState* peekState();
};


#endif //LEGEND_OF_THE_SWAMP_GAME_H
