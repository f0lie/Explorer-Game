#ifndef LEGEND_OF_THE_SWAMP_GAMESTATEEDITOR_H
#define LEGEND_OF_THE_SWAMP_GAMESTATEEDITOR_H

#include <SFML/Graphics.hpp>

#include "GameState.h"

class GameStateEditor : public GameState
{
public:
    GameStateEditor(Game* game);

    virtual void draw(const float dt) override;
    virtual void update(const float dt) override;
    virtual void handleInput() override;
private:
    sf::View m_gameView;
    sf::View m_guiView;
};


#endif //LEGEND_OF_THE_SWAMP_GAMESTATEEDITOR_H
