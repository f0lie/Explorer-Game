#ifndef LEGEND_OF_THE_SWAMP_MAP_H
#define LEGEND_OF_THE_SWAMP_MAP_H

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <map>

#include "Tile.h"

class Map
{
public:
    unsigned int m_width;
    unsigned int m_height;

    std::vector<Tile> m_tiles;

    unsigned int m_tileSize;

    Map() : m_tileSize(8),
            m_width(0),
            m_height(0) { }

    /* Load map from file constructor */
    Map(const std::string &filename, std::map<std::string, Tile> &tileAtlas) : m_tileSize(8)
    {
        load(filename, tileAtlas);
    }

    /* Load map from disk */
    void load(const std::string &filename, std::map<std::string, Tile> &tileAtlas);

    /* Save map to disk */
    void save(const std::string &filename);

    /* Draw the map */
    void draw(sf::RenderWindow &window, float dt);


    /*
     * Update the direction of directional tiles to correct position
     * i.e roads, rivers, and etc
     */
    void updateDirection(TileType tileType);
};


#endif //LEGEND_OF_THE_SWAMP_MAP_H
