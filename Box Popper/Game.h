#pragma once
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

	//private  functions
	void initVariables();
	void initWindow();
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

