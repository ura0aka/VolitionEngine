#include "State.hpp"

// == CONSTRUCTOR/DESTRUCTOR ==
State::State(sf::RenderWindow* Win, std::stack<State*>* States)
{
    this->mWindow = Win;
    this->mQuitState = false;
    this->mStatesPtr_Stack = States;
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
void State::updateMousePosition()
{
    this->mMousePosWin = sf::Mouse::getPosition(*this->mWindow);
    this->mMousePosView = this->mWindow->mapPixelToCoords(this->mMousePosWin);

    std::cout << "(" << mMousePosView.x << "," << mMousePosView.y << ") \n";
}

void State::checkEndState()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->cleanUpState();
        this->mQuitState = true;
    }
}
