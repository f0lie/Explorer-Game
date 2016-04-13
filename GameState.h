#ifndef LEGEND_OF_THE_SWAMP_GAMESTATE_H
#define LEGEND_OF_THE_SWAMP_GAMESTATE_H

#include "Game.h"

// ABC for States
class GameState
{
public:
    virtual void draw(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void handleInput() = 0;

protected:
    GameState(Game* game) : m_game(game) {}

    Game* m_game;
};


#endif //LEGEND_OF_THE_SWAMP_GAMESTATE_H
