#ifndef LEGEND_OF_THE_SWAMP_TILE_H
#define LEGEND_OF_THE_SWAMP_TILE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "AnimationHandler.h"

//TODO: changes the types to the correct game
enum class TileType
{
    VOID, GRASS, FOREST, WATER, RESIDENTIAL, COMMERCIAL, INDUSTRIAL, ROAD
};

std::string tileTypeToStr(TileType type);

class Tile
{
public:


    Tile() = default;
    Tile(unsigned int tileSize, unsigned int height, sf::Texture &texture,
         const std::vector<Animation>& animations,
         TileType tileType, unsigned int cost, unsigned int maxPopPerLevel,
         unsigned int maxLevels);

    void draw(sf::RenderWindow& window, const float dt);

    void update();

    AnimationHandler m_animHandler;
    sf::Sprite m_sprite;

    TileType m_tileType;

    // Tile variant, allow for different looking versions of the same tile
    int m_tileVariant;

    //TODO: remove these variables for the correct game type
    unsigned int m_regions[1];
    unsigned int m_cost;
    double m_population;
    unsigned int m_maxPopPerLevel;
    unsigned int m_maxLevels;
    float m_production;
    float m_storedGoods;
};

#endif //LEGEND_OF_THE_SWAMP_TILE_H
