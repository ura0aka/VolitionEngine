#pragma once

#include <iostream>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Button
{


private:

bool mPressed;
bool mHover;

sf::RectangleShape mButtonShape;
sf::Font* mFont;
sf::Text mText;

sf::Color mIdleColor;
sf::Color mHoverColor;
sf::Color mActiveColor;


public:
Button(float x, float y, float width, float height,
       sf::Font* font, std::string text,
       sf::Color idle, sf::Color hover, sf::Color active);

~Button();

// == MAIN FUNCTIONS ==
void updateButton(sf::Vector2f mousePos);
void renderButton(sf::RenderTarget* targetWin);

};