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

const int training_iterations_10mil = 10000000;

const int width_10mil = 600;
const int height_10mil = 600;

const int board_size_10mil = 20;

struct Point_10mil {
	int x, y;
	Point_10mil() { x = 0; y = 0; };
	Point_10mil(int _x, int _y) { x = _x; y = _y; };
};

class Stage_10mil {
public:
	bool debug;
	bool **board;
	deque<Point_10mil> snake;

	int random(int from, int to);
	int direct;
	int prevDirect;
	int candidatDirect;
	int score;
	Point_10mil crystal;
	float reward;

	void startNN10mil();
	void init_data();
	void reset();
	bool iteration();
	void random_crystal();
	int makeDir(int base, int d);
	void createInput(Stage_10mil& game, fann_type* input, int d = -1);
	void think(Stage_10mil& game, bool debug = false);

	Stage_10mil() {	
		init_data();
		reset();	
	};
	Stage_10mil(Stage_10mil *stage) {
		
		init_data();
		reset();

		for (int x = 0; x < board_size_10mil; x++)
			for (int y = 0; y < board_size_10mil; y++) {
				bool p = stage->board[x][y];
				board[x][y] = p;
			}
		board = stage->board;
		snake = stage->snake;
	}
	~Stage_10mil() {
		for (int x = 0; x < board_size_10mil; x++) {
			delete board[x];
		}
		delete board;
	}
};
