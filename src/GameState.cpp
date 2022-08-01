#include "GameState.hpp"
// == INITIALIZER FUNCTIONS ==


// == CONSTRUCTOR/DESTRUCTOR ==
VolE::GameState::GameState(sf::RenderWindow* Win) : State(Win)
{
    auto& gEntity(e_Manager.addEntity());
    auto& gShape(gEntity.addComponent<VolE::ShapeComponent>());
    auto& gCounter(gEntity.addComponent<VolE::LifeTimeComponent>());
    auto& gKill(gEntity.addComponent<VolE::KillComponent>(gCounter));
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
    e_Manager.updateManager(dt);

}


void VolE::GameState::renderState(sf::RenderTarget* targetWin)
{
    e_Manager.renderManager(targetWin);
}