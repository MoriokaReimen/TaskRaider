#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace GUI
{

class ResourceManager
{
    std::unordered_map<std::string, sf::Font> fonts_;
    std::unordered_map<std::string, sf::Texture> textures_;
    std::unordered_map<std::string, std::string> texts_;

public:
    ResourceManager();
    void loadFont(const std::string &path, const std::string &name);
    void loadTexture(const std::string &path, const std::string &name);
    void loadText(const std::string &path, const std::string &name);
    void freeFont(const std::string &name);
    void freeTexture(const std::string &name);
    void freeText(const std::string &name);
    void freeFont();
    void freeTexture();
    void freeText();
    void free();
    sf::Font &getFont(const std::string &name);
    sf::Texture &getTexture(const std::string &name);
    std::string &getText(const std::string &name);
};

inline ResourceManager resource;

}; // namespace GUI