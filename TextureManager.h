#ifndef LEGEND_OF_THE_SWAMP_TEXTUREMANAGER_H
#define LEGEND_OF_THE_SWAMP_TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <memory>

class TextureManager
{
public:
    // Add a texture from a file
    void loadTexture(const std::string& name, const std::string& filename);

    // Translate an id into a reference
    sf::Texture& getRef(const std::string& texture);
private:
    // Array of textures that holds ownership
    std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
};


#endif //LEGEND_OF_THE_SWAMP_TEXTUREMANAGER_H
