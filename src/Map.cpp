#include <SFML/Graphics.hpp>

#include <fstream>

#include "include/Map.h"
#include "../lib/EasyBMP/EasyBMP.h"

/* Load map from disk */
void Map::load(const std::string &filename, std::map<std::string, Tile> &tileAtlas)
{
    BMP map_file;
    map_file.ReadFromFile(filename.c_str());

    m_height = unsigned(map_file.TellHeight());
    m_width = unsigned(map_file.TellWidth());
	
    for (unsigned int y = 0; y < m_height; y++)
    {
        for (unsigned int x = 0; x < m_width; x++)
        {
            switch (pixelToTileType(map_file(x, y)->Red, map_file(x, y)->Green, map_file(x, y)->Blue))
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
                    m_tiles.back().m_tileVariant = 1;
                    break;
            }
        }
    }
}

void Map::save(const std::string &filename)
{
    std::ofstream outputFile(filename);

    outputFile << "TileType, TileVariant" << std::endl;

    for (auto tile : m_tiles)
    {
        outputFile << int(tile.m_tileType) << "," << tile.m_tileVariant << std::endl;
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
