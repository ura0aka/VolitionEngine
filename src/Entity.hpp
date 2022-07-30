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
    virtual ~Entity();

    // == ACCESSOR FUNCTIONS ==
    bool getStatus();
    const char* getName();

    // == MAIN FUNCTIONS == 
    virtual void updateObj(const float& dt);
    virtual void renderObj(sf::RenderTarget* targetWin);

    };
}