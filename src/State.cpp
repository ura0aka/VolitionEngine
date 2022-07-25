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