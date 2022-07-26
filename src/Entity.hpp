#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>

namespace VolE
{
    class Entity
    {
    private:
    typedef std::uint32_t EntityType;
    const EntityType MAX_ENTITIES = 5000; // manually set how many entities to generate

    const char* mName{};
    bool mAlive = true;


    public:
    // == CONSTRUCTOR/DESTRUCTOR ==
    Entity();
    ~Entity();

    // == ACCESSOR FUNCTIONS ==
    bool getStatus();
    const char* getName();

    // == MAIN FUNCTIONS == 
    void updateEntity(const float& dt);
    void renderEntity(sf::RenderTarget* targetWin);

    };
}