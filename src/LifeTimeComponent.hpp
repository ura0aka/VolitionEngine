#pragma once

#include "Component.hpp"

#include <iostream>

namespace VolE
{
    class LifeTimeComponent : Component
    {
    private:

    public:
    float mCounter{0.0f};
    void updateComponent(const float& dt) override;

    };
}