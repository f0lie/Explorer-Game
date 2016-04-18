#ifndef LEGEND_OF_THE_SWAMP_TILE_H
#define LEGEND_OF_THE_SWAMP_TILE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "AnimationHandler.h"

//TODO: Expand on the type of tiles like roads
enum class TileType
{
    VOID, GRASS, FOREST, WATER,
};

constexpr TileType pixelToTileType(unsigned char red, unsigned char green, unsigned char blue)
{
    if (blue == 255) { return TileType::WATER; }
    if (green == 255) { return TileType::GRASS; }
    if (green == 219) { return TileType::FOREST; }
    return TileType::VOID;
}

class Tile
{
public:
    AnimationHandler m_animHandler;
    sf::Sprite m_sprite;

    TileType m_tileType;

    // Tile variant, allow for different looking versions of the same tile
    unsigned int m_tileVariant;

    Tile() = default;

    Tile(unsigned int tileSize,
         unsigned int height,
         sf::Texture &texture,
         const std::vector<Animation> &animations,
         TileType tileType);

    void draw(sf::RenderWindow &window, const float dt);

    void update();


};

#endif //LEGEND_OF_THE_SWAMP_TILE_H
