#include "GameState.hpp"
#include "ComponentsUtil.hpp"
// == INITIALIZER FUNCTIONS ==
void GameState::initManager()
{
    auto& entity(this->manager.addEntity());
    auto& entity1(this->manager.addEntity());
    auto& entity2(this->manager.addEntity());
    auto& entity3(this->manager.addEntity());


    auto& cCounter(entity.addComponent<CounterComponent>());
    auto& cCounter1(entity1.addComponent<CounterComponent>());
    auto& cCounter2(entity2.addComponent<CounterComponent>());
    auto& cCounter3(entity3.addComponent<CounterComponent>());

    auto& cShape(entity.addComponent<ShapeComponent>());
    auto& cShape1(entity1.addComponent<ShapeComponent>());
    auto& cShape2(entity2.addComponent<ShapeComponent>());
    auto& cShape3(entity3 .addComponent<ShapeComponent>());


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