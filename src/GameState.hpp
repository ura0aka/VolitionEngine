#pragma once

#include "State.hpp"

namespace VolE
{
    class GameState : public State
    {
    private:

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