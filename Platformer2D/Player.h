#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum State {right, left, jumping, idle};

class Player
{
	
private:

	//model
	sf::Sprite player;
	sf::Texture playerTexture;

	//STATE
	State playerstate;
	bool onGround;
	float VelocityY;
	//float VelocityX;

	//GAME CONSTANTS
	const float gravity = 980.0f;
	const float jumpStrength = -400.0f;
	//const float dashSpeed = 15.0f;

public:
	//player Initialization
	void initPlayer();
	void render(sf::RenderTarget& target);

	//player movement and updates
	void playerMovement();
	void update(float deltaTime);


};

