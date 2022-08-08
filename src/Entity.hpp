#pragma once

#include "Component.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Component;

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
void renderObj(sf::RenderTarget* targetWin);

};
