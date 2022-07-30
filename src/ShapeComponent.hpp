#pragma once

#include "Component.hpp"

#include <random>

namespace VolE
{
    std::default_random_engine gen;
    std::uniform_real_distribution<float> randPosx(0.0f,500.0f);
    std::uniform_real_distribution<float> randPosy(0.0f,500.0f);

    class ShapeComponent : Component
    {
        private:
        sf::RectangleShape mShape{};

        public:
        // == CONSTRUCTOR/DESTRUCTOR
        ShapeComponent()
        {
            // simply for testing purposes
            mShape.setFillColor(sf::Color::Cyan);
            mShape.setSize(sf::Vector2f(100.0f,100.0f));
            mShape.setPosition(randPosx(gen),randPosy(gen));
        }

        ~ShapeComponent()
        {

        }

        // == MAIN FUNCTIONS ==
        void updateComponent(const float& dt) override
        {

        }

        void renderComponent(sf::RenderTarget* targetWin) override
        {
            targetWin->draw(this->mShape);
        }
    };
}