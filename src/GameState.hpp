#pragma once

#include "State.hpp"
#include "EntityManager.hpp"

#include <random>

class EntityManager;
// == GAME STATE CLASS ==
// game state class where everything will happen
class GameState : public State
{
private:

// == MANAGERS ==
EntityManager manager;
// == COMPONENTS ==

// == RESOURCES ==

// == GAME OBJECTS ==

// == INITIALIZER FUNCTIONS ==
Entity& initPlayer();
Entity& initNPC();

public:
// == CONSTRUCTOR/DESTRUCTOR ==
GameState(sf::RenderWindow* Win);
virtual ~GameState();

// == MAIN FUNCTIONS ==
void cleanUpState() override;
void updateKeyInputs() override;
void updateState(const float& dt) override;
void renderState(sf::RenderTarget* targetWin) override;
};
