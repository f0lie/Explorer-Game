#include "GameStateStart.h"
#include "GameStateEditor.h"

GameStateStart::GameStateStart(Game* game) : GameState(game)
{
    sf::Vector2f pos{m_game->m_window.getSize()};
    m_view.setSize(pos);
    pos *= 0.5f;
    m_view.setCenter(pos);
}

void GameStateStart::draw(const float dt)
{
    m_game->m_window.setView(m_view);

    m_game->m_window.clear(sf::Color::Black);
    m_game->m_window.draw(m_game->m_background);
}

void GameStateStart::update(const float dt)
{

}

void GameStateStart::handleInput()
{
    sf::Event event;

    while(m_game->m_window.pollEvent(event)) {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                m_game->m_window.close();
                break;
            }
            case sf::Event::Resized:
            {
                m_view.setSize(event.size.width, event.size.height);
                m_game->m_background.setPosition(m_game->m_window.mapPixelToCoords(sf::Vector2i(0, 0)));
                m_game->m_background.setScale(
                        float(event.size.width) / float(m_game->m_background.getTexture()->getSize().x),
                        float(event.size.height) / float(m_game->m_background.getTexture()->getSize().y));
                break;
            }
            case sf::Event::KeyPressed:
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    m_game->m_window.close();
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    loadGame();
                }
                break;
            }
            default:
                break;
        }
    }
}

void GameStateStart::loadGame()
{
    m_game->pushState(std::make_unique<GameStateEditor>(m_game));
}