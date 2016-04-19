#include "include/Game.h"
#include "include/GameState.h"

constexpr unsigned int winWidth{800}, winHeight{600};
std::vector<Entity *> entitiesToRender;
std::vector<Enemy *> AIsToMove;
std::vector<Pickup *> pickups;


Game::Game() : m_window({winWidth, winHeight}, "Legend of the Swamp"),
               m_texmgr(),
               m_background()
{
    loadTextures();
    loadTiles();
    loadFonts();
    loadStylesheets();
	playerExists = false; //This bool needed to prevent segfaults on WASD entry on load screen.
    m_window.setFramerateLimit(60);

    m_background.setTexture(m_texmgr.getRef("background"));
}

void Game::loadStartingEntities()
{
    m_player = new Player(true, 100, 300, 0, "front.png"); //Just a test entity that uses the player front texture, but with the HIGHEST SIZE WE NEED.
    Enemy *m_enemy = new Enemy(true, 1, m_player, 500, 185, 0.0, "front_e.png");
    Sword *m_sword = new Sword(true, m_player, 300, 215, 0.0, "sword.png");
    Bow *m_bow = new Bow(true, m_player, 200, 215, 0.0, "bow.png");
    std::vector<char> moves;
    moves.push_back('c');
    m_enemy->setMoveSequence(moves);
    entitiesToRender.push_back(m_player);
    entitiesToRender.push_back(m_enemy);
    entitiesToRender.push_back(m_sword);
    entitiesToRender.push_back(m_bow);
    
    AIsToMove.push_back(m_enemy);
    
    pickups.push_back(m_sword);
    pickups.push_back(m_bow);
    playerExists = true;
}

void Game::drawEntities()
{
    for (Entity *e : entitiesToRender)
    {
		if(e->getHealth() <= 0)
			entitiesToRender.erase(std::remove(entitiesToRender.begin(), entitiesToRender.end(), e), entitiesToRender.end()); //Shitty line of code that removes e from the vector.
        else{
        sf::Sprite sprite = e->getSprite();
        	sprite.setPosition(e->getX() + e->xOffset(), e->getY() + e->yOffset());
        m_window.draw(sprite);
		}
    }
}

void Game::moveAIs()
{
    for (Enemy *e : AIsToMove)
    {
        e->move();
    }
}
void Game::checkPickups()
{
    for (Pickup *e : pickups)
    {
		if(e->getHealth() <= 0)
			pickups.erase(std::remove(pickups.begin(), pickups.end(), e), pickups.end()); //Shitty line of code that removes e from the vector.
        else
			e->checkPickup();
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
		if(playerExists)
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
        checkPickups();
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
