#include <ResourceManager.hpp>
#include <exception>
#include <sstream>

namespace GUI
{
ResourceManager::ResourceManager()
    : fonts_{},
      textures_{}
{
}

void ResourceManager::loadFont(const std::string &path, const std::string &name)
{
    sf::Font font;
    if (font.loadFromFile(path))
    {
        fonts_[name] = font;
    }
    else
    {
        std::stringstream ss;
        ss << "Failed to load Font: " << path;
        throw std::runtime_error(ss.str());
    }
}

void ResourceManager::loadTexture(const std::string &path, const std::string &name)
{
    sf::Texture texture;
    if (texture.loadFromFile(path))
    {
        textures_[name] = texture;
    }
    else
    {
        std::stringstream ss;
        ss << "Failed to load Texture: " << path;
        throw std::runtime_error(ss.str());
    }
}

void ResourceManager::freeFont(const std::string &name)
{
    fonts_.erase(name);
}

void ResourceManager::freeTexture(const std::string &name)
{
    textures_.erase(name);
}

void ResourceManager::freeFont()
{
    fonts_.clear();
}

void ResourceManager::freeTexture()
{
    textures_.clear();
}

void ResourceManager::free()
{
    freeTexture();
    freeFont();
}

sf::Font &ResourceManager::getFont(const std::string &name)
{
    return fonts_[name];
}

sf::Texture &ResourceManager::getTexture(const std::string &name)
{
    return textures_[name];
}

}; // namespace GUI