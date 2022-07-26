#pragma once

#include "State.hpp"


// game state class where everything will happen
namespace VolE
{
    class GameState : public State
    {
    private:
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