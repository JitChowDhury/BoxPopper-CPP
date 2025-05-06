#include "Game.h"

//private functions
void Game::initVariables()
{
	this->window = nullptr;
}
void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Box-Popper", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);//pos of top corner ofc
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);

}

//constructors and destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
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
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
		}
	}
}
void Game::update()
{
	this->pollEvents();
	//update mouse pos
	//Relative to screen
	//std::cout << "Mouse pos: " << sf::Mouse::getPosition().x << "," << sf::Mouse::getPosition().y << std::endl;
	//Relative to the window
	std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << "," << sf::Mouse::getPosition(*this->window).y << std::endl;
}


void Game::render()
{
	/*
	- clear old frame
	- render objects
	- display frame in window

	Renders the game objects.
   */



	this->window->clear();//clear
	//Draw game objects
	this->window->draw(this->enemy);

	this->window->display();
}

