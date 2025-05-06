#pragma once
#include <SFML/Graphics.hpp> 
#include<iostream>
#include<vector>
#include<ctime>

//class that acts as the game engine
//wrapper class


class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Gamelogic
	bool endGame;
	int health;
	unsigned points;//changing coz positive int only
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;


	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;//rectangle shape

	//private  functions
	void initVariables();
	void initWindow();
	void initEnemies();
public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//accessors
	const bool running() const;
	const bool getEndGame() const;

	//Fucntions

	void spawnEnemy();
	void updateEnemy();
	void renderEnemy();
	void updateMousePositions();
	void pollEvents();
	void update();
	void render();
};

