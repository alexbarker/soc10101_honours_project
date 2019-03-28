#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <chrono>
#include <random>
#include "../lib/fann/src/include/fann.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// xxx.h - XXX.

using namespace std;

const int training_iterations_1mil = 1000000;

const int width_1mil = 600;
const int height_1mil = 600;

const int board_size_1mil = 20;

struct Point_1mil {
	int x, y;
	Point_1mil() { x = 0; y = 0; };
	Point_1mil(int _x, int _y) { x = _x; y = _y; };
};

class Stage_1mil {
public:
	sf::Texture texture1;
	sf::Sprite crystal_object;
	sf::Texture texture2;
	sf::Sprite head_object;
	sf::Texture texture3;
	sf::Sprite field_object;
	sf::RectangleShape vert_bar;
	sf::RectangleShape horz_bar, horz_bar2, horz_bar3, horz_bar4;;
	sf::Sprite titleSprite6b;
	sf::Texture titleTexture6b;
	sf::Font fontScore;
	sf::Text title_score, score_text, title_controls, controls_text1, controls_text2, controls_text3;

	bool debug;
	bool **board;
	deque<Point_1mil> snake;

	int random(int from, int to);
	int direct;
	int prevDirect;
	int candidatDirect;
	int score;
	Point_1mil crystal;
	float reward;

	void startNN1mil();
	void init_data();
	void reset();
	bool iteration();
	void random_crystal();
	int makeDir(int base, int d);
	void createInput(Stage_1mil& game, fann_type* input, int d = -1);
	void think(Stage_1mil& game, bool debug = false);

	Stage_1mil() {	
		init_data();
		reset();	
	};
	Stage_1mil(Stage_1mil  *stage) {
		
		init_data();
		reset();

		for (int x = 0; x < board_size_1mil; x++)
			for (int y = 0; y < board_size_1mil; y++)
			{
				bool p = stage->board[x][y];
				board[x][y] = p;
			}
		board = stage->board;
		snake = stage->snake;	
	}
	~Stage_1mil() {
		for (int x = 0; x < board_size_1mil; x++)
		{
			delete board[x];
		}
		delete board;
	}
};
