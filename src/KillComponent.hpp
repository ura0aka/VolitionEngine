#pragma once

#include "LifeTimeComponent.hpp"

namespace VolE
{
    class KillComponent : Component
    {
    private:
    LifeTimeComponent& cCounter;

    public:
    KillComponent(LifeTimeComponent& mCounter);

    void updateComponent(const float& dt) override;


    };
}