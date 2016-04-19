#include "include/GameState.h"
#include "include/GameStateEditor.h"

GameStateEditor::GameStateEditor(Game *game) : GameState(game),
                                               m_map("big_map.bmp", game->m_tileAtlas),
                                               m_guiView(),
                                               m_gameView(),
                                               m_currentTile(&game->m_tileAtlas.at("grass"))
{
    sf::Vector2f pos{m_game->m_window.getSize()};
    m_guiView.setSize(pos);
    m_gameView.setSize(pos);
    pos *= 0.5f;
    m_guiView.setCenter(pos);
    m_gameView.setCenter(pos);

    // Centre the camera on the map
    sf::Vector2f centre(float(m_map.m_width * 0.5), float(m_map.m_height * 0.5));
    centre *= float(m_map.m_tileSize);
    m_gameView.setCenter(centre);

    // TODO: Expand on the infobar to include character stats
    m_guiSystem.emplace("infoBar", Gui(sf::Vector2f(m_game->m_window.getSize().x / 5, 16), 2, true,
                                       m_game->m_stylesheets.at("button"),
                                       {std::make_pair("health", "health")}));
    m_guiSystem.at("infoBar").setPosition(sf::Vector2f(0, m_game->m_window.getSize().y - 16));
    m_guiSystem.at("infoBar").show();

    m_actionState = ActionState::NONE;
}

void GameStateEditor::draw(const float dt)
{
    m_game->m_window.clear(sf::Color::Black);

    m_game->m_window.setView(m_guiView);
    m_game->m_window.draw(m_game->m_background);

    m_game->m_window.setView(m_gameView);
    m_map.draw(m_game->m_window, dt);

    m_game->m_window.setView(m_guiView);
    for (auto gui : m_guiSystem) m_game->m_window.draw(gui.second);
}

void GameStateEditor::update(const float dt)
{
    /* Update the info bar at the bottom of the screen */
    // TODO: Change the infoBar to RPG elements like health or something
    m_guiSystem.at("infoBar").setEntryText(0, "Health: " + std::to_string(100));
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

                m_guiView.setSize(event.size.width, event.size.height);

                m_guiSystem.at("infoBar").setDimensions(
                        sf::Vector2f(event.size.width / m_guiSystem.at("infoBar").m_entries.size(), 16));
                m_guiSystem.at("infoBar").setPosition(
                        m_game->m_window.mapPixelToCoords(sf::Vector2i(0, event.size.height - 16), m_guiView));
                m_guiSystem.at("infoBar").show();

                m_game->m_background.setPosition(
                        m_game->m_window.mapPixelToCoords(sf::Vector2i(0, 0), m_guiView));
                m_game->m_background.setScale(
                        float(event.size.width) / float(m_game->m_background.getTexture()->getSize().x),
                        float(event.size.height) / float(m_game->m_background.getTexture()->getSize().y));
                break;
            }
            default:
                break;
        }
    }

}
