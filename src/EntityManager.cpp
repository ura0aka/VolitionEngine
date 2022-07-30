#include "EntityManager.hpp"

// == CONSTRUCTOR/DESTRUCTOR ==
VolE::EntityManager::EntityManager()
{

}
VolE::EntityManager::~EntityManager()
{

}

VolE::Entity& VolE::EntityManager::addEntity()
{
    // 1. allocate new entity object on the heap
    Entity* entity{new Entity{}};
    // 2. wrap regular pointer to a smart pointer
    std::unique_ptr<Entity> uE_ptr{entity};
    // 3. emplace into container
    mEntityContainer.emplace_back(std::move(uE_ptr));

    return *entity;
}

// == MAIN FUNCTIONS ==
void VolE::EntityManager::updateManager(const float& dt)
{
    // remove all dead entities from mEntityContainer
    // 1. we have an iterator return a value in removedEntity
    // 2. using the lambda, it returns a dead entity into removedEntity
    // 3. erase dead entity
    auto removedEntity{std::remove_if(mEntityContainer.begin(), mEntityContainer.end(),
    [](const std::unique_ptr<Entity>& entity)
        {
            return !entity->isAlive();
        })};
    if (removedEntity == mEntityContainer.end())
    {
        mEntityContainer.erase(removedEntity);
    }

    // update all entities in container
    for(auto& entity : mEntityContainer)
    {
        entity->updateObj(dt);
    }
}

void VolE::EntityManager::renderManager(sf::RenderTarget* targetWin)
{
    // render all entities in container
    for(auto& entity : mEntityContainer)
    {
        entity->renderObj(targetWin);
    }
}

