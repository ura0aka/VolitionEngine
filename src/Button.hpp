#pragma once

#include <iostream>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

enum buttonState
{
    IDLE = 0,
    HOVER,
    PRESSED
};


class Button
{

private:

std::uint32_t buttonState;
bool mPressed;
bool mHover;

sf::RectangleShape mButtonShape;
sf::Font* mFont;
sf::Text mText;

sf::Color mIdleColor;
sf::Color mHoverColor;
sf::Color mPressedColor;


public:
Button(float x, float y, float width, float height,
       sf::Font* font, std::string text,
       sf::Color idle, sf::Color hover, sf::Color pressed);

~Button();

const bool isPressed() const;

// == MAIN FUNCTIONS ==
void updateButton(sf::Vector2f mousePos);
void renderButton(sf::RenderTarget* targetWin);

};