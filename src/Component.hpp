#pragma once 

#include "Entity.hpp"

namespace VolE
{
    class Entity;


    // this is the base component class, other game component
    // classes will inherit from this
    class Component
    {
    private:

    // component classes will have:
    // *some data
    // *update function
    // *render function

    public:
    Entity* mEntity{nullptr};
    // == CONSTRUCTOR/DESTRUCTOR ==
    Component();
    virtual ~Component(); 

    // == MAIN FUNCTIONS ==
    virtual void updateComponent(const float& dt);
    virtual void renderComponent(sf::RenderTarget* targetWin);

    };
}