#include "GameState.hpp"
#include "ComponentsUtil.hpp"
// == INITIALIZER FUNCTIONS ==
void GameState::initManager()
{
    auto& entity(this->manager.addEntity());
    auto& cCounter(entity.addComponent<CounterComponent>());
    auto& cShape(entity.addComponent<ShapeComponent>());
    //auto& cKill(entity.addComponent<KillComponent>());
}

// == CONSTRUCTOR/DESTRUCTOR ==
GameState::GameState(sf::RenderWindow* Win) : State(Win)
{
    this->initManager();
}

GameState::~GameState()
{

}

// == MAIN FUNCTIONS ==
void GameState::cleanUpState()
{
    std::cout << "Exiting state \n";
}

void GameState::updateKeyInputs()
{
    // check for key inputs from user
    
    // (Esc) : quit game state
    this->checkEndState();
}

void GameState::updateState(const float& dt)
{
    this->updateKeyInputs();
    this->manager.updateManager(dt);
}


void GameState::renderState(sf::RenderTarget* targetWin)
{
    this->manager.renderManager(targetWin);
}