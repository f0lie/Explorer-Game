#ifndef LEGEND_OF_THE_SWAMP_GAME_H
#define LEGEND_OF_THE_SWAMP_GAME_H

#include <SFML/Graphics.hpp>

#include <stack>
#include <memory>
#include <map>

#include "Gui.h"
#include "TextureManager.h"
#include "Tile.h"

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

    GameState *peekState();

    void run();

    // Public members for now
    sf::RenderWindow m_window;
    sf::Sprite m_background;
    TextureManager m_texmgr;

    const static int tileSize{8};

    //TODO: type alias for tileAtlas
    std::map<std::string, Tile> m_tileAtlas;
    std::map<std::string, GuiStyle> m_stylesheets;
    std::map<std::string, sf::Font> m_fonts;
private:
    void loadTextures();

    void loadTiles();

    void loadStylesheets();

    void loadFonts();
};


#endif //LEGEND_OF_THE_SWAMP_GAME_H
