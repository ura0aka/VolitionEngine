#include "Game.hpp"


// == For testing ==
std::default_random_engine gen;
std::uniform_real_distribution<float> randPosx(0.0f, 800.0f);
std::uniform_real_distribution<float> randPosy(0.0f, 800.0f);
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

    sf::FloatRect getGlobalBounds()
    {
        return this->mShape.getGlobalBounds();
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


struct PhysicsComponent : Component
{
    PositionComponent* mCPos{nullptr};
    ShapeComponent* mShape{nullptr};
    sf::Vector2f mVel;
    sf::Vector2f mSize;

    PhysicsComponent() = default;

    PhysicsComponent(sf::Vector2f velocity, const sf::Vector2f& size)
        :mVel{velocity} {}

    void initComponent() override
    {
        mCPos = &mEntity->getComponent<PositionComponent>();
        mShape = &mEntity->getComponent<ShapeComponent>();
    }

    void updateComponent(const float& dt) override
    {
        mCPos->mPos += dt * mVel;
    }

    float x() const noexcept { return mCPos->x(); };
    float y() const noexcept { return mCPos->y(); };
    float leftX() const noexcept { return mShape->getGlobalBounds().left; };
    float rightX() const noexcept { return mShape->getGlobalBounds().left + mShape->getGlobalBounds().width; };
    float topY() const noexcept { return mShape->getGlobalBounds().top; };
    float bottomY() const noexcept { return mShape->getGlobalBounds().top + mShape->getGlobalBounds().height; };
    float heightY() const noexcept { return mShape->getGlobalBounds().height; };
    float widthX() const noexcept { return mShape->getGlobalBounds().width; };
    sf::FloatRect ShapeBounds() const noexcept { return mShape->getGlobalBounds(); };
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
            mPhys->mVel.y = -playerVelocity;
        }
        // backwards (S)
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            mPhys->mVel.y = playerVelocity;
        }
        else
        {
            mPhys->mVel.y = 0.0f;
        }
        // left (A)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            mPhys->mVel.x = -playerVelocity;
        }
        // right (D)
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            mPhys->mVel.x = playerVelocity;
        }
        else
        {
            mPhys->mVel.x = 0.0f;
        }
    }

};


template <class T1, class T2>
bool isIntersecting(T1& mObjA, T2& mObjB) noexcept
{
    return mObjA.rightX() >= mObjB.leftX() &&
        mObjA.leftX() <= mObjB.rightX() &&
        mObjA.topY() <= mObjB.bottomY() &&
        mObjA.bottomY() >= mObjB.topY(); 
}

void collisionAABB(Entity& mPlayer, Entity& mNpc)
{
    auto& cPlayer(mPlayer.getComponent<PlayerComponent>());
    auto& cNpc(mNpc.getComponent<PhysicsComponent>());


    if(isIntersecting(cPlayer,cNpc))
    {
        // bottom-side collision
        if (cPlayer.topY() < cNpc.topY() && cPlayer.bottomY() < cNpc.bottomY() &&
            cPlayer.leftX() < cNpc.rightX() && cPlayer.rightX() > cNpc.leftX())
        {
            std::cout << "bottom_collision \n";
            cPlayer.pShape.setPosition(cPlayer.leftX(), cNpc.topY() - cPlayer.heightY());
        }

        // top-side collision
        else if (cPlayer.topY() > cNpc.topY() && cPlayer.bottomY() > cNpc.bottomY() &&
            cPlayer.leftX() < cNpc.rightX() && cPlayer.rightX() > cNpc.leftX())
        {
            std::cout << "top_collision \n";
            cPlayer.pShape.setPosition(cPlayer.leftX(), cNpc.bottomY());
        }

        // right side collision
        else if (cPlayer.leftX() < cNpc.leftX() && cPlayer.rightX() < cNpc.rightX() &&
            cPlayer.topY() < cNpc.bottomY() && cPlayer.bottomY() > cNpc.topY())
        {
            std::cout << "right_collision \n";
            cPlayer.pShape.setPosition(cNpc.leftX() - cPlayer.widthX(), cPlayer.topY());
        }

        else if (cPlayer.leftX() > cNpc.leftX() && cPlayer.rightX() > cNpc.rightX() &&
            cPlayer.topY() < cNpc.bottomY() && cPlayer.bottomY() > cNpc.topY())
        {
            std::cout << "left_collision \n";
            cPlayer.pShape.setPosition(cNpc.rightX(), cPlayer.topY());
        }
    }
}


// FIXME: @line 203 
bool isClicked(Entity& mNpc, sf::RenderWindow* mWin)
{
    sf::Vector2i mMousePosWin; 
    sf::Vector2f mMousePosView;

    mMousePosWin = sf::Mouse::getPosition(*mWin);
    mMousePosView = mWin->mapPixelToCoords(mMousePosWin); //throws exception, cannot access sf::RenderWindow from here it seems ...

    auto& cNpc(mNpc.getComponent<PhysicsComponent>());

    if(cNpc.ShapeBounds().contains(mMousePosView)) { return true; }
    else { return false; }
}

enum VolEGroups : std::uint32_t
{
    Player,
    NPC
};




