#include "../components/stdafx.h"
#include <iostream>
#include "astar_snake_interface_1snake.h"
#include "../ai/astar_1snake.h"

using namespace sf;

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// XXX.cpp - XXX.

Gui1::Gui1() {
	scrollVal = 0;

	obstacle.setSize(Vector2f(S_SIZE, S_SIZE));
	obstacle.setFillColor(Color(25,125,225));

	vert_bar.setSize(Vector2f(6, W_HEIGHT));
	vert_bar.setFillColor(Color::White);
	vert_bar.setPosition(G_WIDTH*S_SIZE, 0);

	horiz_bar.setSize(Vector2f(W_WIDTH / 4 + 5, 6));
	horiz_bar.setFillColor(Color::White);
	horiz_bar.setPosition(G_WIDTH*S_SIZE, W_HEIGHT / 7);

	horiz_bar2.setSize(Vector2f(W_WIDTH / 4 + 5, 6));
	horiz_bar2.setFillColor(Color::White);
	horiz_bar2.setPosition(G_WIDTH*S_SIZE, W_HEIGHT / 2.1);

	horiz_bar3.setSize(Vector2f(W_WIDTH / 4 + 5, 6));
	horiz_bar3.setFillColor(Color::White);
	horiz_bar3.setPosition(G_WIDTH*S_SIZE, W_HEIGHT / 2.4);

	horiz_bar_long.setSize(Vector2f(W_WIDTH, 6));
	horiz_bar_long.setFillColor(Color::White);
	horiz_bar_long.setPosition(0, W_HEIGHT);

	black_back.setSize(Vector2f(W_WIDTH / 4, W_HEIGHT / 7));
	black_back.setFillColor(Color::Black);
	black_back.setPosition(G_WIDTH * S_SIZE, 0);

	black_back2.setSize(Vector2f(W_WIDTH / 4, W_HEIGHT / 2.8));
	black_back2.setFillColor(Color::Black);
	black_back2.setPosition(G_WIDTH * S_SIZE, W_HEIGHT / 7);

	black_back3.setSize(Vector2f(W_WIDTH / 4 + 7, W_HEIGHT / 7));
	black_back3.setFillColor(Color::Black);
	black_back3.setPosition(G_WIDTH * S_SIZE, W_HEIGHT);

	fontTitle.loadFromFile(FONT_TITLE);
	fontScore.loadFromFile(FONT_SCORE);

	title_score.setString("Snake Length");
	title_score.setFont(fontTitle);
	title_score.setCharacterSize(W_HEIGHT / 38);
	title_score.setOutlineColor(Color::White);
	title_score.setPosition(7 * W_WIDTH / 8 - title_score.getLocalBounds().width / 2, W_HEIGHT / 2.32);

	controls_text.setString("Controls : [Spacebar] Pause [Z] Show Path [X] Show Weight [C] Show Cost [V] Toggle Breadth First Search [B] Toggle FPS Cap [N/M] Change FPS [Esc] Close");
	controls_text.setFont(fontTitle);
	controls_text.setCharacterSize(W_HEIGHT / 50);
	controls_text.setOutlineColor(Color::White);
	controls_text.setPosition(18, W_HEIGHT + 18);

	score.setString("S00 - 000");
	score.setFont(fontScore);
	score.setCharacterSize(W_HEIGHT / 44);
	score.setPosition((float)(7 * W_WIDTH / 8.7 - score.getLocalBounds().width / 2), 0);

	titleTexture3b.loadFromFile(TITLEIMG);
	titleSprite3b.setTexture(titleTexture3b);
	titleSprite3b.setPosition(W_WIDTH * 0.75, 8);
	titleSprite3b.setScale(0.62, 0.62);
}

void Gui1::scroll(Vector2i& mousePos, int val) {
	if (mousePos.x > vert_bar.getPosition().x && mousePos.x < W_WIDTH
		&& mousePos.y > horiz_bar.getPosition().y && mousePos.y < W_HEIGHT) {
		if (scrollVal <= 0)
			scrollVal += 25 * val;
		if (scrollVal > 0)
			scrollVal = 0;
	}
}

void Gui1::sortByScore(Snake1 snake[NB_PLAYER1]) {
	for (int i = 0; i < NB_PLAYER1; i++) {
		scoreMap.emplace(snake[i].getScore(), i);
	}
}

void Gui1::display(RenderWindow& win, std::vector<sf::Vector2i> fixedO, Snake1 snake[NB_PLAYER1], Crystal1 crystal[NB_CRYSTAL1], Config& config) {
	sortByScore(snake);

	win.clear();

	if (config.isDisplayWeightOn() || config.isDisplayCostOn()) {
		RectangleShape rect;
		for (int i = 0; i < G_WIDTH; i++) {
			for (int j = 0; j < G_HEIGHT; j++) {
				int color = 0;
				if(config.isDisplayWeightOn())
					color += 128 * (1 - Astar1::getWeight(i, j) / WEIGHT_REF);
				if(config.isDisplayCostOn())
					color += 128 * (1 - Astar1::getCost(i, j) / WEIGHT_REF);

				rect.setFillColor(Color(color, color, color));
				rect.setPosition(i*S_SIZE, j * S_SIZE);
				rect.setSize(Vector2f(S_SIZE, S_SIZE));
				win.draw(rect);
			}
		}
	}

	for (auto o : fixedO) {
		obstacle.setPosition(S_SIZE * o.x, S_SIZE * o.y);
		win.draw(obstacle);
	}

	if (NB_PLAYER1 > 10) {
		if (scrollVal < 6 * W_HEIGHT / 7 - (int)(W_HEIGHT / 12 * (NB_PLAYER1 + 1)))
			scrollVal = 6 * W_HEIGHT / 7 - (int)(W_HEIGHT / 12 * (NB_PLAYER1 + 1));
	}
	else
		scrollVal = 0;

	int i = 0;
	for (auto it = scoreMap.rbegin(); it != scoreMap.rend(); ++it) {
		String pnum, pscore;
		if (it->second + 1 < 10)
			pnum = "0" + std::to_string(it->second + 1);
		else
			pnum = std::to_string(it->second + 1);

		if (it->first < 10)
			pscore = "00" + std::to_string(it->first);
		else if (it->first < 100)
			pscore = "0" + std::to_string(it->first);
		else
			pscore = std::to_string(it->first);

		score.setString("Snake " + pnum + " - " + pscore);
		score.setFillColor(snake[it->second].getColor());
		score.setPosition(score.getPosition().x, (float)(W_HEIGHT / 2 + scrollVal + i * W_HEIGHT / 43));
		win.draw(score);

		if (!snake[it->second].isDead())
			snake[it->second].display(win, config);

		i++;
	}
	scoreMap.clear();

	win.draw(black_back);
	win.draw(black_back2);
	win.draw(vert_bar);
	win.draw(horiz_bar);
	win.draw(horiz_bar2);
	win.draw(horiz_bar3);
	win.draw(horiz_bar_long);
	win.draw(title_score);
	for(int i = 0; i < NB_CRYSTAL1; i++)
		crystal[i].display(win);
	win.draw(black_back3);
	win.draw(horiz_bar_long);
	win.draw(controls_text);
	win.draw(titleSprite3b);
	win.display();
}
