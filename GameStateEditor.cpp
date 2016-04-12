#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "GameStateEditor.h"

GameStateEditor::GameStateEditor(Game* game) : GameState(game)
{
    sf::Vector2f pos{m_game->m_window.getSize()};
    m_guiView.setSize(pos);
    m_gameView.setSize(pos);
    pos *= 0.5f;
    m_guiView.setCenter(pos);
    m_gameView.setCenter(pos);
}

void GameStateEditor::draw(const float dt)
{
    m_game->m_window.clear(sf::Color::Black);
    m_game->m_window.draw(m_game->background);

    return;
}

void GameStateEditor::update(const float dt)
{
    return;
}

void GameStateEditor::handleInput()
{
    sf::Event event;

    while(m_game->m_window.pollEvent(event))
    {
        switch(event.type)
        {
            /* Close the window */
            case sf::Event::Closed:
            {
                m_game->m_window.close();
                break;
            }
                /* Resize the window */
            case sf::Event::Resized:
            {
                m_gameView.setSize(event.size.width, event.size.height);
                m_guiView.setSize(event.size.width, event.size.height);
                m_game->background.setPosition(m_game->m_window.mapPixelToCoords(sf::Vector2i(0, 0), this->guiView));
                m_game->background.setScale(
                        float(event.size.width) / float(m_game->background.getTexture()->getSize().x),
                        float(event.size.height) / float(m_game->background.getTexture()->getSize().y));
                break;
            }
            default: break;
        }
    }

    return;
}
