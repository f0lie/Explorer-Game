#ifndef LEGEND_OF_THE_SWAMP_TILE_H
#define LEGEND_OF_THE_SWAMP_TILE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "AnimationHandler.h"

//TODO: changes the types to the correct game
enum class TileType
{
    VOID, GRASS, FOREST, WATER,
};

std::string tileTypeToStr(TileType type);
TileType pixelToTileType(unsigned char red, unsigned char green, unsigned char blue);

class Tile
{
public:
    AnimationHandler m_animHandler;
    sf::Sprite m_sprite;

    TileType m_tileType;

    // Tile variant, allow for different looking versions of the same tile
    unsigned int m_tileVariant;

    //TODO: remove these variables for the correct game type
    unsigned int m_regions[1];

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
