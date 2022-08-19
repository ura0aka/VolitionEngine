#include "EntityManager.hpp"
#include <iostream>

// == CONSTRUCTOR/DESTRUCTOR ==
EntityManager::EntityManager() {}
EntityManager::~EntityManager() {}

// == ENTITY MANAGER FUNCTION(S) ==
Entity& EntityManager::addEntity()
{
    // 1. allocate new entity object on the heap
    Entity* entity{new Entity{*this}};
    // 2. wrap regular pointer to a smart pointer
    std::unique_ptr<Entity> uE_ptr{entity};
    // 3. emplace into container
    mEntityContainer.emplace_back(std::move(uE_ptr));

    return *entity;
}

// == GROUP MANAGEMENT ==
void EntityManager::addToGroup(Entity* entity, GroupID group)
{
    mGroupedEntities[group].emplace_back(entity);
}

std::vector<Entity*>& EntityManager::getEntitiesByGroup(GroupID group)
{
    return mGroupedEntities[group];
}

// == MAIN FUNCTIONS ==
void EntityManager::refreshManager()
{
    for (auto i(0u); i < maxGroups; ++i)
    {
        auto& eV{ mGroupedEntities[i] };

        eV.erase
        (std::remove_if(eV.begin(), eV.end(),
            [i](Entity* entity)
            {
                return !entity->isAlive() || !entity->hasGroup(i);
            }),
            eV.end());
    }
    // remove all dead entities from mEntityContainer (see: https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom)
    // 1. std::remove_if will pass each entity to lambda
    // 2. lambda function checks if the entity is alive
    // 3. if true, remove dead entity
    mEntityContainer.erase
    (std::remove_if(mEntityContainer.begin(), mEntityContainer.end(),
        [](const std::unique_ptr<Entity>& entity)
        {
            return !entity->isAlive();
        }),
        mEntityContainer.end());
}

void EntityManager::updateManager(const float& dt)
{
    // update all entities in container
    for(auto& entity : mEntityContainer)
    {
        entity->updateObj(dt);
    }
}

void EntityManager::renderManager(sf::RenderTarget* targetWin)
{
    // render all entities in container
    for(auto& entity : mEntityContainer)
    {
        entity->renderObj(targetWin);
    }
}

void Entity::addGroup(GroupID group) noexcept
{
    mGroupBitset[group] = true;
    mManager.addToGroup(this, group);
}

