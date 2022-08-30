#pragma once 


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <array>
#include <memory>
#include <bitset>
#include <cstdint>
#include <cassert>


class Component;
class EntityManager;
class Entity;


// == COMPONENT ID SYSTEM ==
using ComponentID = std::uint32_t;
constexpr std::size_t maxComponents{32};

// == GROUP ID SYSTEM ==
using GroupID = std::uint32_t;
constexpr std::uint32_t maxGroups{32};
using GroupBitset = std::bitset<maxGroups>;

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

// == BASE COMPONENT CLASS ==
class Component
{
public:
Entity* mEntity{nullptr};

// == CONSTRUCTOR/DESTRUCTOR ==
Component();
virtual ~Component(); 
virtual void initComponent();

// == ACCESSOR FUNCTIONS ==
void setOwnership(Entity* eOwner) { this->mEntity = eOwner; }

// == MAIN FUNCTIONS ==
virtual void updateComponent(const float& dt);
virtual void renderComponent(sf::RenderTarget* targetWin);

};
