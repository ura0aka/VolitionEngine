#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>
#include "SFML/Graphics/Texture.hpp"

class ResourceManager
{
public:
    
    // map of shared_ptrs to textures (because they will be shared around by different entities)
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> mTexturePtrMap;
    ResourceManager() {}
    ~ResourceManager() {}

    std::shared_ptr<sf::Texture> getTexture(const std::string& filename)
    {
        // iterate through entire map and return corresponding texture
        const auto mapIt = mTexturePtrMap.find(filename);
        if (mapIt != mTexturePtrMap.end())
        {
            // if texture already exists in the map, return
            return mapIt->second;
        }
        else
        {
            // if texture does not exist yet, insert into the map & return
            auto newTex = std::make_shared<sf::Texture>();
            newTex->loadFromFile(filename);
            mTexturePtrMap.insert({ filename,newTex });
            return newTex;
        }
    }

};