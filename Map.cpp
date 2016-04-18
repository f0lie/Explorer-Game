#include <SFML/Graphics.hpp>

#include <fstream>

#include "Map.h"

/* Load map from disk */
// TODO: Change the binary format to a CSV/human readable format
void Map::load(const std::string &filename, unsigned int width, unsigned int height,
               std::map<std::string, Tile> &tileAtlas)
{
    std::ifstream inputFile;
    inputFile.open(filename, std::ios::in | std::ios::binary);

    m_width = width;
    m_height = height;

    for (unsigned int pos = 0; pos < m_width * m_height; pos++)
    {
        m_resources.push_back(255);
        m_selected.push_back(0);

        TileType tileType;
        inputFile.read((char *) &tileType, sizeof(int));
        // TODO: Change to RPG types
        switch (tileType)
        {
            case TileType::VOID:
            case TileType::GRASS:
                m_tiles.push_back(tileAtlas.at("grass"));
                break;
            case TileType::FOREST:
                m_tiles.push_back(tileAtlas.at("forest"));
                break;
            case TileType::WATER:
                m_tiles.push_back(tileAtlas.at("water"));
        }
        Tile &tile = m_tiles.back();

        inputFile.read((char *) &tile.m_tileVariant, sizeof(int));
        inputFile.read((char *) &tile.m_regions, sizeof(int) * 1);
    }

    inputFile.close();
}

// TODO: Save in a human readable format
void Map::save(const std::string &filename)
{
    std::ofstream outputFile;
    outputFile.open(filename, std::ios::out | std::ios::binary);

    for (auto tile : m_tiles)
    {
        outputFile.write((char *) &tile.m_tileType, sizeof(int));
        outputFile.write((char *) &tile.m_tileVariant, sizeof(int));
        outputFile.write((char *) &tile.m_regions, sizeof(int) * 1);
    }

    outputFile.close();
}

void Map::draw(sf::RenderWindow &window, float dt)
{
    for (unsigned int y = 0; y < m_height; y++)
    {
        for (unsigned int x = 0; x < m_width; x++)
        {
            /*
             * Set the position of the tile in the 2d world
             */
            sf::Vector2f pos;
            pos.x = x * m_tileSize;
            pos.y = y * m_tileSize;
            m_tiles[y * m_width + x].m_sprite.setPosition(pos);

            /* Draw the tile */
            m_tiles[y * m_width + x].draw(window, dt);
        }
    }
}

