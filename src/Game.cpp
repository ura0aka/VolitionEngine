#include "Game.hpp"

// == INITIALIZER FUNCTIONS == 
void Game::initVars()
{
    this->mWindow = nullptr;
    this->mEndGame = false;
}

void Game::initState()
{
    // push newly created state to stack (LIFO)
    this->mStatesContainer.push(new MainMenuState(this->mWindow)); 
    this->mStatesContainer.push(new GameState(this->mWindow));
}

void Game::initWindow()
{
    // create a window using settings in conf/window.ini
    std::ifstream win_config("conf/window.ini");

    std::string w_title = "Null";
    sf::VideoMode window_bounds(800,800);
    unsigned int framerate_max = 120;
    bool vsync_status = false;

    if(!win_config.is_open())
    {
        std::cout << "ERROR: No file found. \n";
    }
    std::getline(win_config,w_title);
    win_config >> window_bounds.width >> window_bounds.height;
    win_config >> framerate_max;
    win_config >> vsync_status;

    win_config.close();

    this->mWindow = new sf::RenderWindow(window_bounds, w_title, sf::Style::Titlebar | sf::Style::Close);
    this->mWindow->setFramerateLimit(framerate_max);
    this->mWindow->setVerticalSyncEnabled(vsync_status);
}

// == CONSTRUCTOR/DESTRUCTOR ==
Game::Game()
{
    this->mState = INITIALIZING;

    this->initVars();
    this->initState();
    this->initWindow();
}

Game::~Game()
{
    this->mState = CLOSING;

    // deallocate memory
    delete this->mWindow;

    while(!this->mStatesContainer.empty())
    {
        // while our stack still has states in queue:
        // 1- deallocate the memory the pointer is holding
        delete this->mStatesContainer.top();
        // 2- pop the pointer from the stack
        this->mStatesContainer.pop();
    }

    this->mState = CLOSED;

}

// == ACCESSOR FUNCTIONS ==
const bool Game::isRunning() const
{
    return this->mWindow->isOpen();
}

const bool Game::gameStatus() const
{
    return this->mEndGame;
}

float Game::getElapsedSeconds()
{
    // get elapsed time rendering a frame in seconds
    return this->mClock.getElapsedTime().asSeconds();
}

float Game::getElapsedMilliseconds()
{
    // get elapsed time rendering a frame in milliseconds
    return this->mClock.getElapsedTime().asMilliseconds();
}


// == EVENT HANDLING == 
// get system events 
void Game::pollEvents()
{
    // while there is a flow of pending events
    // (we pass in an sf::Event variable)
    while(this->mWindow->pollEvent(mEvent))
    {
        // check for event type
        switch(mEvent.type)
        {
            // window is closed
            case sf::Event::Closed:
            {
                this->mWindow->close();
                break;
            }

            // // if esc key is pressed, close window
            // case sf::Event::KeyPressed:
            // {
            //     if(mEvent.key.code == sf::Keyboard::Escape)
            //     {
            //         this->mWindow->close();
            //     }
            //     break;
            // }

            default:
            {
                break;
            }
        }
    }
}

// == LOOP ==
// == UPDATE FUNCTIONS ==
void Game::updateMousePositions()
{
    this->mMousePosWin = sf::Mouse::getPosition(*this->mWindow);
    this->mMousePosView = this->mWindow->mapPixelToCoords(this->mMousePosWin);

    std::cout << "(" << mMousePosView.x << "," << mMousePosView.y << ") \n";
}

void Game::updateAll(const float& dt)
{
    this->pollEvents();
    this->updateMousePositions();
    

    // for game states
    if(!this->mStatesContainer.empty())
    {
        this->mStatesContainer.top()->updateState(dt);
        if(this->mStatesContainer.top()->getEndState())
        {
            delete this->mStatesContainer.top();
            this->mStatesContainer.pop();
        }
    }
    else
    {
        this->mWindow->close();
    }
}

// == RENDER FUNCTIONS ==
void Game::renderAll()
{
    // 1. clear previous frame
    this->mWindow->clear();

    // 2. draw objects on window

    // for game states
    if(!this->mStatesContainer.empty())
    {
        this->mStatesContainer.top()->renderState(this->mWindow);
    }
    // 3. display
    this->mWindow->display();
}

// == RUN ==
// main functionning game loop (with delta time calculations)
void Game::run()
{
    this->mState = RUNNING;
    
    float lastFrameTime = 0.0f;
    float dt = 0.0f;
    
    while(this->isRunning() && !this->gameStatus())
    {
        // delta time calculation (in seconds)
        float currentFrameTime = this->getElapsedSeconds();
        dt = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        if(dt >= UPS)
        {
            // update frame (we will pass in delta time here)
            this->updateAll(dt);
            dt -= UPS;
        }
        // render frame
        this->renderAll();
    }
}


