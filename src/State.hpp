#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <stack>
#include <map>

// parent class for different states

class State
{
protected:
// == WINDOW VARIABLES ==
sf::RenderWindow* mWindow;

sf::Vector2i mMousePosScreen;
sf::Vector2i mMousePosWin;
sf::Vector2f mMousePosView;


// == RESOURCES ==
std::vector<sf::Texture*> mTextureContainer;

// == LOGIC ==
bool mQuitState;

public:
// == CONSTRUCTOR/DESTRUCTOR ==
State(sf::RenderWindow* Win);
virtual ~State();

// == ACCESSOR FUNCTIONS ==
const bool getEndState() const;

// == MAIN FUNCTIONS ==
virtual void checkEndState(); 

virtual void cleanUpState() = 0;
virtual void updateMousePositions();
virtual void updateKeyInputs() = 0;
virtual void updateState(const float& dt) = 0;
virtual void renderState(sf::RenderTarget* targetWin = nullptr) = 0;

};