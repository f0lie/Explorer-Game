#ifndef LEGEND_OF_THE_SWAMP_GAMESTATEEDITOR_H
#define LEGEND_OF_THE_SWAMP_GAMESTATEEDITOR_H

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "Map.h"

enum class ActionState {
    NONE, PANNING, SELECTING
};

//TODO: Remove this class because you don't need to edit the world in a RPG
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

    Map m_map;

    sf::Vector2i m_panningAnchor;
    float m_zoomLevel;

    sf::Vector2i m_selectionStart;
    sf::Vector2i m_selectionEnd;

    Tile* m_currentTile;
};


#endif //LEGEND_OF_THE_SWAMP_GAMESTATEEDITOR_H
