#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <random>
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
	std::vector<sf::CircleShape> circles;
	std::vector<float> velocityY;
	std::vector<bool> onGround;
	std::vector<float> velocityX;

	//constants
	const float gravity = 500.0f;

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

	//this function takes values sent from initCircle(); and applies the gravity and velocity values to make them fall to the bottom
	void updateCircle(float deltaTime)
	{
		for (int i = 0; i < this->circles.size(); i++)
		{
			if (!this->onGround[i])
			{
				this->velocityY[i] += gravity * deltaTime;
			}

			this->circles[i].move(0.0f, this->velocityY[i] * deltaTime);

			float bottomcircle = this->circles[i].getPosition().y + this->circles[i].getRadius() * 2;
			if (bottomcircle >= 600.0f)
			{
				this->velocityY[i] = -this->velocityY[i] - deltaTime; 
			}

			for (int j = 0; j < this->circles.size(); j++)
			{
				if (i != j)
				{
					//actually using the distance formula for once in my academic life, incredible
					sf::Vector2f posA = this->circles[i].getPosition();
					sf::Vector2f posB = this->circles[j].getPosition();
					float radA = this->circles[i].getRadius();
					float radB = this->circles[j].getRadius();
					//calculate distance and then add and take the sqrt
					float distX = posA.x - posB.x;
					float distY = posA.y - posB.y;
					float dist = sqrt(distX * distX + distY * distY);
					//collision logic
					if (dist <= (radA + radB))
					{
						float movecirc = (radA + radB) - dist;
						sf::Vector2f moveDir(distX / dist, distY / dist);
						this->circles[i].move(moveDir.x * movecirc * 0.5f, moveDir.y * movecirc * 0.5f);
						this->circles[j].move(-moveDir.x * movecirc * 0.5f, -moveDir.y * movecirc * 0.5f);

						//BOUNCE PHYSICS (revised)
						std::swap(this->velocityY[i], this->velocityY[j]);
						std::swap(this->velocityX[i], this->velocityX[j]);

					}
				}
			}
		}
		
	}
	//picks color randomly and returns that color to function call in game.cpp
	sf::Color pickColor()
	{
		std::random_device rd;

		std::mt19937 gen(rd());

		std::uniform_int_distribution<> distr(0, 6);

		std::vector<sf::Color> colors = { sf::Color::Blue , sf::Color::Red, sf::Color::Cyan, sf::Color::Green, sf::Color::Magenta, sf::Color::White, sf::Color::Yellow};

		return colors[distr(gen)];
	}
};