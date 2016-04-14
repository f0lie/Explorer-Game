#include "GameState.h"
#include "GameStateEditor.h"

GameStateEditor::GameStateEditor(Game *game) : GameState(game),
                                               m_guiView(),
                                               m_gameView(),
                                               m_map("city_map.dat", 64, 64, game->m_tileAtlas),
                                               m_zoomLevel(1.0f)
{
    sf::Vector2f pos{m_game->m_window.getSize()};
    m_guiView.setSize(pos);
    m_gameView.setSize(pos);
    pos *= 0.5f;
    m_guiView.setCenter(pos);
    m_gameView.setCenter(pos);

    // Centre the camera on the map
    sf::Vector2f centre(m_map.m_width, m_map.m_height * 0.5);
    centre *= float(m_map.m_tileSize);
    m_gameView.setCenter(centre);

    m_actionState = ActionState::NONE;
}

void GameStateEditor::draw(const float dt)
{
    m_game->m_window.clear(sf::Color::Black);

    m_game->m_window.setView(m_guiView);
    m_game->m_window.draw(m_game->m_background);

    m_game->m_window.setView(m_gameView);
    m_map.draw(m_game->m_window, dt);
}

void GameStateEditor::update(const float dt)
{

}

void GameStateEditor::handleInput()
{
    sf::Event event;

    while (m_game->m_window.pollEvent(event))
    {
        switch (event.type)
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
                m_gameView.zoom(m_zoomLevel);

                m_guiView.setSize(event.size.width, event.size.height);

                m_game->m_background.setPosition(
                        m_game->m_window.mapPixelToCoords(sf::Vector2i(0, 0), this->m_guiView));
                m_game->m_background.setScale(
                        float(event.size.width) / float(m_game->m_background.getTexture()->getSize().x),
                        float(event.size.height) / float(m_game->m_background.getTexture()->getSize().y));
                break;
            }
            case sf::Event::MouseMoved:
            {
                // Pan the camera
                if(m_actionState == ActionState::PANNING)
                {
                    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(m_game->m_window) - m_panningAnchor);
                    m_gameView.move(-1.0f * pos * m_zoomLevel);
                    m_panningAnchor = sf::Mouse::getPosition(m_game->m_window);
                }
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                // Start panning
                if(event.mouseButton.button == sf::Mouse::Middle)
                {
                    if(m_actionState != ActionState::PANNING)
                    {
                        m_actionState = ActionState::PANNING;
                        m_panningAnchor = sf::Mouse::getPosition(m_game->m_window);
                    }
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                // Stop panning
                if(event.mouseButton.button == sf::Mouse::Middle)
                {
                    m_actionState = ActionState::NONE;
                }
                break;
            }
            case sf::Event::MouseWheelMoved:
            {
                if(event.mouseWheel.delta < 0)
                {
                    m_gameView.zoom(2.0f);
                    m_zoomLevel *= 2.0f;
                }
                else
                {
                    m_gameView.zoom(0.5f);
                    m_zoomLevel *= 0.5f;
                }
                break;
            }
            default:
                break;
        }
    }
}
