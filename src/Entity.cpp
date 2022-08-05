#include "Entity.hpp"

// == COMPONENT MANAGER SECTION == 

template<typename T>
bool VolE::Entity::hasComponent() const
{
    // check if entity possesses a component of given type 'T'
    // bitset returns (true/false) of given unique ID at index
    return mComponentBitset[getComponentTypeID<T>()];
}

template<typename T, typename... TArgs>
T& VolE::Entity::addComponent(TArgs&&... mArgs)
{
    assert(!hasComponent<T>() && "ERROR: Entity already owns this component. \n");

    // 1. allocate new component of type <T>, 
    T* component(new T(std::forward<TArgs>(mArgs)...));
    // 2. components entity owner is set like so
    component->setOwnership(this);
    // 3. wrap the regular pointer into a smart pointer
    std::unique_ptr<Component> uC_Ptr{component};
    // 4. store the component ptr in our container
    mComponentsContainer.emplace_back(std::move(uC_Ptr));

    // add a component of type 'T' to array at given index->(generated unique ID)
    mComponentArray[getComponentTypeID<T>()] = component;
    // set component's bitset signature 
    mComponentBitset[getComponentTypeID<T>()] = true;

    // return reference (so it's not lost to the container's ownership) to the component
    return *component;
}

template<typename T>
T& VolE::Entity::getComponent() const
{
    // retrieve pointer to component of given type 'T' from mComponentArray
    assert(hasComponent<T>() && "ERROR: Component does not exist. \n");
    auto ptr{mComponentArray[getComponentTypeID<T>()]};
    return *static_cast<T*>(ptr); 
}
// == ACCESSOR FUNCTIONS ==
bool VolE::Entity::isAlive() const { return this->mAlive; }
void VolE::Entity::destroyObj() { this->mAlive = false; }



// == MAIN FUNCTIONS ==

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

