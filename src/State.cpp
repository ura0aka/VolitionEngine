#include "State.hpp"

// == CONSTRUCTOR/DESTRUCTOR ==
State::State(sf::RenderWindow* Win)
{
    this->mWindow = Win;
    this->mQuitState = false;
}

State::~State()
{

}

// == ACCESSOR FUNCTIONS ==
const bool State::getEndState() const
{
    return mQuitState;
}

// == MAIN FUNCTIONS ==
void State::updateMousePositions()
{
    this->mMousePosScreen = sf::Mouse::getPosition();
    this->mMousePosWin = sf::Mouse::getPosition(*this->mWindow);
    this->mMousePosView = this->mWindow->mapPixelToCoords(sf::Mouse::getPosition(*this->mWindow));
}

void State::checkEndState()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->cleanUpState();
        this->mQuitState = true;
    }
}
