#ifndef __GUI10_H__
#define __GUI10_H__

#include "SFML/Graphics.hpp"
#include "../define.h"
#include "../components/cmp_snake_body_10snakes.h"
#include "../components/cmp_snake_food_10snakes.h"
#include "../config.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// XXX.cpp - XXX.

class Gui10 {
	private:
		int scrollVal;
		sf::RectangleShape obstacle;
		std::multimap<int, int> scoreMap;
		sf::Font fontTitle, fontScore;
		sf::RectangleShape vert_bar, horiz_bar, horiz_bar2, horiz_bar3, horiz_bar_long, black_back, black_back2, black_back3;
		sf::Text title_score, score, controls_text, mouse_text1, mouse_text2, mouse_text3;
		sf::Sprite titleSprite4b;
		sf::Texture titleTexture4b;

	public:
		Gui10();
		void scroll(sf::Vector2i& mousePos, int i);
		void sortByScore(Snake10 snake[NB_PLAYER10]);
		void display(sf::RenderWindow& win, std::vector<sf::Vector2i> fixedO, Snake10 snake[NB_PLAYER10], Crystal10 crsytal[NB_CRYSTAL10], Config& config);
};

#endif