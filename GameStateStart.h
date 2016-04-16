#ifndef LEGEND_OF_THE_SWAMP_GAMESTATESTART_H
#define LEGEND_OF_THE_SWAMP_GAMESTATESTART_H

#include <SFML/Graphics.hpp>

#include <utility>

#include "GameState.h"

// First state to load
class GameStateStart : public GameState
{
public:
    GameStateStart(Game *game);

    virtual void draw(const float dt) override;

    virtual void update(const float dt) override;

    virtual void handleInput() override;

private:
    void loadGame();

    sf::View m_view;

    std::map<std::string, Gui> m_guiSystem;
};


#endif //LEGEND_OF_THE_SWAMP_GAMESTATESTART_H
