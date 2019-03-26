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

const int training_iterations_100k = 100000;

const int width_100k = 600;
const int height_100k = 600;

const int board_size_100k = 20;

struct Point_100k {
	int x, y;
	Point_100k() { x = 0; y = 0; };
	Point_100k(int _x, int _y) { x = _x; y = _y; };
};

class Stage_100k {
public:
	bool debug;
	bool **board;
	deque<Point_100k> snake;

	int random(int from, int to);
	int direct;
	int prevDirect;
	int candidatDirect;
	int score;
	Point_100k crystal;
	float reward;

	void startNN100k();
	void init_data();
	void reset();
	bool iteration();
	void random_crystal();
	int makeDir(int base, int d);
	void createInput(Stage_100k& game, fann_type* input, int d = -1);
	void think(Stage_100k& game, bool debug = false);

	Stage_100k() {
		init_data();
		reset();
	};
	Stage_100k(Stage_100k *stage) {	
		init_data();
		reset();

		for (int x = 0; x < board_size_100k; x++)
			for (int y = 0; y < board_size_100k; y++) {
				bool p = stage->board[x][y];
				board[x][y] = p;
			}
		board = stage->board;
		snake = stage->snake;	
	}
	~Stage_100k() {
		for (int x = 0; x < board_size_100k; x++) {
			delete board[x];
		}
		delete board;
	}
};
