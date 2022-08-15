#include "Entity.hpp"
// == CONSTRUCTOR/DESTRUCTOR ==
Entity::~Entity() {}



// == ACCESSOR FUNCTIONS ==
bool Entity::isAlive() const { return this->mAlive; }
void Entity::destroyObj() { this->mAlive = false; }

// == MAIN FUNCTIONS ==
void Entity::updateObj(const float& dt)
{
    // will iterate through all the components
    // and update whichever needs to be updated
    for(auto& component : mComponentsContainer)
    {
        component->updateComponent(dt);
    }
}

void Entity::renderObj(sf::RenderTarget* targetWin)
{
    // will iterate through all the components it possesses
    // and each component will be drawn on target window
    for(auto& component : mComponentsContainer)
    {
        component->renderComponent(targetWin);
    }
}

