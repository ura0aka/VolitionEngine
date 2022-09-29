#include "MainMenuState.hpp"

// == INITIALIZER FUNCTIONS ==
void MainMenuState::initFont()
{
    this->mFont.loadFromFile("res/fonts/Perfect DOS VGA 437 Win.ttf");
}

void MainMenuState::initButtons()
{
    this->mButtonContainer["MM_NEWGAME_BTN"] = new Button(300, 100, 300, 100, &this->mFont, "New State", sf::Color(80, 73, 69, 200), sf::Color(177, 98, 134, 200), sf::Color(204, 36, 29, 200));
    this->mButtonContainer["MM_EXIT_BTN"] = new Button(300, 300, 300, 100, &this->mFont, "Quit", sf::Color(80, 73, 69, 200), sf::Color(177, 98, 134, 200), sf::Color(204, 36, 29, 200));
}

void MainMenuState::initBG()
{
    this->mBackground.setSize(sf::Vector2f(this->mWindow->getSize().x, this->mWindow->getSize().y));

    this->mBackgroundTex.loadFromFile("res/images/vol-e.png");
    this->mBackground.setTexture(&this->mBackgroundTex);
}

// == CONSTRUCTOR/DESTRUCTOR ==
MainMenuState::MainMenuState(sf::RenderWindow* Win, std::stack<State*>* States) : State(Win,States)
{
    std::cout << "pushed main menu state" << '\n';
    this->initBG();
    this->initFont();
    this->initButtons();
    
}

MainMenuState::~MainMenuState() 
{
    // iterate over buttons container and delete all button objects
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
    targetWin->draw(this->mBackground);
    this->renderButtons(targetWin);
    
}