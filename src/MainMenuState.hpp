#pragma once

#include "State.hpp"
#include "Button.hpp"

class MainMenuState : public State
{

private:

// == RESOURCES ==
Button* mMMButton;
sf::Font mFont;

// == INITIALIZER FUNCTIONS ==
void initFont();

public:
// == CONSTRUCTOR/DESTRUCTOR ==
MainMenuState(sf::RenderWindow* Win);
virtual ~MainMenuState();

// == MAIN FUNCTIONS ==
void cleanUpState() override;
void updateKeyInputs() override;
void checkEndState() override;
void updateState(const float& dt) override;
void renderState(sf::RenderTarget* targetWin) override;


};