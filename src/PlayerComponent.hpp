#include "Component.hpp"
#include "ResourceManager.hpp"
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
        IdleUp,
        IdleDown,
        IdleLeft,
        IdleRight,
        maxCount
    };

    sf::Vector2f pSize{ 10.0f,10.0f };
    sf::Vector2f pMovVelocity{ 210.0f, 210.0f };
    sf::Vector2f pPos;

    std::string pFilename{"res/textures/drifter_walk_cycle_full.png"};
    sf::Sprite pSprite;
    AnimationComponent pAnimations[int(AnimationIndex::maxCount)];
    AnimationIndex pPrevAnimation = AnimationIndex::IdleDown;
    AnimationIndex pCurrAnimation = pPrevAnimation;

    
    PlayerComponent(sf::Vector2f pos) 
        : pPos{ pos }
    {
        // while sprite is moving
        pAnimations[int(AnimationIndex::Up)] = AnimationComponent(32, 0, 32, 32, 12, 0.07f, std::move(pFilename));
        pAnimations[int(AnimationIndex::Down)] = AnimationComponent(32, 32, 32, 32, 12, 0.07f, std::move(pFilename));
        pAnimations[int(AnimationIndex::Left)] = AnimationComponent(32, 64, 32, 32, 12, 0.07f, std::move(pFilename));
        pAnimations[int(AnimationIndex::Right)] = AnimationComponent(32, 96, 32, 32, 12, 0.07f, std::move(pFilename));
        // while sprite is idling
        pAnimations[int(AnimationIndex::IdleUp)] = AnimationComponent(0, 0, 32, 32, 1, 10.0f, std::move(pFilename));
        pAnimations[int(AnimationIndex::IdleDown)] = AnimationComponent(0, 32, 32, 32, 1, 10.0f, std::move(pFilename));
        pAnimations[int(AnimationIndex::IdleLeft)] = AnimationComponent(0, 64, 32, 32, 1, 10.0f, std::move(pFilename));
        pAnimations[int(AnimationIndex::IdleRight)] = AnimationComponent(0, 96, 32, 32, 1, 10.0f, std::move(pFilename));
        pSprite.setScale(2,2);
    }

    
    void updateInput(const float& dt)
    {
        // WARNING: these are some of the worst conditional statements ever, but it works -too bad!

        // initially, our character is in an idle state
        if (pPrevAnimation == AnimationIndex::Up)
        {
            this->pCurrAnimation = AnimationIndex::IdleUp;
        }
        else if (pPrevAnimation == AnimationIndex::Down)
        {
            this->pCurrAnimation = AnimationIndex::IdleDown;
        }
        if (pPrevAnimation == AnimationIndex::Left)
        {
            this->pCurrAnimation = AnimationIndex::IdleLeft;
        }
        else if (pPrevAnimation == AnimationIndex::Right)
        {
            this->pCurrAnimation = AnimationIndex::IdleRight;
        }

        // keyboard input (player movement)
        // forward (W)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->pCurrAnimation = AnimationIndex::Up;
            this->pPrevAnimation = pCurrAnimation;
            this->pSprite.move(0.0f, dt * -(this->pMovVelocity.y));
        }
        // backwards (S)
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            this->pCurrAnimation = AnimationIndex::Down;
            this->pPrevAnimation = pCurrAnimation;
            this->pSprite.move(0.0f, dt * this->pMovVelocity.y);
        }
        // left (A)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->pCurrAnimation = AnimationIndex::Left;
            this->pPrevAnimation = pCurrAnimation;
            this->pSprite.move(-(dt * this->pMovVelocity.x), 0.0f);
        }
        // right (D)
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->pCurrAnimation = AnimationIndex::Right;
            this->pPrevAnimation = pCurrAnimation;
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