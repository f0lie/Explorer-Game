#include "GameState.h"
#include "GameStateEditor.h"

GameStateEditor::GameStateEditor(Game* game) : GameState(game),
                                               m_guiView(),
                                               m_gameView()
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
    m_game->m_window.draw(m_game->m_background);

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
            case sf::Event::Closed:
            {
                m_game->m_window.close();
                break;
            }
            case sf::Event::Resized:
            {
                // Change the view so it matches the resized window
                m_gameView.setSize(event.size.width, event.size.height);
                m_guiView.setSize(event.size.width, event.size.height);
                m_game->m_background.setPosition(m_game->m_window.mapPixelToCoords(sf::Vector2i(0, 0), this->m_guiView));
                m_game->m_background.setScale(
                        float(event.size.width) / float(m_game->m_background.getTexture()->getSize().x),
                        float(event.size.height) / float(m_game->m_background.getTexture()->getSize().y));
                break;
            }
            default:
                break;
        }
    }

    return;
}
