#include <iostream>
#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>



void Game::initVars()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videomode.height = 600;
	this->videomode.width = 800;
	this->window = new sf::RenderWindow(this->videomode, "Bouncing-Balls", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initCircle()
{
	//to generate random values
	std::random_device rd;

	std::mt19937 gen(rd());

	std::uniform_int_distribution<> distr(1, 51);
	//renders a circle and sends that info back to a bunch of vectors so that they can be initialized correctly in game.h
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::CircleShape circle;
		circle.setRadius(distr(gen));
		//TODO: make a function to randomly assign colors to the circles
		circle.setFillColor(sf::Color::Blue);
		circle.setPosition(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y);
		this->circles.push_back(circle);
		this->velocityY.push_back(0.0f);
		//TODO fix velocity x so that it decays over time and bounce slows overtime
		this->velocityX.push_back(0.0f);
		this->onGround.push_back(false);
	}

}

Game::Game()
{
	this->initVars();
	this->initWindow();
	this->initCircle();
}

Game::~Game()
{
	delete this->window;
}
const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{

	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}

	}
}

void Game::update()
{
	this->pollEvents();

	//DELTA TIME CLOCK
	static sf::Clock clock;
	float deltaTime = clock.restart().asSeconds();

	//circle movement update
	this->updateCircle(deltaTime);
	this->initCircle();

}

void Game::render()
{
	this->window->clear();

	//draw circles
	for (const auto& circle : circles)
	{
		this->window->draw(circle);
	}

	this->window->display();
}