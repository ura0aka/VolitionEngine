#pragma once

#include "Component.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

class Component;

class Entity
{
private:
bool mAlive{true};
std::vector<std::unique_ptr<Component>> mComponentsContainer{};

ComponentArray mComponentArray {}; // stores pointers to its components
ComponentBitset mComponentBitset {}; // stores the ID of a particular component

public:
// == DESTRUCTOR ==
~Entity();

// == COMPONENT MANAGER FUNCTIONS ==
template<typename T>
bool hasComponent() const
{
    // check if entity possesses a component of given type 'T'
    // bitset returns (true/false) of given unique ID at index
    return mComponentBitset[getComponentTypeID<T>()];
}

template<typename T, typename... TArgs>
T& addComponent(TArgs&&... mArgs)
{
    assert(!hasComponent<T>() && "ERROR: Entity already owns this component. \n");

    // 1. allocate new component of type <T>, 
    T* component(new T(std::forward<TArgs>(mArgs)...));
    // 2. components entity owner is set like so
    component->setOwnership(this);
    // 3. wrap the regular pointer into a smart pointer
    std::unique_ptr<Component> uC_Ptr{component};
    // 4. store the component ptr in our container
    mComponentsContainer.emplace_back(std::move(uC_Ptr));

    // add a component of type 'T' to array at given index->(generated unique ID)
    mComponentArray[getComponentTypeID<T>()] = component;
    // set component's bitset signature 
    mComponentBitset[getComponentTypeID<T>()] = true;

    std::cout << "Added component" << std::endl; 
    // Component::initComponent() (for better component composition)
    component->initComponent();
    // return reference (so it's not lost to the container's ownership) to the component
    return *component;
}

template<typename T>
T& getComponent() const
{
    // retrieve pointer to component of given type 'T' from mComponentArray
    assert(hasComponent<T>() && "ERROR: Component does not exist. \n");
    auto ptr{mComponentArray[getComponentTypeID<T>()]};
    return *static_cast<T*>(ptr); 
}

// == ACCESSOR FUNCTIONS ==
bool isAlive() const;
void destroyObj();

// == MAIN FUNCTIONS ==
void updateObj(const float& dt);
void renderObj(sf::RenderTarget* targetWin);

};
