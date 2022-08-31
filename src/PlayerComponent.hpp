#include "Component.hpp"


// separate player component with all of its unique sub-components
struct PlayerComponent : Component
{
    // sf::RectangleShape pSprite;
    sf::Vector2f pSize{10.0f,10.0f};
    sf::Vector2f pMovVelocity{200.0f, 200.0f};
    sf::Vector2f pPos;
    sf::Color pColor{sf::Color::Green};

    sf::Texture pTexture;
    sf::Sprite pSprite;

    PlayerComponent(sf::Vector2f pos, sf::Texture texture) : pPos{pos}, pTexture{texture}
    {
        pSprite.setScale(0.2f,0.2f);
        pSprite.setPosition(pPos);
        // pSprite.setFillColor(pColor);
        pSprite.setTexture(pTexture);
    }

    
    void updateInput(const float& dt)
    {
        // keyboard input (player movement)
        // forward (W)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->pSprite.move(0.0f, dt * -(this->pMovVelocity.y));
        }
        // backwards (S)
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            this->pSprite.move(0.0f, dt * this->pMovVelocity.y);
        }
        // left (A)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->pSprite.move(-(dt * this->pMovVelocity.x), 0.0f);
        }
        // right (D)
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->pSprite.move(dt * this->pMovVelocity.x, 0.0f);
        } 
    }


    void updateComponent(const float& dt) override
    {
        this->updateInput(dt);
    }

    void renderComponent(sf::RenderTarget* targetWin) override
    {
        targetWin->draw(this->pSprite);
    }

    float leftX() const noexcept { return pSprite.getGlobalBounds().left; };
    float rightX() const noexcept { return pSprite.getGlobalBounds().left + pSprite.getGlobalBounds().width; };
    float topY() const noexcept { return pSprite.getGlobalBounds().top; };
    float bottomY() const noexcept { return pSprite.getGlobalBounds().top + pSprite.getGlobalBounds().height; };
    float heightY() const noexcept { return pSprite.getGlobalBounds().height; };
    float widthX() const noexcept { return pSprite.getGlobalBounds().width; };
};