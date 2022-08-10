#include "Game.hpp"


// == For testing ==
std::default_random_engine gen;
std::uniform_real_distribution<float> randPosx(0.0f, 500.0f);
std::uniform_real_distribution<float> randPosy(0.0f, 500.0f);
std::uniform_int_distribution<int> randColorRed(0,255);
std::uniform_int_distribution<int> randColorGreen(0,255);
std::uniform_int_distribution<int> randColorBlue(0,255); 


// == COMPONENTS ==

struct CounterComponent : Component
{
    float counter;
    void updateComponent(const float& dt) override
    {
        counter += dt;
    }
};

struct ShapeComponent : Component
{
    sf::RectangleShape mShape;
    ShapeComponent()
    {
        mShape.setFillColor(sf::Color(randColorRed(gen),randColorGreen(gen),randColorBlue(gen),255));
        mShape.setSize(sf::Vector2f(10.0f,10.0f));
        mShape.setPosition(randPosx(gen),randPosy(gen));
    }
    const float getPos()
    {
        return mShape.getPosition().y;
    }
    void updateComponent(const float& dt)
    {
        //mShape.move(0.0f, 200.0f * dt);
    }
    void renderComponent(sf::RenderTarget* targetWin) override
    {
        targetWin->draw(this->mShape);
    }
    
};

struct KillComponent : Component
{
    CounterComponent* cCounter;
    ShapeComponent* cShape;
    void initComponent() override
    {
        cCounter = &mEntity->getComponent<CounterComponent>();
        cShape = &mEntity->getComponent<ShapeComponent>();
    }
    void updateComponent(const float& dt) override
    {
        if(cCounter->counter >= 2) mEntity->destroyObj();
    }
};

struct PositionComponent : Component
{
    sf::Vector2f mPos;
    PositionComponent() = default;
    PositionComponent(const sf::Vector2f& position)
        :mPos{position} {}
    
    float posX() const noexcept
    {
        return mPos.x;
    }

    float posY() const noexcept
    {
        return mPos.y;
    }
};