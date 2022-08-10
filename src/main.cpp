#include "Game.hpp"

// == For testing ==
std::default_random_engine gen;
std::uniform_real_distribution<float> randPosx(0.0f, 500.0f);
std::uniform_real_distribution<float> randPosy(0.0f, 500.0f);
std::uniform_int_distribution<int> randColorRed(0,255);
std::uniform_int_distribution<int> randColorGreen(0,255);
std::uniform_int_distribution<int> randColorBlue(0,255); 


// == COMPONENTS ==

struct CounterComponent : Component
{
    float counter;
    void updateComponent(const float& dt) override
    {
        counter += dt;
        //std::cout << counter << std::endl;
    }
};

struct ShapeComponent : Component
{
    sf::RectangleShape mShape;
    ShapeComponent()
    {
        mShape.setFillColor(sf::Color(randColorRed(gen),randColorGreen(gen),randColorBlue(gen),255));
        mShape.setSize(sf::Vector2f(10.0f,10.0f));
        mShape.setPosition(randPosx(gen),randPosy(gen));
    }
    const float getPos()
    {
        return mShape.getPosition().y;
    }
    void updateComponent(const float& dt)
    {
        mShape.move(0.0f, 200.0f * dt);
    }
    void renderComponent(sf::RenderTarget* targetWin) override
    {
        targetWin->draw(this->mShape);
    }
    
};

struct KillComponent : Component
{
    CounterComponent* cCounter;
    ShapeComponent* cShape;
    void initComponent() override
    {
        cCounter = &mEntity->getComponent<CounterComponent>();
        cShape = &mEntity->getComponent<ShapeComponent>();
    }
    void updateComponent(const float& dt) override
    {
        if(cCounter->counter >= 2) mEntity->destroyObj();
    }
};


// main functionning game loop (with delta time calculations)
void run(Game& mainGame, EntityManager& manager)
{
    float spawnTimerMax = 5.0f;
    float spawnTimer = spawnTimerMax;

    float UPS = 1.0f / 120.0f;
    float lastFrameTime = 0.0f;
    float dt = 0.0f;
    
    while(mainGame.isRunning() && !mainGame.gameStatus())
    {
        // delta time calculation (in seconds)
        float currentFrameTime = mainGame.getElapsedSeconds();
        dt = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        if(spawnTimer >= spawnTimerMax)
        {
            for(int i {0}; i < 10; ++i)
            {
                auto& entity(manager.addEntity());
                auto& cCounter(entity.addComponent<CounterComponent>());
                auto& cShape(entity.addComponent<ShapeComponent>());
                auto& cKill(entity.addComponent<KillComponent>());
                
                spawnTimer = 0.0f;
            }
        }
        else
        {
            spawnTimer += 1;
        }

        if(dt >= UPS)
        {
            // update frame (we will pass in delta time here)
            mainGame.updateAll(dt);
            dt -= UPS;
            manager.updateManager(dt);
        }
        // render frame
        mainGame.renderAll();
        manager.renderManager(mainGame.getWindow());
    }
}

int main()
{
    Game mainGame;
    EntityManager manager;

    run(mainGame, manager);

    return 0;
}