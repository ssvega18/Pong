#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


/*
	Class that will handle all game-related functions

*/



class Game
{

	private:

		// Variables
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event ev;

		// Game logic variables
		unsigned int p1Score = 0;
		unsigned int p2Score = 0;
		bool gameEnd = false;

		// Game entities
		sf::RectangleShape pad1;
		sf::RectangleShape pad2;
		sf::Vertex border[2];
		sf::CircleShape ball;
		
		// entity variables
		const unsigned int padHeight = 100;
		const unsigned int padWidth = 20;

		// movement variables
		int moveX = 5;
	    int moveY = 5;
		float SPEED = 55.f;


		// text variables
		sf::Font font;
		sf::Text player1Score;
		sf::Text player2Score;
		sf::Text gameOverText;

		// delta time
		sf::Clock dtClock;
		float dt;

		// Utility functions 
		void initVariables();
		void initWindow();
		void initEntities();
		void Checkcollision();
	    void initText();
		void endGame();
		void restartGame();
		void updateText(unsigned int number, sf::Text* text);

	public:
		// Constructor
		Game();
		virtual ~Game();

		// Getters
		const bool running() const;

		// general functions
		void pollEvents();
		
		void updateDT();
		void update();
		void render();
		
};

