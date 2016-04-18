#include "include/Game.h"
#include "include/GameState.h"

constexpr unsigned int winWidth{800}, winHeight{600};
std::vector<Entity *> entitiesToRender;
std::vector<Enemy *> AIsToMove;

Game::Game() : m_window({winWidth, winHeight}, "Legend of the Swamp"),
               m_texmgr(),
               m_background()
{
    loadTextures();
    loadTiles();
    loadFonts();
    loadStylesheets();
    loadStartingEntities();

    m_window.setFramerateLimit(60);

    m_background.setTexture(m_texmgr.getRef("background"));
}

void Game::loadStartingEntities()
{
    m_player = new Player(true, 100, 100, 0, "front.png"); //Just a test entity that uses the m_player front texture.
    m_enemy = new Enemy(true, 1, m_player, 600, 485, 0, "front_e.png");
    char moves[2] = {'c', 'c'};
    m_enemy->setMoveSequence(moves);
    entitiesToRender.push_back(m_player);
    entitiesToRender.push_back(m_enemy);
    AIsToMove.push_back(m_enemy);
}

void Game::drawEntities()
{
    for (Entity *e : entitiesToRender)
    {
        sf::Sprite sprite = e->getSprite();
        sprite.setPosition(e->getX() + 3,
                           e->getY() + 9); //the +3 and +9 are so they're drawn in a more central location.
        m_window.draw(sprite);
    }
}

void Game::moveAIs()
{
    for (Enemy *e : AIsToMove)
    {
        e->move();
    }
}

void Game::run()
{
    sf::Clock clock;
    sf::Music music;

    if (!music.openFromFile("media/Fade.ogg"))
        std::cout << "Missing audio file Fade.ogg!";

    music.play();

    while (m_window.isOpen())
    {
        takeInput();
        sf::Time elapsed{clock.restart()};
        float dt{elapsed.asSeconds()};

        if (peekState() == nullptr)
        {
            continue;
        }

        peekState()->handleInput();
        peekState()->update(dt);
        m_window.clear(sf::Color::Black);
        peekState()->draw(dt);
        moveAIs();
        drawEntities();
        m_window.display();
    }
}

void Game::takeInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_player->up();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_player->left();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_player->down();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_player->right();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_player->attack();
    }
}

void Game::pushState(std::unique_ptr<GameState> state)
{
    // http://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function
    // m_states owns the states so move is required
    m_states.push(std::move(state));
}

void Game::popState()
{
    m_states.pop();
}

void Game::changeState(std::unique_ptr<GameState> state)
{
    if (!m_states.empty())
    {
        popState();
    }

    pushState(std::move(state));
}

GameState *Game::peekState()
{
    if (m_states.empty())
    {
        return nullptr;
    }

    return m_states.top().get();
}

void Game::loadTiles()
{
    // TODO: Expand on the type of tiles
    // TODO: Figure out a way to draw Entities on top of tiles
    Animation staticAnim(0, 0, 1.0f);
    m_tileAtlas["grass"] =
            Tile(m_tileSize, 1, m_texmgr.getRef("grass"), {staticAnim}, TileType::GRASS);
    m_tileAtlas["forest"] =
            Tile(m_tileSize, 1, m_texmgr.getRef("forest"), {staticAnim}, TileType::FOREST);
    m_tileAtlas["water"] =
            Tile(m_tileSize, 1, m_texmgr.getRef("water"), {Animation(0, 3, 0.5f),
                                                           Animation(0, 3, 0.5f),
                                                           Animation(0, 3, 0.5f)}, TileType::WATER);
}

void Game::loadTextures()
{
    // TODO: Change to load RPG texture, assuming we made them...
    m_texmgr.loadTexture("grass", "media/grass.png");
    m_texmgr.loadTexture("forest", "media/forest.png");
    m_texmgr.loadTexture("water", "media/water.png");

    m_texmgr.loadTexture("background", "media/background.png");
}

void Game::loadFonts()
{
    sf::Font font;
    font.loadFromFile("media/font.ttf");
    m_fonts["main_font"] = font;
}

void Game::loadStylesheets()
{
    m_stylesheets["button"] = GuiStyle(&m_fonts.at("main_font"), 1,
                                       sf::Color(0xc6, 0xc6, 0xc6), sf::Color(0x94, 0x94, 0x94),
                                       sf::Color(0x00, 0x00, 0x00),
                                       sf::Color(0x61, 0x61, 0x61), sf::Color(0x94, 0x94, 0x94),
                                       sf::Color(0x00, 0x00, 0x00));
    m_stylesheets["text"] = GuiStyle(&m_fonts.at("main_font"), 0,
                                     sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00),
                                     sf::Color(0xff, 0xff, 0xff),
                                     sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00),
                                     sf::Color(0xff, 0x00, 0x00));
}
