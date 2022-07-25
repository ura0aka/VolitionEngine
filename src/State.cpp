#include "State.hpp"

// == CONSTRUCTOR/DESTRUCTOR ==
VolE::State::State(sf::RenderWindow* Win)
{
    this->mWindow = Win;
    this->mQuitState = false;
}

VolE::State::~State()
{

}

// == ACCESSOR FUNCTIONS ==
const bool VolE::State::getEndState() const
{
    return mQuitState;
}

// == MAIN FUNCTIONS ==
void VolE::State::checkEndState()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->cleanUpState();
        this->mQuitState = true;
    }
}
