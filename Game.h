//
// Created by alex on 4/12/16.
//

#ifndef LEGEND_OF_THE_SWAMP_GAME_H
#define LEGEND_OF_THE_SWAMP_GAME_H

#include <SFML/Graphics.hpp>

#include <stack>
#include <memory>

#include "TextureManager.h"

class GameState;

class Game
{
public:
    Game();

    std::stack<std::unique_ptr<GameState>> m_states;

    sf::RenderWindow m_window;
    TextureManager m_texmgr;
    sf::Sprite m_background;

    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);
    GameState* peekState();

    void run();
private:
    void loadTextures();
};


#endif //LEGEND_OF_THE_SWAMP_GAME_H
