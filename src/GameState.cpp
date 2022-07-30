#include "GameState.hpp"
// == INITIALIZER FUNCTIONS ==


// == CONSTRUCTOR/DESTRUCTOR ==
VolE::GameState::GameState(sf::RenderWindow* Win) : State(Win)
{

}

VolE::GameState::~GameState()
{

}

// == MAIN FUNCTIONS ==
void VolE::GameState::cleanUpState()
{
    std::cout << "Exiting state \n";
}

void VolE::GameState::updateKeyInputs()
{
    // check for key inputs from user
    
    // (Esc) : quit game state
    this->checkEndState();
}

void VolE::GameState::updateState(const float& dt)
{
    this->updateKeyInputs();

    // update all entities in our container
    for(auto& entity : this->mEntityContainer)
    {
        entity->updateObj(dt);
    }
}


void VolE::GameState::renderState(sf::RenderTarget* targetWin)
{
    for(auto& entity : this->mEntityContainer)
    {
        entity->renderObj(targetWin);
    }
}