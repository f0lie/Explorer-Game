#include "include/TextureManager.h"

void TextureManager::loadTexture(const std::string &name, const std::string &filename)
{
    auto tex = std::make_unique<sf::Texture>();
    tex->loadFromFile(filename);

    m_textures[name] = std::move(tex);
}

sf::Texture &TextureManager::getRef(const std::string &texture)
{
    return *m_textures.at(texture);
}