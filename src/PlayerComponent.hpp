#include "Component.hpp"


// separate player component with all of its unique sub-components
struct PlayerComponent : Component
{
    sf::RectangleShape pShape;
    sf::Vector2f pSize{10.0f,10.0f};
    sf::Vector2f pMovVelocity{200.0f, 200.0f};
    sf::Vector2f pPos;
    sf::Color pColor{sf::Color::Green};

    PlayerComponent(sf::Vector2f pos) : pPos{pos}
    {
        pShape.setSize(pSize);
        pShape.setPosition(pPos);
        pShape.setFillColor(pColor);
    }

    
    void updateInput(const float& dt)
    {
        // keyboard input (player movement)
        // forward (W)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->pShape.move(0.0f, dt * -(this->pMovVelocity.y));
        }
        // backwards (S)
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            this->pShape.move(0.0f, dt * this->pMovVelocity.y);
        }
        // left (A)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->pShape.move(-(dt * this->pMovVelocity.x), 0.0f);
        }
        // right (D)
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->pShape.move(dt * this->pMovVelocity.x, 0.0f);
        } 
    }


    void updateComponent(const float& dt) override
    {
        this->updateInput(dt);
    }

    void renderComponent(sf::RenderTarget* targetWin) override
    {
        targetWin->draw(this->pShape);
    }

    float leftX() const noexcept { return pShape.getGlobalBounds().left; };
    float rightX() const noexcept { return pShape.getGlobalBounds().left + pShape.getGlobalBounds().width; };
    float topY() const noexcept { return pShape.getGlobalBounds().top; };
    float bottomY() const noexcept { return pShape.getGlobalBounds().top + pShape.getGlobalBounds().height; };
    float heightY() const noexcept { return pShape.getGlobalBounds().height; };
    float widthX() const noexcept { return pShape.getGlobalBounds().width; };
};