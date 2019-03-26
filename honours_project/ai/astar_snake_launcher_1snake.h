#ifndef __GAME1_H__
#define __GAME1_H__

#include <SFML/Graphics.hpp>
#include "../components/cmp_snake_body_1snake.h"
#include "../components/cmp_snake_food_1snake.h"
#include "../scenes/astar_snake_interface_1snake.h"
#include "../config.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// xxx.h - XXX.

class Game1 {
	private:
		int snakeAlive;								//Number of snakes left
		Crystal1 crystal[NB_CRYSTAL1];
		Snake1 snake[NB_PLAYER1];
		std::vector<sf::Vector2i> fixedObstacles;
		std::vector<sf::Vector2i> obstacles;		//Obstacles as a list of (x, y)
		Gui1 gui;									//Interface
		Config config;
	
	public:
		Game1();
		void play(sf::RenderWindow& win);
		bool collide(Snake1& s);					//Collision check
		void stall(Snake1& s);						//Zig-Zag cycle when snake can't find path
		void addObstacle(sf::Vector2i v);			// To add an obstacle with mouse click
		void removeObstacle(sf::Vector2i v);		// To remove an obstacle with mouse click
		void generateObstacles();					//Just add all snake elements into the obstacles list
		void gameOver(sf::RenderWindow& win);		//Game over panel and score display
		void handleEvents(sf::RenderWindow& win);
};

#endif