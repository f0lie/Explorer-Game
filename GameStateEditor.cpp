#include "GameState.h"
#include "GameStateEditor.h"

// TODO: Entire class is almost useless for RPG game. However methods here are useful for other things.
GameStateEditor::GameStateEditor(Game *game) : GameState(game),
                                               m_city("city", m_game->m_tileSize, game->m_tileAtlas),
                                               m_guiView(),
                                               m_gameView(),
                                               m_zoomLevel(1.0f),
                                               m_selectionStart(0, 0),
                                               m_selectionEnd(0, 0),
                                               m_currentTile(&game->m_tileAtlas.at("grass"))
{
    sf::Vector2f pos{m_game->m_window.getSize()};
    m_guiView.setSize(pos);
    m_gameView.setSize(pos);
    pos *= 0.5f;
    m_guiView.setCenter(pos);
    m_gameView.setCenter(pos);

    // Centre the camera on the map
    // TODO: Replace City with the game map
    sf::Vector2f centre(m_city.map.m_width, m_city.map.m_height * 0.5);
    centre *= float(m_city.map.m_tileSize);
    m_gameView.setCenter(centre);

    m_city.shuffleTiles();

    /* Create gui elements */
    // TODO: Replace GUI elements with RPG ones
    m_guiSystem.emplace("rightClickMenu", Gui(sf::Vector2f(196, 16), 2, false, m_game->m_stylesheets.at("button"),
                                              {
                                                      std::make_pair(
                                                              "Flatten $" + m_game->m_tileAtlas["grass"].m_cost,
                                                              "grass"),
                                                      std::make_pair(
                                                              "Forest $" + m_game->m_tileAtlas["forest"].m_cost,
                                                              "forest"),
                                                      std::make_pair("Residential Zone $" +
                                                                     m_game->m_tileAtlas["residential"].m_cost,
                                                                     "residential"),
                                                      std::make_pair("Commercial Zone $" +
                                                                     m_game->m_tileAtlas["commercial"].m_cost,
                                                                     "commercial"),
                                                      std::make_pair("Industrial Zone $" +
                                                                     m_game->m_tileAtlas["industrial"].m_cost,
                                                                     "industrial"),
                                                      std::make_pair("Road $" + m_game->m_tileAtlas["road"].m_cost,
                                                                     "road")
                                              }));

    m_guiSystem.emplace("selectionCostText", Gui(sf::Vector2f(196, 16), 0, false, m_game->m_stylesheets.at("text"),
                                                 {std::make_pair("", "")}));

    m_guiSystem.emplace("infoBar", Gui(sf::Vector2f(m_game->m_window.getSize().x / 5, 16), 2, true,
                                       m_game->m_stylesheets.at("button"),
                                       {std::make_pair("time", "time"),
                                        std::make_pair("funds", "funds"),
                                        std::make_pair("population", "population"),
                                        std::make_pair("employment", "employment"),
                                        std::make_pair("current tile", "tile")}));
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
    m_city.map.draw(m_game->m_window, dt);

    m_game->m_window.setView(m_guiView);
    for (auto gui : m_guiSystem) m_game->m_window.draw(gui.second);
}

void GameStateEditor::update(const float dt)
{
    m_city.update(dt);

    /* Update the info bar at the bottom of the screen */
    // TODO: Change the infoBar to RPG elements like health or something
    m_guiSystem.at("infoBar").setEntryText(0, "Day: " + std::to_string(m_city.day));
    m_guiSystem.at("infoBar").setEntryText(1, "$" + std::to_string(long(m_city.funds)));
    m_guiSystem.at("infoBar").setEntryText(2, std::to_string(long(m_city.population)) + " (" +
                                              std::to_string(long(m_city.getHomeless())) + ")");
    m_guiSystem.at("infoBar").setEntryText(3, std::to_string(long(m_city.employable)) + " (" +
                                              std::to_string(long(m_city.getUnemployed())) + ")");
    m_guiSystem.at("infoBar").setEntryText(4, tileTypeToStr(m_currentTile->m_tileType));

    /* Highlight entries of the right click context menu */
    m_guiSystem.at("rightClickMenu").highlight(m_guiSystem.at("rightClickMenu").getEntry(
            m_game->m_window.mapPixelToCoords(sf::Mouse::getPosition(m_game->m_window), m_guiView)));
}

