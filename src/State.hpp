#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <stack>
#include <map>

// parent class for different states

class State
{
private:

protected:
// == WINDOW VARIABLES ==
sf::RenderWindow* mWindow;

sf::Vector2i mMousePosWin;
sf::Vector2f mMousePosView;

// stack of game state stack pointer
std::stack<State*>* mStatesPtr_Stack;

// == LOGIC ==
bool mQuitState;

public:
// == CONSTRUCTOR/DESTRUCTOR ==
State(sf::RenderWindow* Win, std::stack<State*>* States);
virtual ~State();

// == ACCESSOR FUNCTIONS ==
const bool getEndState() const;

// == MAIN FUNCTIONS ==
virtual void checkEndState(); 

virtual void cleanUpState() = 0;
virtual void updateKeyInputs() = 0;
virtual void updateMousePosition();
virtual void updateState(const float& dt) = 0;
virtual void renderState(sf::RenderTarget* targetWin = nullptr) = 0;

};