#include "MainMenuState.hpp"

// == INITIALIZER FUCNTIONS ==
void MainMenuState::initFont()
{
    this->mFont.loadFromFile("res/fonts/Perfect DOS VGA 437 Win.ttf");
}

void MainMenuState::initButtons()
{
    
    this->mButtonContainer["MM_NEWGAME_BTN"] = new Button(200,100,300,150,&this->mFont, "New Game",sf::Color::White, sf::Color::Green, sf::Color::Magenta);
    this->mButtonContainer["MM_EXIT_BTN"] = new Button(200, 300, 300, 150, &this->mFont, "Quit", sf::Color::White, sf::Color::Green, sf::Color::Magenta);

    
}

// == CONSTRUCTOR/DESTRUCTOR ==
MainMenuState::MainMenuState(sf::RenderWindow* Win, std::stack<State*>* States) : State(Win,States)
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

    // push new game state
    if (this->mButtonContainer["MM_NEWGAME_BTN"]->isPressed())
    {
        this->mStatesPtr_Stack->push(new GameState(this->mWindow, this->mStatesPtr_Stack));
    }

    // quit game
    if (this->mButtonContainer["MM_EXIT_BTN"]->isPressed())
    {
        this->mQuitState = true;
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