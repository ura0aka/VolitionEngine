#include "MainMenuState.hpp"

// == CONSTRUCTOR/DESTRUCTOR ==
MainMenuState::MainMenuState(sf::RenderWindow* Win) : State(Win) 
{
    std::cout << "pushed main menu state" << '\n';
}

MainMenuState::~MainMenuState() {}


// == MAIN FUCNTIONS ==
void MainMenuState::cleanUpState()
{
    std::cout << "Exiting state \n";
}

void MainMenuState::updateKeyInputs()
{
    // check for key inputs from user
    
    // (Esc) : quit game state
    this->checkEndState();
}


void MainMenuState::checkEndState()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        this->cleanUpState();
        this->mQuitState = true;
    }
}

void MainMenuState::updateState(const float& dt) 
{
    this->updateKeyInputs();
}


void MainMenuState::renderState(sf::RenderTarget* targetWin)
{

}