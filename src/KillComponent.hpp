#pragma once

#include "LifeTimeComponent.hpp"

namespace VolE
{
    class KillComponent : Component
    {
    private:
    LifeTimeComponent& cCounter;

    public:
    KillComponent(LifeTimeComponent& mCounter)
        :cCounter(mCounter) {}

    void updateComponent(const float& dt) override
    {
        if(cCounter.mCounter >= 100)
        {
            VolE::Component::mEntity->destroyObj();
        } 
    } 


    };
}