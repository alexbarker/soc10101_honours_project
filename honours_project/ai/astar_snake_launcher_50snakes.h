#ifndef __GAME3_H__
#define __GAME3_H__

#include <SFML/Graphics.hpp>
#include "../components/cmp_snake_body_50snakes.h"
#include "../components/cmp_snake_food_50snakes.h"
#include "../scenes/astar_snake_interface_50snakes.h"
#include "../config.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// xxx.h - XXX.

class Game50 {
	private:
		int snakeAlive;								//Number of snakes left
		Crystal50 crystal[NB_CRYSTAL50];
		Snake50 snake[NB_PLAYER50];
		std::vector<sf::Vector2i> fixedObstacles;
		std::vector<sf::Vector2i> obstacles;		//Obstacles as a list of (x, y)
		Gui50 gui;									//Interface
		Config config;
	
	public:
		Game50();
		void play(sf::RenderWindow& win);
		bool collide(Snake50& s);					//Collision check
		void stall(Snake50& s);						//Zig-Zag cycle when snake can't find path
		void addObstacle(sf::Vector2i v);			// To add an obstacle with mouse click
		void removeObstacle(sf::Vector2i v);		// To remove an obstacle with mouse click
		void generateObstacles();					//Just add all snake elements into the obstacles list
		void gameOver(sf::RenderWindow& win);		//Game over panel and score display
		void handleEvents(sf::RenderWindow& win);
};

#endif