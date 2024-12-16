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
	std::vector<sf::CircleShape> circles;
	std::vector<float> velocityY;
	std::vector<bool> onGround;
	std::vector<float> velocityX;

	//constants
	const float gravity = 500.0f;

	//nonConstants
	std::vector<float> bounceVal;

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

	//circle functions
	//this function takes values sent from initCircle(); and applies the gravity and velocity values to make them fall to the bottom
	//TODO: add bounching physics
	void updateCircle(float deltaTime)
	{
		for (int i = 0; i < this->circles.size(); i++)
		{
			if (!this->onGround[i])
			{
				this->velocityY[i] += gravity * deltaTime;
			}

			this->circles[i].move(0.0f, this->velocityY[i] * deltaTime);
			//calculate bottom of circle
			float circleBottom = this->circles[i].getPosition().y + this->circles[i].getRadius() * 2;

			if (circleBottom >= 600.0f)
			{
				this->velocityY[i] = -this->velocityY[i];

				if (this->bounceVal[i] <= 0.0f)
				{
					this->circles[i].setPosition(this->circles[i].getPosition().x, 600.0f - this->circles[i].getRadius() * 2);
					this->bounceVal[i] = 0.0f;
					this->velocityY[i] = 0.0f;
					this->onGround[i] = true;
				}
			}

			for (int j = 0; j < this->circles.size(); j++)
			{
				if (i != j)
				{
					sf::Vector2f posA = this->circles[i].getPosition();
					sf::Vector2f posB = this->circles[j].getPosition();
					float radA = this->circles[i].getRadius();
					float radB = this->circles[j].getRadius();

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

						//Bounce physics
						std::swap(this->velocityY[i], this->velocityY[j]);
						std::swap(this->velocityX[i], this->velocityX[j]);
					}
				}
			}
		}
		
	}
};

