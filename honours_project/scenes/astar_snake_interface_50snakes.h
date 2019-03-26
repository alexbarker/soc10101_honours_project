#ifndef __GUI50_H__
#define __GUI50_H__

#include "SFML/Graphics.hpp"
#include "../define.h"
#include "../components/cmp_snake_body_50snakes.h"
#include "../components/cmp_snake_food_50snakes.h"
#include "../config.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// XXX.cpp - XXX.

class Gui50 {
	private:
		int scrollVal;
		sf::RectangleShape obstacle;
		std::multimap<int, int> scoreMap;
		sf::Font fontTitle, fontScore;
		sf::RectangleShape vert_bar, horiz_bar, horiz_bar2, horiz_bar3, horiz_bar_long, black_back, black_back2, black_back3;
		sf::Text title_score, score, controls_text;

	public:
		Gui50();
		void scroll(sf::Vector2i& mousePos, int i);
		void sortByScore(Snake50 snake[NB_PLAYER50]);
		void display(sf::RenderWindow& win, std::vector<sf::Vector2i> fixedO, Snake50 snake[NB_PLAYER50], Crystal50 crystal[NB_CRYSTAL50], Config& config);
};

#endif