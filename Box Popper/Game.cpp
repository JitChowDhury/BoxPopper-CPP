#include "Game.h"

//private functions
void Game::initVariables()
{
	this->window = nullptr;

	//gamelogic

	this->points = 0;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
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

void Game::spawnEnemy()
{
	/*
	* spawns enemies and sets their color and pos
	* sets a random position
	* sets a random color
	* adds enemy to the vector
	*/
	this->enemy.setPosition(
		// Set enemy position randomly within the window, ensuring it stays fully visible on screen
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f

	);
	this->enemy.setFillColor(sf::Color::Red);
	//spawn the enemy
	this->enemies.push_back(this->enemy);

}

void Game::updateEnemy()
{
	/*
	* updates the enemy spawn timer and spawn enemies
	* when total amount of enemies is less that maxenemies
	* moves the enemy downwards
	* removes the enemies at the edge of the screen //TODO
	*/

	//updating the timer for enemySpawning
	if (this->enemies.size() < this->maxEnemies)
	{

		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}
	//move the enemies
	for (auto& e : this->enemies)
	{
		e.move(0.f, 1.f);
	}
}

void Game::renderEnemy()
{
	//rendering all the enemies
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::updateMousePositions()
{
	/*
	return void

	updates the mouse pos:
	*mouse pos relative to window(vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

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
	this->updateMousePositions();
	this->updateEnemy();
	//update mouse pos
	//Relative to screen
	//std::cout << "Mouse pos: " << sf::Mouse::getPosition().x << "," << sf::Mouse::getPosition().y << std::endl;
	//Relative to the window

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
	this->renderEnemy();

	this->window->display();
}

