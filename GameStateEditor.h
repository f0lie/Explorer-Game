#ifndef LEGEND_OF_THE_SWAMP_GAMESTATEEDITOR_H
#define LEGEND_OF_THE_SWAMP_GAMESTATEEDITOR_H

#include <SFML/Graphics.hpp>

#include "GameState.h"

class GameStateEditor : public GameState
{
private:
    sf::View m_gameView;
    sf::View m_guiView;
public:
    virtual void draw(const float dt) override;
    virtual void update(const float dt) override;
    virtual void handleInput() override;

    GameStateEditor(Game* game);
};


#endif //LEGEND_OF_THE_SWAMP_GAMESTATEEDITOR_H
