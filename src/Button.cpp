#include "Button.hpp"

Button::Button(float x, float y, float width, float height,
       sf::Font* font, std::string text,
       sf::Color idle, sf::Color hover, sf::Color active)
{
    this->mButtonShape.setSize(sf::Vector2f(width ,height));
    this->mButtonShape.setPosition(sf::Vector2f(x,y));

    this->mFont = font;
    this->mText.setFont(*this->mFont);
    this->mText.setString(text);
    this->mText.setFillColor(sf::Color::White);
    this->mText.setCharacterSize(12);
    this->mText.setPosition(
        this->mButtonShape.getPosition().x / 2.0f - this->mText.getGlobalBounds().width / 2.0f,
        this->mButtonShape.getPosition().y / 2.0f - this->mText.getGlobalBounds().height / 2.0f
    );

    this->mIdleColor = idle;
    this->mHoverColor = hover;
    this->mActiveColor = active;

    this->mButtonShape.setFillColor(this->mIdleColor);

}

Button::~Button()
{

}

// == MAIN FUNCTIONS ==
void Button::updateButton(const sf::Vector2f mousePos)
{
    // check if mouse is hovering over the button
    if(this->mButtonShape.getGlobalBounds().contains(mousePos))
    {
        std::cout << "something" << '\n';
    }
}

void Button::renderButton(sf::RenderTarget* targetWin)
{
    targetWin->draw(this->mButtonShape);
}