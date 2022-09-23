#pragma once

#include "State.hpp"
#include "Button.hpp"

class MainMenuState : public State
{

private:

// == RESOURCES ==
Button* mMMButton;
sf::Font mFont;

std::map<std::string, Button*> mButtonContainer;

// == INITIALIZER FUNCTIONS ==
void initFont();
void initButtons();

public:
// == CONSTRUCTOR/DESTRUCTOR ==
MainMenuState(sf::RenderWindow* Win);
virtual ~MainMenuState();

// == MAIN FUNCTIONS ==
void cleanUpState() override;
void updateKeyInputs() override;
void checkEndState() override;
void updateButtons();
void updateState(const float& dt) override;
void renderButtons(sf::RenderTarget* targetWin);
void renderState(sf::RenderTarget* targetWin) override;


};