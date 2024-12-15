#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{

private:

	//WINDOW
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event event;

	//Init object circle
	sf::CircleShape circle;

	void initVars();
	void initWindow();
	void initCircle();

public:
	Game();
	virtual ~Game();

	//accessors
	const bool running() const;

	//functions
	void pollEvents();
	void update();
	void render();
};

