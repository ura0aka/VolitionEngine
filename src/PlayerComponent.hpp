#include "Component.hpp"
#include "AnimationComponent.hpp"


// separate player component with all of its unique sub-components
struct PlayerComponent : Component
{
    enum class AnimationIndex
    {
        Up,
        Down,
        Left,
        Right,
        Idle,
        maxCount
    };

    sf::Vector2f pSize{10.0f,10.0f};
    sf::Vector2f pMovVelocity{210.0f, 210.0f};
    sf::Vector2f pPos;
    //sf::RectangleShape pSprite;
    //sf::Texture pTexture;
    sf::Sprite pSprite;
    AnimationComponent pAnimations[int(AnimationIndex::maxCount)];
    AnimationIndex pCurrAnimation = AnimationIndex::Down;
    
    PlayerComponent(sf::Vector2f pos) 
        : pPos{ pos }
    {
        //pSprite.setFillColor(pColor);
        //pSprite.setSize(pSize);
        //pSprite.setTexture(pTexture);
   
        //pSprite.setTexture(pTexture);
        pSprite.setTextureRect({0,0,32,32});
        pAnimations[int(AnimationIndex::Up)] = AnimationComponent(32, 0, 32, 32);
        pAnimations[int(AnimationIndex::Down)] = AnimationComponent(32, 32, 32, 32);
        pAnimations[int(AnimationIndex::Left)] = AnimationComponent(32, 64, 32, 32);
        pAnimations[int(AnimationIndex::Right)] = AnimationComponent(32, 96, 32, 32);
        pSprite.setScale(2,2);

    }

    
    void updateInput(const float& dt)
    {
        // keyboard input (player movement)
        // forward (W)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->pCurrAnimation = AnimationIndex::Up;
            this->pSprite.move(0.0f, dt * -(this->pMovVelocity.y));
        }
        // backwards (S)
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            this->pCurrAnimation = AnimationIndex::Down;
            this->pSprite.move(0.0f, dt * this->pMovVelocity.y);
        }
        // left (A)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->pCurrAnimation = AnimationIndex::Left;
            this->pSprite.move(-(dt * this->pMovVelocity.x), 0.0f);
        }
        // right (D)
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->pCurrAnimation = AnimationIndex::Right;
            this->pSprite.move(dt * this->pMovVelocity.x, 0.0f);
        } 
    }

    void updateSpriteAnimation(const float& dt)
    {
        pAnimations[int(pCurrAnimation)].updateAnimation(dt);
        pAnimations[int(pCurrAnimation)].animateSprite(this->pSprite);
    }

    void updateComponent(const float& dt) override
    {
        this->updateSpriteAnimation(dt);
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