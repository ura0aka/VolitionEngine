#include "MainMenuState.hpp"

// == INITIALIZER FUCNTIONS ==
void MainMenuState::initFont()
{
    this->mFont.loadFromFile("res/fonts/Perfect DOS VGA 437 Win.ttf");
}

// == CONSTRUCTOR/DESTRUCTOR ==
MainMenuState::MainMenuState(sf::RenderWindow* Win) : State(Win) 
{
    std::cout << "pushed main menu state" << '\n';
    this->mMMButton = new Button(100,100,150,150,
                                &this->mFont, "New Game",
                                sf::Color::White, sf::Color::Green, sf::Color::Magenta);
}

MainMenuState::~MainMenuState() 
{
    delete this->mMMButton;
}


// == MAIN FUCNTIONS ==
void MainMenuState::cleanUpState()
{
    std::cout << "Exiting state \n";
}

void MainMenuState::updateKeyInputs()
{
    // check for key inputs from user
    
    // (Esc) : quit game state
    this->checkEndState();
}


void MainMenuState::checkEndState()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        this->cleanUpState();
        this->mQuitState = true;
    }
}

void MainMenuState::updateState(const float& dt) 
{
    this->updateMousePosition();
    this->updateKeyInputs();
    this->mMMButton->updateButton(this->mMousePosView);
}


void MainMenuState::renderState(sf::RenderTarget* targetWin)
{
    this->mMMButton->renderButton(targetWin);
}