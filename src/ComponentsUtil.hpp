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

struct PositionComponent : Component
{
    sf::Vector2f mPos;
    PositionComponent(sf::Vector2f position):mPos{position} {}

    float x() const noexcept {return mPos.x;}
    float y() const noexcept {return mPos.y;}
};


struct ShapeComponent : Component
{
    PositionComponent* mShapePos{nullptr};
    sf::RectangleShape mShape;
    sf::Vector2f mSize;
    sf::Color mColor;
    
    ShapeComponent() = default;

    ShapeComponent(sf::Vector2f size,sf::Color color)
        :mSize{size},mColor{color} {} 

    void initComponent() override
    {
        mShapePos = &mEntity->getComponent<PositionComponent>();
        mShape.setSize(mSize);
        mShape.setFillColor(mColor);
    }

    void updateComponent(const float& dt) override
    {
        mShape.setPosition(mShapePos->mPos);
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

