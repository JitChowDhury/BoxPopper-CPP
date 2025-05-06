#pragma once
#include<iostream>
#include <SFML/Graphics.hpp> 

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

	//Game objects
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

	//Fucntions
	void pollEvents();
	void update();
	void render();
};

  