#pragma once

#include <fstream>
#include <sstream>

#include "State.hpp"
#include "GameState.hpp"


namespace VolE
{

    enum winState
    {
        INITIALIZING,       // game is being initialized
        LOADING,            // game is loading in assets (fonts, textures, etc.)
        RUNNING,            // game is currently running in the main loop
        CLOSING,            // game is closing
        CLOSED              // game is closed  
    };

    class Game
    {
    private:
        // == WINDOW VARIABLES ==
        sf::RenderWindow* mWindow;
        sf::VideoMode mVideoMode;

        // == RESOURCES ==
        std::stack<VolE::State*> mStatesContainer;

        // == EVENT VARIABLES ==
        sf::Event mEvent;

        // == TIME VARIABLES ==
        sf::Clock mClock;
        float UPS = 1.0f / 120.0f;

        // == LOGIC ==
        winState mState;
        bool mEndGame;

        // == INITIALIZER FUNCTIONS ==
        void initVars();
        void initState();
        void initWindow();

    public:
        // == CONSTRUCTOR/DESTRUCTOR ==
        Game();
        ~Game();

        // == ACCESSOR FUNCTIONS ==
        const bool isRunning() const;
        const bool gameStatus() const;
        float getElapsedSeconds();
        float getElapsedMilliseconds();

        // == EVENT HANDLING ==
        void pollEvents();
        // == LOOP ==
        void updateAll(const float& dt);
        void renderAll();
        void run();
        

    };
}