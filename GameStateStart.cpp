#include "GameStateStart.h"
#include "GameStateEditor.h"

GameStateStart::GameStateStart(Game *game) : GameState(game)
{
    sf::Vector2f pos{m_game->m_window.getSize()};
    m_view.setSize(pos);
    pos *= 0.5f;
    m_view.setCenter(pos);

    m_guiSystem.emplace("menu", Gui(sf::Vector2f(192, 32), 4, false, m_game->m_stylesheets.at("button"),
                                    {std::make_pair("Load Game", "load_game")}));
    m_guiSystem.at("menu").setPosition(pos);
    m_guiSystem.at("menu").setOrigin(96, 32 * 1 / 2);
    m_guiSystem.at("menu").show();
}

void GameStateStart::draw(const float dt)
{
    m_game->m_window.setView(m_view);
    m_game->m_window.clear(sf::Color::Black);
    m_game->m_window.draw(m_game->m_background);

    for (const auto &gui : m_guiSystem)
    { m_game->m_window.draw(gui.second); }
}

void GameStateStart::update(const float dt)
{

}

void GameStateStart::handleInput()
{
    sf::Event event;

    sf::Vector2f mousePos = m_game->m_window.mapPixelToCoords(sf::Mouse::getPosition(m_game->m_window), m_view);

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
                m_view.setSize(event.size.width, event.size.height);
                m_game->m_background.setPosition(m_game->m_window.mapPixelToCoords(sf::Vector2i(0, 0), m_view));

                sf::Vector2f pos{event.size.width, event.size.height};
                pos *= 0.5f;
                pos = m_game->m_window.mapPixelToCoords(sf::Vector2i(pos), m_view);
                m_guiSystem.at("menu").setPosition(pos);

                m_game->m_background.setScale(
                        float(event.size.width) / float(m_game->m_background.getTexture()->getSize().x),
                        float(event.size.height) / float(m_game->m_background.getTexture()->getSize().y));
                break;
            }
            case sf::Event::MouseMoved:
            {
                // Highlight menu items
                m_guiSystem.at("menu").highlight(m_guiSystem.at("menu").getEntry(mousePos));
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                // Click on menu items
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::string msg = m_guiSystem.at("menu").activate(mousePos);
                    if (msg == "load_game")
                    { loadGame(); }
                }
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                { m_game->m_window.close(); }
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