#pragma once 

#include "Entity.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace VolE
{
    class Entity;

    // == BASE COMPONENT CLASS ==
    class Component
    {
    private:

    // component classes will have:
    // *some data
    // *update functions
    // *render functions

    public:
    Entity* mEntity{nullptr};

    // == CONSTRUCTOR/DESTRUCTOR ==
    Component();
    virtual ~Component(); 
    virtual void initComponent();

    // == ACCESSOR FUNCTIONS ==
    void setOwnership(Entity* eOwner)
    {
        this->mEntity = eOwner;
    }

    // == MAIN FUNCTIONS ==
    virtual void updateComponent(const float& dt);
    virtual void renderComponent(sf::RenderTarget* targetWin);

    };
}