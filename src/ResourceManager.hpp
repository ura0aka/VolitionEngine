#pragma once

#include <map>
#include <memory>
#include <string>
#include <iostream>
#include "SFML/Graphics/Texture.hpp"

class ResourceManager
{
private:
std::map<std::string,std::unique_ptr<sf::Texture>> mTexturePtrMap;
std::map<std::string, sf::Texture*> mTextureMap;

void manageTexture(std::string filename, sf::Texture* texture)
{
    std::unique_ptr<sf::Texture> u_TexturePtr{texture};
    mTextureMap[filename] = texture;
    mTexturePtrMap[filename] = std::move(u_TexturePtr);
}

sf::Texture* getTexture(std::string filename)
{
    // iterate through entire map and return corresponding texture
    auto mapIt = mTextureMap.find(filename);
    if(mapIt == mTextureMap.end())
    {
        std::cout << "Texture not found. \n";
        return nullptr;
    }
    std::cout << "1 texture found, loading... \n";
    return mapIt->second;
}

public:
ResourceManager() {}
~ResourceManager() {}

const sf::Texture& loadTexture(std::string filename)
{
    sf::Texture* managedTexture = getTexture(filename);
    if(managedTexture != nullptr)
    {
        return *managedTexture;
    }

    sf::Texture* temp_t = new sf::Texture;
    assert(temp_t->loadFromFile(filename));
    manageTexture(filename, temp_t);
    return *temp_t; 
}

};