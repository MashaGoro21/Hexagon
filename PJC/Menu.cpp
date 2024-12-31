#include "Menu.hpp"

//Private functions
void Menu::initVariables()
{
    isVisibleMenu = true;
    isVisibleType = false;
    playMode = false;
    saveGame = false;
    gameType = true;
    isGameSaved = false;
}

void Menu::initFonts()
{
    if(!this->font.loadFromFile("/Users/masagorosena/Desktop/2223s_20c_s27179/PJC/arial.ttf"))
    {
        return EXIT_FAILURE;
    }
}

void Menu::initText()
{
    //Menu text init
    this->menuText = sf::Text("MENU", font, 200);
    this->menuText.setFillColor(sf::Color::Black);
    this->menuText.setPosition(sf::Vector2f(1150, 150));

    //New Game text init
    this->newGameText = sf::Text("New Game", font, 80);
    this->newGameText.setFillColor(sf::Color::Black);
    this->newGameText.setPosition(sf::Vector2f(1250, 420));

    //Load Game text init
    this->loadGameText = sf::Text("Load Game", font, 80);
    this->loadGameText.setFillColor(sf::Color::Black);
    this->loadGameText.setPosition(sf::Vector2f(1240, 530));

    //Quit text init
    this->quitText = sf::Text("Quit", font, 80);
    this->quitText.setFillColor(sf::Color::Black);
    this->quitText.setPosition(sf::Vector2f(1350, 640));
    
    //Play with another player (game type) init
    this->playerText = sf::Text("PLAYER  vs.  PLAYER", font, 100);
    this->playerText.setFillColor(sf::Color::Black);
    this->playerText.setPosition(sf::Vector2f(970, 550));
    
    //Play with computer (game type) init
    this->computerText = sf::Text("PLAYER  vs.  COMPUTER", font, 100);
    this->computerText.setFillColor(sf::Color::Black);
    this->computerText.setPosition(sf::Vector2f(970, 750));
    
    //Quit in the field init
    this->quitTextField = sf::Text("QUIT", font, 100);
    this->quitTextField.setFillColor(sf::Color::Black);
    this->quitTextField.setPosition(sf::Vector2f(70, 1300));
    
    //Save Game text init
    this->saveGameText = sf::Text("Do you want to save game?", font, 80);
    this->saveGameText.setFillColor(sf::Color::Black);
    this->saveGameText.setPosition(sf::Vector2f(1000, 520));
    
    //Yes text init
    this->yesText = sf::Text("YES", font, 100);
    this->yesText.setFillColor(sf::Color::Black);
    this->yesText.setPosition(sf::Vector2f(1050, 700));
    
    //No text init
    this->noText = sf::Text("NO", font, 100);
    this->noText.setFillColor(sf::Color::Black);
    this->noText.setPosition(sf::Vector2f(1790, 700));
}

void Menu::initPanel()
{
    this->panelShape.setSize(sf::Vector2f(1200, 400));
    this->panelShape.setFillColor(sf::Color(128, 128, 128));
    this->panelShape.setPosition(sf::Vector2f(900, 500));
    this->panelShape.setOutlineColor(sf::Color::Black);
    this->panelShape.setOutlineThickness(5.f);
}

//Constructor and destructor
Menu::Menu()
{
    this->initVariables();
    this->initFonts();
    this->initText();
    this->initPanel();
    
}

Menu::~Menu()
{
    
}

//Functions
bool Menu::checkCollision(sf::Text text, sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return text.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    
}

void Menu::update(sf::RenderWindow& window)
{
    if(isVisibleMenu)
    {
        //New Game
        if(checkCollision(newGameText, window))
        {
            newGameText.setFillColor(sf::Color::White);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                isVisibleMenu = false;
                isVisibleType = true;
                
            }
        }else
        {
            newGameText.setFillColor(sf::Color::Black);
        }
        
        //Load Game
        if(checkCollision(loadGameText, window))
        {
            loadGameText.setFillColor(sf::Color::White);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(isGameSaved){
                    isVisibleMenu = false;
                    playMode = true;
                }
            }
        }else
        {
            loadGameText.setFillColor(sf::Color::Black);
        }
        
        //Quit
        if(checkCollision(quitText, window))
        {
            quitText.setFillColor(sf::Color::White);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                window.close();
            }
        }else
        {
            quitText.setFillColor(sf::Color::Black);
        }
    }
    
    if(isVisibleType)
    {
        //Player vs. Player
        if(checkCollision(playerText, window))
        {
            playerText.setFillColor(sf::Color::White);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                playMode = true;
                isVisibleType = false;
                gameType = true;
                this->hexagon = Hexxagon(gameType);
            }
        }else
        {
            playerText.setFillColor(sf::Color::Black);
        }
        
        //Player vs. Computer
        if(checkCollision(computerText, window))
        {
            computerText.setFillColor(sf::Color::White);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                playMode = true;
                isVisibleType = false;
                gameType = false;
                this->hexagon = Hexxagon(gameType);
            }
        }else
        {
            computerText.setFillColor(sf::Color::Black);
        }
    }
    if(playMode)
    {
        if(checkCollision(quitTextField, window))
        {
            quitTextField.setFillColor(sf::Color::White);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                playMode = false;
                saveGame = true;
            }
        }else
        {
            quitTextField.setFillColor(sf::Color::Black);
        }
    }
    if(saveGame)
    {
        if(checkCollision(yesText, window))
        {
            yesText.setFillColor(sf::Color::White);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                saveGame = false;
                isVisibleMenu = true;
                isGameSaved = true;

            }
        } else
        {
            yesText.setFillColor(sf::Color::Black);
        }
        
        if(checkCollision(noText, window))
        {
            noText.setFillColor(sf::Color::White);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                saveGame = false;
                isVisibleMenu = true;
                isGameSaved = false;
                
            }
        } else
        {
            noText.setFillColor(sf::Color::Black);
        }
    }

}

void Menu::render(sf::RenderWindow& window)
{
    this->update(window);
    if(isVisibleMenu)
    {
        window.draw(this->menuText);
        window.draw(this->newGameText);
        window.draw(this->loadGameText);
        window.draw(this->quitText);
    }
    
    if(isVisibleType)
    {
        window.draw(this->playerText);
        window.draw(this->computerText);
    }
    
    if(playMode)
    {
        hexagon.render(window);
        window.draw(this->quitTextField);
    }
    
    if(saveGame)
    {
        window.draw(this->panelShape);
        window.draw(this->saveGameText);
        window.draw(this->yesText);
        window.draw(this->noText);
    }
}

