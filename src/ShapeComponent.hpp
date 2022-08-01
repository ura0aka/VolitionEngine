#pragma once

#include "Component.hpp"

#include <random>

namespace VolE
{


    class ShapeComponent : Component
    {
        private:
        sf::RectangleShape mShape{};



        public:

        // == CONSTRUCTOR/DESTRUCTOR ==
        ShapeComponent();

        ~ShapeComponent();

        // == MAIN FUNCTIONS ==
        void updateComponent(const float& dt) override;

        void renderComponent(sf::RenderTarget* targetWin) override;
    };
}