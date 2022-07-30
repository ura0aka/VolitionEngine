#include "Entity.hpp"

// == CONSTRUCTOR/DESTRUCTOR
VolE::Entity::Entity()
{

}

VolE::Entity::~Entity()
{

}

// == ACCESSOR FUNCTIONS ==
bool VolE::Entity::isAlive() const
{
    return this->mAlive;
}

const char* VolE::Entity::getName()
{
    return this->mName;
}

// == COMPONENT MANAGER SECTION == 

// takes in T(specified component type) <T>
// takes in any amount of specified arguments that will be forwarded to the Component constructor <TArgs>
template<typename T, typename... TArgs>
T& VolE::Entity::addComponent(TArgs&&... mArgs)
{
    // 1. allocate new component of type <T>, 
    T* component(new T(std::forward<TArgs>(mArgs)...));
    // 2. components entity owner is set like so
    component->entity = this;
    // 3. wrap the regular pointer into a smart pointer
    std::unique_ptr<Component> uC_Ptr{component};
    // 4. store the component ptr in our container
    mComponentsContainer.emplace(std::move(uC_Ptr));

    // return reference(so it's not lost to the container's ownership) to the component
    return *component;
}

// == MAIN FUNCTIONS ==
void VolE::Entity::destroyObj()
{
    this->mAlive = false;
}

void VolE::Entity::updateObj(const float& dt)
{
    // will iterate through all the components
    // and update whichever needs to be updated
    for(auto& component : mComponentsContainer)
    {
        component->updateComponent(dt);
    }
}

void VolE::Entity::renderObj(sf::RenderTarget* targetWin)
{
    // will iterate through all the components it possesses
    // and each component will be drawn on target window
    for(auto& component : mComponentsContainer)
    {
        component->renderComponent(targetWin);
    }
}

