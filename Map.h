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
    Map() : m_tileSize(8),
            m_width(0),
            m_height(0),
            m_numRegions{1},
            m_numSelected(0)
    { }

    /* Load map from file constructor */
    Map(const std::string &filename, unsigned int width, unsigned int height,
        std::map<std::string, Tile> &tileAtlas) : m_tileSize(8),
                                                  m_numSelected(0)
    {
        load(filename, width, height, tileAtlas);
    }

    unsigned int m_width;
    unsigned int m_height;

    std::vector<Tile> m_tiles;

    /* Resource map for industrial tiles */
    std::vector<int> m_resources;

    unsigned int m_tileSize;

    /* 0 = Deselected, 1 = Selected, 2 = Invalid */
    std::vector<char> m_selected;
    unsigned int m_numSelected;

    unsigned int m_numRegions[1];

    /* Load map from disk */
    void load(const std::string &filename, unsigned int width, unsigned int height,
              std::map<std::string, Tile> &tileAtlas);

    /* Save map to disk */
    void save(const std::string &filename);

    /* Draw the map */
    void draw(sf::RenderWindow &window, float dt);

    /* Check if one position in the map is connected to another by traversing whitelist */
    void findConnectedRegions(std::vector<TileType> whitelist, int type);

    /*
     * Update the direction of directional tiles to correct position
     * i.e roads, rivers, and etc
     */
    void updateDirection(TileType tileType);

    /* Select the tiles within the bounds */
    void select(sf::Vector2i start, sf::Vector2i end, std::vector<TileType> blacklist);

    /* Deselect all tiles */
    void clearSelected();

private:
    void depthFirstSearch(std::vector<TileType> &whitelist,
                          sf::Vector2i pos, int label, int type);

};


#endif //LEGEND_OF_THE_SWAMP_MAP_H
