#ifndef __CRYSTAL3_H__
#define __CRYSTAL3_H__

#include <SFML/Graphics.hpp>

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// xxx.h - XXX.

class Crystal50 {
	private:
		sf::Vector2i pos;
		sf::Texture texture;
		sf::Sprite sprite;

	public:
		Crystal50();
		void spawn(std::vector<sf::Vector2i> obstacles, Crystal50 crystal[NB_CRYSTAL50]);
		void display(sf::RenderWindow& win);
		sf::Vector2i getPosition() const;
};

#endif