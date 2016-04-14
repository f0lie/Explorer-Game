#include <SFML/Graphics.hpp>

#include <fstream>

#include "Map.h"

// Load map from disk
void Map::load(const std::string &filename, unsigned int width, unsigned int height,
               std::map<std::string, Tile> &tileAtlas)
{
    std::ifstream inputFile;
    inputFile.open(filename, std::ios::in | std::ios::binary);

    m_width = width;
    m_height = height;

    for (int pos = 0; pos < m_width * m_height; pos++)
    {
        m_resources.push_back(255);
        m_selected.push_back(0);

        TileType tileType;
        inputFile.read((char *) &tileType, sizeof(int));
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
                break;
            case TileType::RESIDENTIAL:
                m_tiles.push_back(tileAtlas.at("residential"));
                break;
            case TileType::COMMERCIAL:
                m_tiles.push_back(tileAtlas.at("commercial"));
                break;
            case TileType::INDUSTRIAL:
                m_tiles.push_back(tileAtlas.at("industrial"));
                break;
            case TileType::ROAD:
                m_tiles.push_back(tileAtlas.at("road"));
                break;
        }
        Tile &tile = m_tiles.back();
        inputFile.read((char *) &tile.m_tileVariant, sizeof(int));
        inputFile.read((char *) &tile.m_regions, sizeof(int) * 1);
        inputFile.read((char *) &tile.m_population, sizeof(double));
        inputFile.read((char *) &tile.m_storedGoods, sizeof(float));
    }

    inputFile.close();
}

void Map::save(const std::string &filename)
{
    std::ofstream outputFile;
    outputFile.open(filename, std::ios::out | std::ios::binary);

    for (auto tile : m_tiles)
    {
        outputFile.write((char *) &tile.m_tileType, sizeof(int));
        outputFile.write((char *) &tile.m_tileVariant, sizeof(int));
        outputFile.write((char *) &tile.m_regions, sizeof(int) * 1);
        outputFile.write((char *) &tile.m_population, sizeof(double));
        outputFile.write((char *) &tile.m_storedGoods, sizeof(float));
    }

    outputFile.close();
}

void Map::draw(sf::RenderWindow &window, float dt)
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            // Set the position of the tile in the 2d world
            // This match is for isometric grids
            sf::Vector2f pos;
            pos.x = (x - y) * m_tileSize + m_width * m_tileSize;
            pos.y = (x + y) * m_tileSize * 0.5f;
            m_tiles[y * m_width + x].m_sprite.setPosition(pos);

            if(m_selected[y*m_width+x])
                m_tiles[y*m_width+x].m_sprite.setColor(sf::Color(0x7d, 0x7d, 0x7d));
            else
                m_tiles[y*m_width+x].m_sprite.setColor(sf::Color(0xff, 0xff, 0xff));

            // Draw the tile
            m_tiles[y * m_width + x].draw(window, dt);
        }
    }
}

void Map::updateDirection(TileType tileType)
{
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
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
                adjacentTiles[0][3] = (m_tiles[(y - 1) * m_width + (x)].m_tileType == tileType);
            if (x < m_width - 1 && y > 0)
                adjacentTiles[0][4] = (m_tiles[(y - 1) * m_width + (x + 1)].m_tileType == tileType);
            if (x > 0)
                adjacentTiles[1][0] = (m_tiles[(y) * m_width + (x - 1)].m_tileType == tileType);
            if (x < m_width - 1)
                adjacentTiles[1][5] = (m_tiles[(y) * m_width + (x + 1)].m_tileType == tileType);
            if (x > 0 && y < m_height - 1)
                adjacentTiles[2][0] = (m_tiles[(y + 1) * m_width + (x - 1)].m_tileType == tileType);
            if (y < m_height - 1)
                adjacentTiles[2][6] = (m_tiles[(y + 1) * m_width + (x)].m_tileType == tileType);
            if (x < m_width - 1 && y < m_height - 1)
                adjacentTiles[2][7] = (m_tiles[(y + 1) * m_width + (x + 1)].m_tileType == tileType);

            /* Change the tile variant depending on the tile position */
            if (adjacentTiles[1][0] && adjacentTiles[1][8] && adjacentTiles[0][9] && adjacentTiles[2][10])
                m_tiles[pos].m_tileVariant = 2;
            else if (adjacentTiles[1][0] && adjacentTiles[1][11] && adjacentTiles[0][12])
                m_tiles[pos].m_tileVariant = 7;
            else if (adjacentTiles[1][0] && adjacentTiles[1][13] && adjacentTiles[2][14])
                m_tiles[pos].m_tileVariant = 8;
            else if (adjacentTiles[0][15] && adjacentTiles[2][16] && adjacentTiles[1][0])
                m_tiles[pos].m_tileVariant = 9;
            else if (adjacentTiles[0][16] && adjacentTiles[2][17] && adjacentTiles[1][18])
                m_tiles[pos].m_tileVariant = 10;
            else if (adjacentTiles[1][0] && adjacentTiles[1][19])
                m_tiles[pos].m_tileVariant = 0;
            else if (adjacentTiles[0][20] && adjacentTiles[2][21])
                m_tiles[pos].m_tileVariant = 1;
            else if (adjacentTiles[2][22] && adjacentTiles[1][0])
                m_tiles[pos].m_tileVariant = 3;
            else if (adjacentTiles[0][23] && adjacentTiles[1][24])
                m_tiles[pos].m_tileVariant = 4;
            else if (adjacentTiles[1][0] && adjacentTiles[0][25])
                m_tiles[pos].m_tileVariant = 5;
            else if (adjacentTiles[2][26] && adjacentTiles[1][27])
                m_tiles[pos].m_tileVariant = 6;
            else if (adjacentTiles[1][0])
                m_tiles[pos].m_tileVariant = 0;
            else if (adjacentTiles[1][28])
                m_tiles[pos].m_tileVariant = 0;
            else if (adjacentTiles[0][29])
                m_tiles[pos].m_tileVariant = 1;
            else if (adjacentTiles[2][30])
                m_tiles[pos].m_tileVariant = 1;
        }
    }
}

