#pragma once

#include "State.hpp"

namespace VolE
{
    class GameState : public State
    {
    private:

    public:
    // == CONSTRUCTOR/DESTRUCTOR ==
    GameState();
    virtual ~GameState();

    // == MAIN FUNCTIONS ==
    void updateState(const float& dt) override;
    void renderState(sf::RenderTarget* targetWin) override;
    };
}