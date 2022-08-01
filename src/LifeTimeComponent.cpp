#include "LifeTimeComponent.hpp"

void VolE::LifeTimeComponent::updateComponent(const float& dt)
{
    ++mCounter * dt;
    std::cout << mCounter << '\n';
}