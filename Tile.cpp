#include "Tile.h"

Tile::Tile(unsigned int tileSize,
           unsigned int height,
           sf::Texture &texture,
           const std::vector<Animation> &animations,
           TileType tileType) : m_tileType(tileType),
                                m_tileVariant(0),
                                m_regions{0}
{
    m_sprite.setTexture(texture);

    m_animHandler.m_frameSize = sf::IntRect(0, 0, tileSize, tileSize * height);
    for (auto animation : animations)
    {
        m_animHandler.addAnim(animation);
    }
    m_animHandler.update(0.0f);
}

void Tile::draw(sf::RenderWindow &window, const float dt)
{
    // Change the sprite to reflect the tile variant
    m_animHandler.changeAnim(m_tileVariant);

    // Update the animation
    m_animHandler.update(dt);

    // Update the sprite
    m_sprite.setTextureRect(m_animHandler.m_bounds);

    // Draw the tile
    window.draw(m_sprite);
}

void Tile::update()
{

}

std::string tileTypeToStr(TileType type)
{
// TODO: Change the tiles to RPG ones
    switch (type)
    {
        case TileType::GRASS:
            return "Flatten";
        case TileType::FOREST:
            return "Forest";
        case TileType::WATER:
            return "Water";
        default:
            return "Void";
    }
}
