#ifndef LEGEND_OF_THE_SWAMP_GAMESTATESTART_H
#define LEGEND_OF_THE_SWAMP_GAMESTATESTART_H

#include <SFML/Graphics.hpp>

#include "GameState.h"

class GameStateStart : public GameState
{
public:
    virtual void draw(const float dt) override;

    virtual void update(const float dt) override;
    virtual void handleInput() override;
    GameStateStart(Game* game);
private:
    sf::View m_view;

    void loadGame();
};


#endif //LEGEND_OF_THE_SWAMP_GAMESTATESTART_H
