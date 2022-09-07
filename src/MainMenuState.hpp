#pragma once

#include "State.hpp"

class MainMenuState : public State
{

private:


public:
// == CONSTRUCTOR/DESTRUCTOR ==
MainMenuState(sf::RenderWindow* Win);
virtual ~MainMenuState();

// == MAIN FUNCTIONS ==
void cleanUpState() override;
void updateKeyInputs() override;
void updateMousePositions();
void checkEndState() override;
void updateState(const float& dt) override;
void renderState(sf::RenderTarget* targetWin) override;


};