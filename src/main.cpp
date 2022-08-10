#include "Game.hpp"
#include "Entity.hpp"

int main()
{
    Game mainGame;
    // EntityManager manager;

    // auto& entity(manager.addEntity());
    // auto& cCounter(entity.addComponent<CounterComponent>());
    // auto& cShape(entity.addComponent<ShapeComponent>());
    // auto& cKill(entity.addComponent<KillComponent>());

    mainGame.run();
    
    return 0;
}