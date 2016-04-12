//
// Created by alex on 4/12/16.
//

#ifndef LEGEND_OF_THE_SWAMP_GAMESTATE_H
#define LEGEND_OF_THE_SWAMP_GAMESTATE_H

#include "Game.h"

class GameState {
public:
    Game* game;

    virtual void draw(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void handleInput() = 0;
};


#endif //LEGEND_OF_THE_SWAMP_GAMESTATE_H
