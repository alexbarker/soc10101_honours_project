#ifndef __SNAKE1_H__
#define __SNAKE1_H__

#include <vector>
#include <SFML/Graphics.hpp>
#include "../config.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// xxx.h - XXX.

class Snake1 {
	private:
		int length;
		int direction;					// Direction of the head
		int score;
		bool dead;
		std::vector<sf::Vector2i> pos;	// The snake is just stored as a list of (x, y)
		std::vector<sf::Vector2i> path; // Same for the path
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Color color;				// Original image is white but we can color it thanks to SFML
		
	public:
		Snake1();
		Snake1(Snake1& s);
		void spawn();											// Random positionning
		void move(int dir);										// Move in said direction
		bool followPath();										// Move according to the path
		void setPath(const std::vector<sf::Vector2i>& p);
		void clearPath();										// Empty path
		void eat();												// Grow and gain score
		void die();
		void display(sf::RenderWindow& win, Config& config);
		bool isOutOfBounds() const;								// Basic check to see if the snake hit a side wall
		bool hasPath() const;
		int getScore() const;
		bool isDead() const;
		sf::Color getColor() const;
		sf::Vector2i getHeadPosition() const;
		std::vector<sf::Vector2i> getPosition() const;
		int getPathSize() const;
};

#endif