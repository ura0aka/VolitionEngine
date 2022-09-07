#pragma once

#include "State.hpp"
#include "PlayerComponent.hpp"
#include "EntityManager.hpp"
#include "ResourceManager.hpp"

#include <random>

class EntityManager;
class ResourceManager;
// == GAME STATE CLASS ==
// game state class where everything will happen
class GameState : public State
{
private:

// == MANAGERS ==
EntityManager manager;
ResourceManager res_manager;

// == RESOURCES ==
sf::Sprite mSprite;
sf::Font mFont;
sf::Text mUIText;

// == GAME OBJECT INITIALIZER FUNCTIONS ==
void initFonts();
void initText();
Entity& initPlayer();
Entity& initNPC();

bool mMouseHeld;

public:
// == CONSTRUCTOR/DESTRUCTOR ==
GameState(sf::RenderWindow* Win);
virtual ~GameState();

// == MAIN FUNCTIONS ==
void cleanUpState() override;
void updateUIText(const float& dt);
void updateKeyInputs() override;
void updateState(const float& dt) override;
void renderUIText(sf::RenderTarget* targetWin);
void renderState(sf::RenderTarget* targetWin) override;
};
