#include "Game.hpp"


//Private functions
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Hexagon", sf::Style::Default);
    
}

//Constructor and destructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

//Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

//Functions
void Game::pollEvents()
{
    while(this->window->pollEvent(this->event))
    {
        if(this->event.type == sf::Event::Closed || this->event.key.code == sf::Keyboard::Escape)
        {
            this->window->close();
        }
    }
}

void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    this->window->clear(sf::Color(80, 90, 255));
    this->menu.render(*this->window);
    this->window->display();
}