void GameStateEditor::handleInput()
{
    sf::Event event;

    sf::Vector2f guiPos = m_game->m_window.mapPixelToCoords(sf::Mouse::getPosition(m_game->m_window), m_guiView);
    sf::Vector2f gamePos = m_game->m_window.mapPixelToCoords(sf::Mouse::getPosition(m_game->m_window), m_gameView);

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
            case sf::Event::MouseMoved:
            {
                // Pan the camera
                if (m_actionState == ActionState::PANNING)
                {
                    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(m_game->m_window) - m_panningAnchor);
                    m_gameView.move(-1.0f * pos * m_zoomLevel);
                    m_panningAnchor = sf::Mouse::getPosition(m_game->m_window);
                }
                    // TODO: Remove selecting
                else if (m_actionState == ActionState::SELECTING)
                {
                    sf::Vector2f pos = m_game->m_window.mapPixelToCoords(sf::Mouse::getPosition(m_game->m_window),
                                                                         m_gameView);
                    m_selectionEnd.x =
                            pos.y / (m_city.map.m_tileSize) + pos.x / (2 * m_city.map.m_tileSize) -
                            m_city.map.m_width * 0.5 - 0.5;
                    m_selectionEnd.y =
                            pos.y / (m_city.map.m_tileSize) - pos.x / (2 * m_city.map.m_tileSize) +
                            m_city.map.m_width * 0.5 + 0.5;

                    m_city.map.clearSelected();
                    if (m_currentTile->m_tileType == TileType::GRASS)
                    {
                        m_city.map.select(m_selectionStart, m_selectionEnd,
                                          {m_currentTile->m_tileType, TileType::WATER});
                    }
                    else
                    {
                        m_city.map.select(m_selectionStart, m_selectionEnd,
                                          {
                                                  m_currentTile->m_tileType, TileType::FOREST,
                                                  TileType::WATER, TileType::ROAD,
                                                  TileType::RESIDENTIAL, TileType::COMMERCIAL,
                                                  TileType::INDUSTRIAL
                                          });
                    }

                    // TODO: Remove cost menus
                    m_guiSystem.at("selectionCostText").setEntryText(0, "$" + std::to_string(
                            m_currentTile->m_cost * m_city.map.m_numSelected));

                    if (m_city.funds <= m_city.map.m_numSelected * m_currentTile->m_cost)
                        m_guiSystem.at("selectionCostText").highlight(0);
                    else
                        m_guiSystem.at("selectionCostText").highlight(-1);

                    m_guiSystem.at("selectionCostText").setPosition(guiPos + sf::Vector2f(16, -16));
                    m_guiSystem.at("selectionCostText").show();
                }
                /* Highlight entries of the right click context menu */
                m_guiSystem.at("rightClickMenu").highlight(m_guiSystem.at("rightClickMenu").getEntry(guiPos));
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                // Start panning
                if (event.mouseButton.button == sf::Mouse::Middle)
                {
                    // TODO: Remove cost menus
                    m_guiSystem.at("rightClickMenu").hide();
                    m_guiSystem.at("selectionCostText").hide();
                    if (m_actionState == ActionState::PANNING)
                    {
                        m_actionState = ActionState::PANNING;
                        m_panningAnchor = sf::Mouse::getPosition(m_game->m_window);
                    }
                }
                    // TODO: Remove selecting
                else if (event.mouseButton.button == sf::Mouse::Left)
                {
                    /* Select a context menu entry. */
                    if (m_guiSystem.at("rightClickMenu").m_visable)
                    {
                        std::string msg = m_guiSystem.at("rightClickMenu").activate(guiPos);
                        if (msg != "null") m_currentTile = &m_game->m_tileAtlas.at(msg);

                        m_guiSystem.at("rightClickMenu").hide();
                    }
                    else
                    {
                        // Select map tile
                        if (m_actionState != ActionState::SELECTING)
                        {
                            m_actionState = ActionState::SELECTING;
                            m_selectionStart.x =
                                    gamePos.y / (m_city.map.m_tileSize) + gamePos.x / (2 * m_city.map.m_tileSize) -
                                    m_city.map.m_width * 0.5 - 0.5;
                            m_selectionStart.y =
                                    gamePos.y / (m_city.map.m_tileSize) - gamePos.x / (2 * m_city.map.m_tileSize) +
                                    m_city.map.m_width * 0.5 + 0.5;
                        }

                    }
                }
                    // TODO: Remove unselecting
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    /* Stop selecting */
                    if(m_actionState == ActionState::SELECTING)
                    {
                        m_actionState = ActionState::NONE;
                        m_guiSystem.at("selectionCostText").hide();
                        m_city.map.clearSelected();
                    }
                    else
                    {
                        /* Open the tile select menu */
                        sf::Vector2f pos = guiPos;

                        if(pos.x > m_game->m_window.getSize().x - m_guiSystem.at("rightClickMenu").getSize().x)
                        {
                            pos -= sf::Vector2f(m_guiSystem.at("rightClickMenu").getSize().x, 0);
                        }
                        if(pos.y > m_game->m_window.getSize().y - m_guiSystem.at("rightClickMenu").getSize().y)
                        {
                            pos -= sf::Vector2f(0, m_guiSystem.at("rightClickMenu").getSize().y);
                        }
                        m_guiSystem.at("rightClickMenu").setPosition(pos);
                        m_guiSystem.at("rightClickMenu").show();
                    }
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                // Stop panning
                if (event.mouseButton.button == sf::Mouse::Middle)
                {
                    m_actionState = ActionState::NONE;
                }
                    // Stop selecting
                else if (event.mouseButton.button == sf::Mouse::Left)
                {
                    /* Replace tiles if enough funds and a tile is selected */
                    if (m_currentTile != nullptr)
                    {
                        unsigned int cost = m_currentTile->m_cost * m_city.map.m_numSelected;
                        if (m_city.funds >= cost)
                        {
                            m_city.bulldoze(*m_currentTile);
                            m_city.funds -= m_currentTile->m_cost * m_city.map.m_numSelected;
                            m_city.tileChanged();
                        }
                    }
                    m_guiSystem.at("selectionCostText").hide();
                    m_actionState = ActionState::NONE;
                    m_city.map.clearSelected();
                }
                break;
            }
            case sf::Event::MouseWheelMoved:
            {
                // TODO: Reduce the speed of zooming
                if (event.mouseWheel.delta < 0)
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
