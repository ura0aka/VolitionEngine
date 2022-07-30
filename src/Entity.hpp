#pragma once

#include <Component.hpp>

#include <SFML/Graphics.hpp>

#include <cstdint>

namespace VolE
{
    class Component;
    
    class Entity
    {
    private:
    typedef std::uint32_t EntityType;
    const EntityType MAX_ENTITIES = 5000; // manually set how many entities to generate

    const char* mName{};
    bool mAlive = true;
    std::vector<std::unique_ptr<Component>> mComponentsContainer{};


    public:
    // == CONSTRUCTOR/DESTRUCTOR ==
    Entity();
    virtual ~Entity();

    // == ACCESSOR FUNCTIONS ==
    bool isAlive() const;
    const char* getName();

    // == MAIN FUNCTIONS ==
    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs);

    void destroyObj();
    void updateObj(const float& dt);
    void renderObj(sf::RenderTarget* targetWin);

    };
}