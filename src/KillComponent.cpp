#include "KillComponent.hpp"

VolE::KillComponent::KillComponent(LifeTimeComponent& mCounter)
    :cCounter(mCounter) {}

void VolE::KillComponent::updateComponent(const float& dt)
{
    if(cCounter.mCounter >= 100)
    {
        VolE::Component::mEntity->destroyObj();
    }     
}