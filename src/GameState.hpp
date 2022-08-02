#pragma once

#include "State.hpp"
#include "Entity.hpp"
#include "Component.hpp"
#include "EntityManager.hpp"
#include "ShapeComponent.hpp"
#include "LifeTimeComponent.hpp"
#include "KillComponent.hpp"


// game state class where everything will happen
namespace VolE
{
    class GameState : public State
    {
    private:

    // == MANAGERS ==
    VolE::EntityManager e_Manager;
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