#pragma once

#include "State.hpp"
#include "Entity.hpp"
#include "Component.hpp"
#include "EntityManager.hpp"

#include <random>

namespace VolE
{

// == For testing ==
std::default_random_engine gen;
std::uniform_real_distribution<float> randPosx(0.0f, 500.0f);
std::uniform_real_distribution<float> randPosy(0.0f, 500.0f);
std::uniform_int_distribution<int> randColorRed(0,255);
std::uniform_int_distribution<int> randColorGreen(0,255);
std::uniform_int_distribution<int> randColorBlue(0,255); 

EntityManager manager;

// == COMPONENTS ==
struct CounterComponent : Component
{
    float counter;
    void updateComponent(const float& dt) override
    {
        counter += dt;
        //std::cout << counter << std::endl;
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
        mShape.move(0.0f, 200.0f * dt);
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
}


// game state class where everything will happen
namespace VolE
{
    class GameState : public State
    {
    private:

    // == MANAGERS ==
    
    // == COMPONENTS ==

    // == RESOURCES ==

    // == GAME OBJECTS ==
    
    // == INITIALIZER FUNCTIONS ==

    public:
    // == CONSTRUCTOR/DESTRUCTOR ==
    GameState(sf::RenderWindow* Win);
    virtual ~GameState();

    // == MAIN FUNCTIONS ==
    void cleanUpState() override;
    void updateKeyInputs() override;
    void updateState(const float& dt) override;
    void renderState(sf::RenderTarget* targetWin) override;
    };
}