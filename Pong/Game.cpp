#include "Game.h"

// Private functions
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Pong", sf::Style::Default);
	this->window->setFramerateLimit(120);
}

// Constructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEntities();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}


// TODO: Optimize paddle movement
void Game::pollEvents()
{

	while (this->window->pollEvent(this->ev)) {

		switch (this->ev.type) {

		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			if (this->ev.key.code == sf::Keyboard::W) {
				this->pad1.move(0.f, -SPEED);
			}
			if (this->ev.key.code == sf::Keyboard::S) {
				this->pad1.move(0.f, SPEED);
			}
			if (this->ev.key.code == sf::Keyboard::Up) {
				this->pad2.move(0.f, -SPEED);
			}
			if (this->ev.key.code == sf::Keyboard::Down) {
				this->pad2.move(0.f, SPEED);
			}
			if (this->ev.key.code == sf::Keyboard::Space && gameEnd == true) {
				restartGame();
			}
			break;

		}

	}
}

void Game::initEntities()
{
	// border
	this->border[0].position = sf::Vector2f(400, 0);
	this->border[0].color = sf::Color::White;

	this->border[1].position = sf::Vector2f(400, 600);
	this->border[0].color = sf::Color::White;

	// ball
	this->ball.setRadius(10);
	this->ball.setPosition(sf::Vector2f(350.f, 300.f));
	this->ball.setFillColor(sf::Color::White);

	// paddles
	this->pad1.setPosition(sf::Vector2f(0.f, 250.f));
	this->pad1.setSize(sf::Vector2f(padWidth, padHeight));
	this->pad1.setFillColor(sf::Color::White);

	this->pad2.setPosition(sf::Vector2f(780.f, 250.f));
	this->pad2.setSize(sf::Vector2f(padWidth, padHeight));
	this->pad2.setFillColor(sf::Color::White);

}
void Game::Checkcollision()
{
	// calculates distance between paddles and ball

	int positionPad1X = std::clamp(this->ball.getPosition().x, this->pad1.getPosition().x, this->pad1.getPosition().x + padWidth);
	int positionPad1Y = std::clamp(this->ball.getPosition().y, this->pad1.getPosition().y, this->pad1.getPosition().y + padHeight);

	int subtractX = this->ball.getPosition().x - positionPad1X;
	int subtractY = this->ball.getPosition().y - positionPad1Y;

	int distanceBetween1 = std::sqrt((subtractX * subtractX) + (subtractY * subtractY));

	int positionPad2X = std::clamp(this->ball.getPosition().x, this->pad2.getPosition().x, this->pad2.getPosition().x + padWidth);
	int positionPad2Y = std::clamp(this->ball.getPosition().y, this->pad2.getPosition().y, this->pad2.getPosition().y + padHeight);

	int subtractX2 = this->ball.getPosition().x - positionPad2X;
	int subtractY2 = this->ball.getPosition().y - positionPad2Y;

	int distanceBetween2 = std::sqrt((subtractX2 * subtractX2) + (subtractY2 * subtractY2));

	
	// paddle 1 collision 
	if (this->ball.getRadius() > distanceBetween1) {
		
		// paddle1 right side
		if (this->ball.getPosition().x <= this->pad1.getPosition().x + padWidth) {
			moveX = -moveX;
		}

		// paddle1 top
		if (this->ball.getPosition().y <= this->pad1.getPosition().y) {
			moveY = -moveY;
		}

		// paddle1 bottom
		if (this->ball.getPosition().y >= this->pad1.getPosition().y + padHeight) {
			moveY = -moveY;
		}

	}

	if (this->ball.getRadius() > distanceBetween2) {

		// paddle2 right side
		if (this->ball.getPosition().x <= this->pad2.getPosition().x + padWidth) {
			moveX = -moveX;
		}

		// paddle2 top
		if (this->ball.getPosition().y <= this->pad2.getPosition().y) {
			moveY = -moveY;
		}

		// paddle2 bottom
		if (this->ball.getPosition().y >= this->pad2.getPosition().y + padHeight) {
			moveY = -moveY;
		}

	}

	// ceiling collision
	if (this->ball.getPosition().y <= 0) {
		moveY = -moveY;
	}

	// floor collision 
	if (this->ball.getPosition().y >= this->videoMode.height) {
		moveY = -moveY;
	}

	// left wall collision
	if (this->ball.getPosition().x < 0) {
		p2Score++;
		updateText(p2Score, &player2Score);
		this->ball.setPosition(400, 300);
	}

	// right wall collision
	if (this->ball.getPosition().x > this->videoMode.width) {
		p1Score++;
		updateText(p1Score, &player1Score);
		this->ball.setPosition(400, 300);
	}

}

void Game::initText()
{
	if (!this->font.loadFromFile("fonts/04B_09__.ttf")) {
		std::cout << "ERROR: Could not load font.";
		exit(1);
	}

	this->player1Score.setFont(this->font);
	this->player1Score.setPosition(sf::Vector2f(200.f, 0.f));
	this->player1Score.setFillColor(sf::Color::White);
	this->player1Score.setCharacterSize(40);
	this->player1Score.setString(std::to_string(this->p1Score));

	this->player2Score.setFont(this->font);
	this->player2Score.setPosition(sf::Vector2f(600.f, 0.f));
	this->player2Score.setFillColor(sf::Color::White);
	this->player2Score.setCharacterSize(40);
	this->player2Score.setString(std::to_string(this->p2Score));

	this->gameOverText.setFont(this->font);
	this->gameOverText.setPosition(sf::Vector2f(100.f, 200.f));
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setCharacterSize(22);
}

void Game::endGame()
{
	if (p1Score == 20) {
		moveX = 0;
		moveY = 0;
		SPEED = 0;
		gameEnd = true;
		this->gameOverText.setString("Player 1 WINS! Press SPACE to restart");
	}
	else if (p2Score == 20) {
		moveX = 0;
		moveY = 0;
		SPEED = 0;
		gameEnd = true;
		this->gameOverText.setString("Player 2 WINS! Press SPACE to restart");
	}



}

void Game::restartGame()
{
   this->gameOverText.setString("");
   this->updateText(0, &player1Score);
   this->updateText(0, &player2Score);
	p1Score = 0;
	p2Score = 0;
	moveX = 5;
	moveY = 5;
	SPEED = 55.f;
	
}

void Game::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateText(unsigned int number, sf::Text* text)
{
	text->setString(std::to_string(number));
}


// General functions
void Game::update()
{	
	this->endGame();
	this->ball.move(moveX, moveY);
	this->pollEvents();
	this->Checkcollision();
	
}

void Game::render()
{
	/*
		Renders game objects 
		- clear old frame
		- render objects
		- display frame in window
	*/

	this->window->clear(sf::Color(0,0,0,255));

	// Draw game objects

	this->window->draw(this->ball);
	this->window->draw(this->pad1);
	this->window->draw(this->pad2);
	this->window->draw(this->border,2,sf::Lines);
	this->window->draw(this->player1Score);
	this->window->draw(this->player2Score);
	this->window->draw(this->gameOverText);


	this->window->display();
}

