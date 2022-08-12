#include "Game.hpp"


// == For testing ==
std::default_random_engine gen;
std::uniform_real_distribution<float> randPosx(0.0f, 500.0f);
std::uniform_real_distribution<float> randPosy(0.0f, 500.0f);
std::uniform_int_distribution<int> randColorRed(0,255);
std::uniform_int_distribution<int> randColorGreen(0,255);
std::uniform_int_distribution<int> randColorBlue(0,255); 


// == COMPONENTS ==
struct PositionComponent : Component
{
    sf::Vector2f mPos;
    PositionComponent(sf::Vector2f position):mPos{position} {}

    float x() const noexcept { return mPos.x; }
    float y() const noexcept { return mPos.y; }
};


struct PhysicsComponent : Component
{
    PositionComponent* mCPos{nullptr};
    sf::Vector2f mVel;

    PhysicsComponent() = default;

    PhysicsComponent(sf::Vector2f velocity)
        :mVel{velocity} {}

    void initComponent() override
    {
        mCPos = &mEntity->getComponent<PositionComponent>();
    }

    void updateComponent(const float& dt) override
    {
        mCPos->mPos += dt * mVel;
    }


    float x() const noexcept { return mCPos->x(); };
    float y() const noexcept { return mCPos->y(); };

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


constexpr float playerVelocity{200.0f};

struct MovementComponent : Component
{
    PositionComponent* mPos{nullptr};
    PhysicsComponent* mPhys{nullptr};
    ShapeComponent* mShape{nullptr};

    void initComponent() override
    {
        mPos = &mEntity->getComponent<PositionComponent>();
        mPhys = &mEntity->getComponent<PhysicsComponent>();
        mShape = &mEntity->getComponent<ShapeComponent>();
    }

    void updateComponent(const float& dt) override
    {
        // keyboard input (player movement)
        // forward (W)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            //mShape->mShape.move(0.0f, dt * -(mPhys->mVel.y));
            mPhys->mVel.y = -playerVelocity;
        }
        // backwards (S)
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            //mShape->mShape.move(0.0f, dt * mPhys->mVel.y);
            mPhys->mVel.y = playerVelocity;
        }
        else
        {
            mPhys->mVel.y = 0.0f;
        }
        // left (A)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            //mShape->mShape.move(dt * -(mPhys->mVel.x), 0.0f);
            mPhys->mVel.x = -playerVelocity;
        }
        // right (D)
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            //mShape->mShape.move(dt * mPhys->mVel.x, 0.0f);
            mPhys->mVel.x = playerVelocity;
        }
        else
        {
            mPhys->mVel.x = 0.0f;
        }
    }

};




