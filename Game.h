#ifndef LEGEND_OF_THE_SWAMP_GAME_H
#define LEGEND_OF_THE_SWAMP_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stack>
#include <memory>
#include <map>
#include <iostream>
#include <vector>

#include "Gui.h"
#include "TextureManager.h"
#include "Tile.h"
#include "Entity.h"

class GameState;

class Game
{
public:
    // Public members for now
    sf::RenderWindow m_window;
    sf::Sprite m_background;
    TextureManager m_texmgr;
    Entity *player; //Temporary player to test controls.
	
    const static int m_tileSize{8};

    //TODO: type alias for tileAtlas
    std::map<std::string, Tile> m_tileAtlas;
    std::map<std::string, GuiStyle> m_stylesheets;
    std::map<std::string, sf::Font> m_fonts;
	
    Game();

    /*
     * m_states is a stack that contains all of the states to be loaded.
     * Stacking the states allow swap states easily like between Pause and Start.
     */
    std::stack<std::unique_ptr<GameState>> m_states;
	void loadStartingEntities();
    void pushState(std::unique_ptr<GameState> state);

    void popState();
	void takeInput();
    void changeState(std::unique_ptr<GameState> state);

    GameState *peekState();

    void run();

private:
    void loadTextures();

    void loadTiles();

    void loadStylesheets();

    void loadFonts();
    void drawEntities();
};


#endif //LEGEND_OF_THE_SWAMP_GAME_H
