#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>



namespace VolE
{
    class Game
    {
    private:
        // == WINDOW VARIABLES ==
        sf::RenderWindow* mWindow;
        sf::VideoMode mVideoMode;
        // == EVENT VARIABLES ==
        sf::Event mEvent;
        // == TIME VARIABLES ==
        sf::Clock mClock;
        float UPS = 1.0f / 120.0f;
        // == LOGIC ==
        bool mEndGame;

        // == INITIALIZER FUNCTIONS ==
        void initVars();
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