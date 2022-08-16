#pragma once

#include "Entity.hpp"


class Entity;

class EntityManager
{
private:
std::vector<std::unique_ptr<Entity>> mEntityContainer;

public:
// == CONSTRUCTOR/DESTRUCTOR ==
EntityManager();
~EntityManager();

// == ENTITY MANAGER FUNCTION(S) ==
Entity& addEntity();

// == GROUP MANAGEMENT ==
void addToGroup(Entity* entity, GroupID group);

// == MAIN FUNCTIONS ==
void updateManager(const float& dt);
void renderManager(sf::RenderTarget* targetWin);

};

