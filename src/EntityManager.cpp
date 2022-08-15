#include "EntityManager.hpp"
#include <iostream>

// == CONSTRUCTOR/DESTRUCTOR ==
EntityManager::EntityManager() {}
EntityManager::~EntityManager() {}

// == ENTITY MANAGER FUNCTION(S) ==
Entity& EntityManager::addEntity()
{
    // 1. allocate new entity object on the heap
    Entity* entity{new Entity(*this)};
    // 2. wrap regular pointer to a smart pointer
    std::unique_ptr<Entity> uE_ptr{entity};
    // 3. emplace into container
    mEntityContainer.emplace_back(std::move(uE_ptr));

    return *entity;
}

// == GROUP MANAGEMENT ==
void Entity::addGroup(GroupID group) noexcept
{
    // when an entity is created, we set the bitset of the group to 1
    // EntityManager adds entity to the array of entity vectors (by calling EntityManager::addToGroup)
    mGroupBitset[group] = true;
    mManager.addToGroup(this, group);
}

void EntityManager::addToGroup(Entity* entity, GroupID group)
{
    mGroupedEntities[group].emplace_back(entity);
}

std::vector<Entity*>& EntityManager::getEntitiesByGroup(GroupID group)
{
    // return entity that belongs to a specific group from the array
    return mGroupedEntities[group];
}

// == MAIN FUNCTIONS ==
void EntityManager::updateManager(const float& dt)
{
    // remove all dead entities or entities without the right group from the group array
    // once again using the erase-remove idiom
    for(int i {0}; i < maxGroups; ++i)
    {
        auto& entity_vec{mGroupedEntities[i]};
        entity_vec.erase
        (std::remove_if(entity_vec.begin(), entity_vec.end(),
        [i](Entity* entity)
        {
            return !entity->isAlive() || !entity->hasGroup(i);
        }),
        entity_vec.end());
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

