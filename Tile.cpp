#include "Tile.h"

Tile::Tile(unsigned int tileSize, unsigned int height, sf::Texture &texture,
           const std::vector<Animation> &animations,
           TileType tileType, unsigned int cost, unsigned int maxPopPerLevel,
           unsigned int maxLevels) : m_tileType(tileType),
                                     m_tileVariant(0),
                                     m_regions{0}
{
    m_sprite.setOrigin(sf::Vector2f(0.0f, tileSize * (height - 1)));
    m_sprite.setTexture(texture);

    m_animHandler.m_frameSize = sf::IntRect(0, 0, tileSize * 2, tileSize * height);
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
        default:
        case TileType::VOID:
            return "Void";
        case TileType::GRASS:
            return "Flatten";
        case TileType::FOREST:
            return "Forest";
        case TileType::WATER:
            return "Water";
    }
}