// TODO: Possibly remove this
void Map::updateDirection(TileType tileType)
{
    for (unsigned int y = 0; y < m_height; ++y)
    {
        for (unsigned int x = 0; x < m_width; ++x)
        {
            int pos = y * m_width + x;

            if (m_tiles[pos].m_tileType != tileType) continue;

            bool adjacentTiles[3][3] = {{0, 0, 0},
                                        {0, 0, 0},
                                        {0, 0, 0}};

            /* Check for adjacent tiles of the same type */
            if (x > 0 && y > 0)
                adjacentTiles[0][0] = (m_tiles[(y - 1) * m_width + (x - 1)].m_tileType == tileType);
            if (y > 0)
                adjacentTiles[0][1] = (m_tiles[(y - 1) * m_width + (x)].m_tileType == tileType);
            if (x < m_width - 1 && y > 0)
                adjacentTiles[0][2] = (m_tiles[(y - 1) * m_width + (x + 1)].m_tileType == tileType);
            if (x > 0)
                adjacentTiles[1][0] = (m_tiles[(y) * m_width + (x - 1)].m_tileType == tileType);
            if (x < m_width - 1)
                adjacentTiles[1][2] = (m_tiles[(y) * m_width + (x + 1)].m_tileType == tileType);
            if (x > 0 && y < m_height - 1)
                adjacentTiles[2][0] = (m_tiles[(y + 1) * m_width + (x - 1)].m_tileType == tileType);
            if (y < m_height - 1)
                adjacentTiles[2][1] = (m_tiles[(y + 1) * m_width + (x)].m_tileType == tileType);
            if (x < m_width - 1 && y < m_height - 1)
                adjacentTiles[2][2] = (m_tiles[(y + 1) * m_width + (x + 1)].m_tileType == tileType);

            /* Change the tile variant depending on the tile position */
            if (adjacentTiles[1][0] && adjacentTiles[1][2] && adjacentTiles[0][1] && adjacentTiles[2][1])
                m_tiles[pos].m_tileVariant = 2;
            else if (adjacentTiles[1][0] && adjacentTiles[1][2] && adjacentTiles[0][1])
                m_tiles[pos].m_tileVariant = 7;
            else if (adjacentTiles[1][0] && adjacentTiles[1][2] && adjacentTiles[2][1])
                m_tiles[pos].m_tileVariant = 8;
            else if (adjacentTiles[0][1] && adjacentTiles[2][1] && adjacentTiles[1][0])
                m_tiles[pos].m_tileVariant = 9;
            else if (adjacentTiles[0][1] && adjacentTiles[2][1] && adjacentTiles[1][2])
                m_tiles[pos].m_tileVariant = 10;
            else if (adjacentTiles[1][0] && adjacentTiles[1][2])
                m_tiles[pos].m_tileVariant = 0;
            else if (adjacentTiles[0][1] && adjacentTiles[2][1])
                m_tiles[pos].m_tileVariant = 1;
            else if (adjacentTiles[2][1] && adjacentTiles[1][0])
                m_tiles[pos].m_tileVariant = 3;
            else if (adjacentTiles[0][1] && adjacentTiles[1][2])
                m_tiles[pos].m_tileVariant = 4;
            else if (adjacentTiles[1][0] && adjacentTiles[0][1])
                m_tiles[pos].m_tileVariant = 5;
            else if (adjacentTiles[2][1] && adjacentTiles[1][2])
                m_tiles[pos].m_tileVariant = 6;
            else if (adjacentTiles[1][0])
                m_tiles[pos].m_tileVariant = 0;
            else if (adjacentTiles[1][2])
                m_tiles[pos].m_tileVariant = 0;
            else if (adjacentTiles[0][1])
                m_tiles[pos].m_tileVariant = 1;
            else if (adjacentTiles[2][1])
                m_tiles[pos].m_tileVariant = 1;
        }
    }
}

// depthFirstSearch and findConnectedRegions are designed for citybuilder tiles.
// Some tiles depend on the tiles around it so thats why they exist.

// TODO: Possiblely remove this for RPG game
void Map::depthFirstSearch(std::vector<TileType> &whitelist,
                           sf::Vector2i pos, int label, int regionType = 0)
{
    if (pos.x < 0 || pos.x >= int(m_width)) { return; }
    if (pos.y < 0 || pos.y >= int(m_height)) { return; }
    if (m_tiles[pos.y * m_width + pos.x].m_regions[regionType] != 0) { return; }

    bool found = false;
    for (auto type : whitelist)
    {
        if (type == m_tiles[pos.y * m_width + pos.x].m_tileType)
        {
            found = true;
            break;
        }
    }
    if (!found) { return; }

    m_tiles[pos.y * m_width + pos.x].m_regions[regionType] = label;

    depthFirstSearch(whitelist, pos + sf::Vector2i(-1, 0), label, regionType);
    depthFirstSearch(whitelist, pos + sf::Vector2i(0, 1), label, regionType);
    depthFirstSearch(whitelist, pos + sf::Vector2i(1, 0), label, regionType);
    depthFirstSearch(whitelist, pos + sf::Vector2i(0, -1), label, regionType);
}

// TODO: Possiblely remove this for RPG game
void Map::findConnectedRegions(std::vector<TileType> whitelist, int regionType = 0)
{
    int regions = 1;

    for (auto &tile : m_tiles)
    {
        tile.m_regions[regionType] = 0;
    }

    for (unsigned int y = 0; y < m_height; ++y)
    {
        for (unsigned int x = 0; x < m_width; ++x)
        {
            bool found = false;
            for (auto type : whitelist)
            {
                if (type == m_tiles[y * m_width + x].m_tileType)
                {
                    found = true;
                    break;
                }
            }
            if (m_tiles[y * m_width + x].m_regions[regionType] == 0 && found)
            {
                depthFirstSearch(whitelist, sf::Vector2i(x, y), regions++, regionType);
            }
        }
    }
    m_numRegions[regionType] = regions;
}
