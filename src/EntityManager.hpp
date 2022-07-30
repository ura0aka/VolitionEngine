#pragma once

#include "Entity.hpp"

namespace VolE
{
    class EntityManager
    {
    private:
    std::vector<std::unique_ptr<Entity>> mEntityContainer {};

    public:
    // == CONSTRUCTOR/DESTRUCTOR ==
    EntityManager();
    ~EntityManager();

    Entity& addEntity();

    // == MAIN FUNCTIONS ==
    void updateManager(const float& dt);
    void renderManager(sf::RenderTarget* targetWin);



    };
}
