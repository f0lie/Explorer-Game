#ifndef LEGEND_OF_THE_SWAMP_GAMESTATEEDITOR_H
#define LEGEND_OF_THE_SWAMP_GAMESTATEEDITOR_H

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "Map.h"

enum class ActionState
{
    NONE
};

class GameStateEditor : public GameState
{
public:
    GameStateEditor(Game *game);

    virtual void draw(const float dt) override;

    virtual void update(const float dt) override;

    virtual void handleInput() override;

private:
    ActionState m_actionState;

    sf::View m_gameView;
    sf::View m_guiView;

    std::map<std::string, Gui> m_guiSystem;

    Map m_map;

    Tile *m_currentTile;
};


#endif //LEGEND_OF_THE_SWAMP_GAMESTATEEDITOR_H
