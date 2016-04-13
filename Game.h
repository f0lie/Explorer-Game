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

    /*
     * m_states is a stack that contains all of the states to be loaded.
     * Stacking the states allow swap states easily like between Pause and Start.
     */
    std::stack<std::unique_ptr<GameState>> m_states;
    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);
    GameState* peekState();

    void run();

    // Public members for now
    sf::RenderWindow m_window;
    sf::Sprite m_background;
    TextureManager m_texmgr;
private:
    void loadTextures();
};


#endif //LEGEND_OF_THE_SWAMP_GAME_H
