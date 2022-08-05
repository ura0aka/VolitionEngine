#pragma once

#include "Component.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <array>
#include <memory>
#include <bitset>
#include <cstdint>
#include <cassert>

namespace VolE
{
    class Component;

    // == COMPONENT ID SYSTEM ==
    using ComponentID = std::uint32_t;
    constexpr std::size_t maxComponents{32};

    using ComponentBitset = std::bitset<maxComponents>;
    using ComponentArray = std::array<Component*, maxComponents>;

    inline ComponentID genUComponentID() noexcept
    {
        // generate a unique id for a component 
        // (this gets called in the getComponentTypeID function -> when Entity::addComponent() is called)
        static ComponentID lastID{0u};
        return lastID++;
    }

    template<typename T> inline ComponentID getComponentTypeID() noexcept
    {
        // for each unique component type, the template will be instanciated
        // only once for each type of component thus, creating a unique ID

        // make sure getComponentTypeID only gets called with 'T' that inherits from the Component class
        // (std::is_base_of provides ::value = TRUE if the derived is part of the given base class)
        static_assert(std::is_base_of<Component, T>::value && "ERROR: T must inherit from base Component class. \n");
        static ComponentID typeID{genUComponentID()};

        // subsequent calls with the same component type will return the same ID
        return typeID;
    }
    
    class Entity
    {
    private:
    bool mAlive{true};
    std::vector<std::unique_ptr<Component>> mComponentsContainer{};

    ComponentArray mComponentArray {}; // stores pointers to its components
    ComponentBitset mComponentBitset {}; // stores the ID of a particular component

    public:
    // == COMPONENT MANAGER FUNCTIONS ==
    template<typename T> bool hasComponent() const;
    template<typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs);
    template<typename T> T& getComponent() const;

    // == ACCESSOR FUNCTIONS ==
    bool isAlive() const;
    void destroyObj();

    // == MAIN FUNCTIONS ==
    void updateObj(const float& dt);
    void renderObj(sf::RenderWindow& targetWin);

    };
}