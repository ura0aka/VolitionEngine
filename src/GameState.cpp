#include "GameState.hpp"
#include "ComponentsUtil.hpp"
// == INITIALIZER FUNCTIONS ==
Entity& GameState::initPlayer()
{
    sf::Vector2f playerSize(10.0f,10.0f);
    sf::Color playerColor(sf::Color::Green);
    sf::Vector2f playerVelocity(200.0f,200.0f);
    auto& entity(this->manager.addEntity());

    entity.addComponent<PositionComponent>(sf::Vector2f(100.0f,100.0f));
    entity.addComponent<ShapeComponent>(playerSize,playerColor);
    entity.addComponent<PhysicsComponent>(playerVelocity);
    entity.addComponent<MovementComponent>();
    return entity;
}

Entity& GameState::initNPC()
{
    sf::Vector2f npcSize(10.0f,10.0f);
    sf::Color npcColor(sf::Color(randColorRed(gen),randColorGreen(gen),randColorBlue(gen)));
    sf::Vector2f npcVelocity(20.0f,20.0f);
    auto& entity(this->manager.addEntity());

    entity.addComponent<PositionComponent>(sf::Vector2f(randPosx(gen),randPosy(gen)));
    entity.addComponent<ShapeComponent>(npcSize,npcColor);
    entity.addComponent<PhysicsComponent>(npcVelocity);
    return entity;
}

// == CONSTRUCTOR/DESTRUCTOR ==
GameState::GameState(sf::RenderWindow* Win) : State(Win)
{
    this->initPlayer();
    for(int i{0}; i < 100; ++i)
    {
        this->initNPC();
    }
    
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