#ifndef __CRYSTAL1_H__
#define __CRYSTAL1_H__

#include <SFML/Graphics.hpp>

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// xxx.h - XXX.

class Crystal1 {
	private:
		sf::Vector2i pos;
		sf::Texture texture;
		sf::Sprite sprite;

	public:
		Crystal1();
		void spawn(std::vector<sf::Vector2i> obstacles, Crystal1 crystal[NB_CRYSTAL1]);
		void display(sf::RenderWindow& win);
		sf::Vector2i getPosition() const;
};

#endif