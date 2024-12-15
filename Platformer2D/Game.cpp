#include <iostream>
#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <random>



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
	std::random_device rd;

	std::mt19937 gen(rd());

	std::uniform_int_distribution<> distr(1, 100);
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->circle.setRadius(distr(gen));
		this->circle.setFillColor(sf::Color::Red);
		this->circle.setPosition(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y);
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
	this->initCircle();
}

void Game::render()
{
	this->window->clear();

	this->window->draw(this->circle);

	this->window->display();
}