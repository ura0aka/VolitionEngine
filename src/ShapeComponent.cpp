#include "ShapeComponent.hpp"

VolE::ShapeComponent::ShapeComponent()
{
    // simply for testing purposes
    mShape.setFillColor(sf::Color::Cyan);
    mShape.setSize(sf::Vector2f(100.0f,100.0f));
    mShape.setPosition(100.0f,100.0f);
}

VolE::ShapeComponent::~ShapeComponent()
{

}

void VolE::ShapeComponent::updateComponent(const float& dt)
{

}

void VolE::ShapeComponent::renderComponent(sf::RenderTarget* targetWin)
{
    targetWin->draw(this->mShape);
}