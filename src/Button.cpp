#include "Button.hpp"

Button::Button(float x, float y, float width, float height,
       sf::Font* font, std::string text,
       sf::Color idle, sf::Color hover, sf::Color pressed)
{

    this->buttonState = IDLE;

    this->mButtonShape.setSize(sf::Vector2f(width ,height));
    this->mButtonShape.setPosition(sf::Vector2f(x,y));

    this->mFont = font;
    this->mText.setFont(*this->mFont);
    this->mText.setString(text);
    this->mText.setFillColor(sf::Color::White);
    this->mText.setCharacterSize(12);
    this->mText.setPosition(
        this->mButtonShape.getPosition().x + (this->mButtonShape.getGlobalBounds().width / 2.0f) - this->mText.getGlobalBounds().width / 2.0f,
        this->mButtonShape.getPosition().y + (this->mButtonShape.getGlobalBounds().height / 2.0f) - this->mText.getGlobalBounds().height / 2.0f
    );

    this->mIdleColor = idle;
    this->mHoverColor = hover;
    this->mPressedColor = pressed;

    this->mButtonShape.setFillColor(this->mIdleColor);

}

Button::~Button()
{

}

const bool Button::isPressed() const
{
    if(this->buttonState == PRESSED) { return true; }
    else { return false; }
}

// == MAIN FUNCTIONS ==
void Button::updateButton(const sf::Vector2f mousePos)
{
    // check if mouse is hovering over the button
    this->buttonState = IDLE;
    if(this->mButtonShape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = HOVER;

        // check if button is pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonState = PRESSED;
        }
    }

    switch (this->buttonState)
    {
        case(IDLE):
        {
            this->mButtonShape.setFillColor(this->mIdleColor);
            break;
        }
        case(HOVER):
        {
            this->mButtonShape.setFillColor(this->mHoverColor);
            break;
        }
        case(PRESSED):
        {
            this->mButtonShape.setFillColor(this->mPressedColor);
            break;
        }
        default:
        {
            break;
        }
    }
}

void Button::renderButton(sf::RenderTarget* targetWin)
{
    targetWin->draw(this->mButtonShape);
    targetWin->draw(this->mText);
     
}