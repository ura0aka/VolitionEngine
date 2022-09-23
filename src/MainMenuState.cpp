#include "MainMenuState.hpp"

// == INITIALIZER FUCNTIONS ==
void MainMenuState::initFont()
{
    this->mFont.loadFromFile("res/fonts/Perfect DOS VGA 437 Win.ttf");
}

void MainMenuState::initButtons()
{
    
    this->mButtonContainer["MM_BTN"] = new Button(100,100,150,150,&this->mFont, "New Game",sf::Color::White, sf::Color::Green, sf::Color::Magenta);
    std::cout << "created button" << std::endl;
}

// == CONSTRUCTOR/DESTRUCTOR ==
MainMenuState::MainMenuState(sf::RenderWindow* Win) : State(Win) 
{

    std::cout << "pushed main menu state" << '\n';
    this->initFont();
    this->initButtons();
    
}

MainMenuState::~MainMenuState() 
{
    // iterate over buttons container and delete all button object
    for(auto const& button : mButtonContainer)
    {
        delete button.second;
    }
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

void MainMenuState::updateButtons()
{
    for(auto const& button : mButtonContainer)
    {
        button.second->updateButton(this->mMousePosView);
    }

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
    this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* targetWin)
{
    for(auto const& button : mButtonContainer)
    {
        button.second->renderButton(targetWin);
    }
}
void MainMenuState::renderState(sf::RenderTarget* targetWin)
{
    this->renderButtons(targetWin);
}