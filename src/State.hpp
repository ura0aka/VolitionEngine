#pragma once

#include <Entity.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <stack>
#include <map>

// parent class for different states
namespace VolE
{
    class State
    {
    protected:
    // == WINDOW VARIABLES ==
    sf::RenderWindow* mWindow;

    // == RESOURCES ==
    std::vector<sf::Texture*> mTextureContainer;

    // == LOGIC ==
    bool mQuitState;

    public:
    // == CONSTRUCTOR/DESTRUCTOR ==
    State(sf::RenderWindow* Win);
    virtual ~State();

    // == ACCESSOR FUNCTIONS ==
    const bool getEndState() const;

    // == MAIN FUNCTIONS ==
    void checkEndState(); 

    virtual void cleanUpState() = 0;
    virtual void updateKeyInputs() = 0;
    virtual void updateState(const float& dt) = 0;
    virtual void renderState(sf::RenderTarget* targetWin = nullptr) = 0;

    };
}