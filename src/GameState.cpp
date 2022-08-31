#include "GameState.hpp"
#include "ComponentsUtil.hpp"
// == INITIALIZER FUNCTIONS ==
Entity& GameState::initPlayer()
{
    // initialize our player object
    auto& entity(this->manager.addEntity());

    entity.addComponent<PlayerComponent>(sf::Vector2f(100.0f,100.0f));

    this->mSprite.setTexture(this->res_manager.loadTexture("res/textures/botamon.png"));

    entity.addGroup(VolEGroups::Player);
    return entity;
}

Entity& GameState::initNPC()
{
    // initialize random NPC object
    sf::Vector2f npcSize(30.0f,20.0f);
    sf::Color npcColor(sf::Color(randColorRed(gen),randColorGreen(gen),randColorBlue(gen)));
    sf::Vector2f npcVelocity(0.0f,0.0f);
    auto& entity(this->manager.addEntity());

    

    entity.addComponent<PositionComponent>(sf::Vector2f(randPosx(gen),randPosy(gen)));
    entity.addComponent<ShapeComponent>(npcSize,npcColor);
    entity.addComponent<PhysicsComponent>(npcVelocity,npcSize);

    entity.addGroup(VolEGroups::NPC);
    return entity;
}

// == CONSTRUCTOR/DESTRUCTOR ==
GameState::GameState(sf::RenderWindow* Win) : State(Win)
{
    this->initPlayer();
    for(int i {0}; i < 300; ++i) { this->initNPC(); }
}

GameState::~GameState() {}

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

    // == group our entity types ==
    auto& npcs(manager.getEntitiesByGroup(NPC));
    auto& player(manager.getEntitiesByGroup(Player));

    for (auto& p : player)
    {
        for (auto& n : npcs)
        {
            collisionAABB(*p, *n);
        }
    }
}

void GameState::renderState(sf::RenderTarget* targetWin)
{
    this->manager.renderManager(targetWin);
}