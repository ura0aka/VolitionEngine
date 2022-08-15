#include "Entity.hpp"
// == CONSTRUCTOR/DESTRUCTOR ==
Entity::Entity(EntityManager& manager) : mManager{manager} {}
Entity::~Entity() {}

// == GROUP MANAGER SECTION == 
bool Entity::hasGroup(GroupID mGroup) const
{
    return mGroupBitset[mGroup];
}
void Entity::deleteGroup(GroupID mGroup) noexcept
{
    mGroupBitset[mGroup] = false;
}

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