void Map::depthFirstSearch(std::vector<TileType> &whitelist,
                           sf::Vector2i pos, int label, int regionType = 0)
{
    if (pos.x < 0 || pos.x >= m_width)
    {
        return;
    }
    if (pos.y < 0 || pos.y >= m_height)
    {
        return;
    }
    if (m_tiles[pos.y * m_width + pos.x].m_regions[regionType] != 0)
    {
        return;
    }

    bool found = false;
    for (auto type : whitelist)
    {
        if (type == m_tiles[pos.y * m_width + pos.x].m_tileType)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        return;
    }

    m_tiles[pos.y * m_width + pos.x].m_regions[regionType] = label;

    depthFirstSearch(whitelist, pos + sf::Vector2i(-1, 0), label, regionType);
    depthFirstSearch(whitelist, pos + sf::Vector2i(0, 1), label, regionType);
    depthFirstSearch(whitelist, pos + sf::Vector2i(1, 0), label, regionType);
    depthFirstSearch(whitelist, pos + sf::Vector2i(0, -1), label, regionType);

    return;
}

void Map::findConnectedRegions(std::vector<TileType> whitelist, int regionType=0)
{
    int regions = 1;

    for(auto& tile : m_tiles)
    {
        tile.m_regions[regionType] = 0;
    }

    for(int y = 0; y < m_height; ++y)
    {
        for(int x = 0; x < m_width; ++x)
        {
            bool found = false;
            for(auto type : whitelist)
            {
                if(type == m_tiles[y*m_width+x].m_tileType)
                {
                    found = true;
                    break;
                }
            }
            if(m_tiles[y*m_width+x].m_regions[regionType] == 0 && found)
            {
                depthFirstSearch(whitelist, sf::Vector2i(x, y), regions++, regionType);
            }
        }
    }
    m_numRegions[regionType] = regions;
}

void Map::clearSelected()
{
    for (auto& tile : m_selected)
    {
        tile = 0;
    }
    m_numSelected = 0;
}

inline int clamp(int n, int lower, int upper)
{
    return std::max(lower, std::min(n, upper));
}

void Map::select(sf::Vector2i start, sf::Vector2i end, std::vector<TileType> blacklist)
{
    // Swap the coordinates if necessary
    if(end.y < start.y)
    {
        std::swap(start.y, end.y);
    }
    if(end.x < start.x)
    {
        std::swap(start.x, end.x);
    }

    // Clamp in range
    end.x = clamp(end.x, 0, m_width-1);
    end.y = clamp(end.y, 0, m_height-1);
    start.x = clamp(start.x, 0, m_width-1);
    start.y = clamp(start.y, 0, m_height-1);

    for(int y = start.y; y <= end.y; y++)
    {
        for(int x = start.x; x <= end.x; x++)
        {
            // Select the tile and deselect the blacklisted ones
            m_selected[y * m_width + x] = 1;
            m_numSelected++;
            for(auto type : blacklist)
            {
                if(m_tiles[y * m_width + x].m_tileType == type)
                {
                    m_selected[y * m_width + x] = 2;
                    m_numSelected--;
                    break;
                }
            }

        }
    }
}