#include "Entity.hpp"

// == CONSTRUCTOR/DESTRUCTOR
VolE::Entity::Entity()
{

}

VolE::Entity::~Entity()
{

}

// == ACCESSOR FUNCTIONS ==
bool VolE::Entity::getStatus()
{
    return this->mAlive;
}

const char* VolE::Entity::getName()
{
    return this->mName;
}

// == MAIN FUNCITONS ==
void VolE::Entity::updateEntity(const float& dt)
{
    // will iterate through all the components
    // and update whichever needs to be updated
}

void VolE::Entity::renderEntity(sf::RenderTarget* targetWin)
{
    // will iterate through all the components it possesses
    // and each component will be drawn on target window

    /*
        for(auto& component : componentarray)
        {
            targetWin->draw(component);
        }
    */
}

