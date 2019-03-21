#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <chrono>
#include <random>
#include "../lib/fann/src/include/fann.h"
#include "define.h"

using namespace std;

const int training_iterations = 10000000;

const int width = 1910;
const int height = 990;

const int board_size = 30;

struct Point
{
	int x, y;
	Point() { x = 0; y = 0; };
	Point(int _x, int _y) { x = _x; y = _y; };
};



class Stage
{
public:



	bool debug;
	bool **board;
	deque<Point> snake;

	int direct;
	int prevDirect;
	int candidatDirect;
	int score;
	Point apple;
	float reward;

	void oops3();
	void init_data();
	void reset();
	bool iteration();
	void random_apple();
	int makeDir(int base, int d);


	Stage()
	{
		
		init_data();
		reset();
		
		
	};
	Stage(Stage *stage)
	{
		
		init_data();
		reset();

		for (int x = 0; x < board_size; x++)
			for (int y = 0; y < board_size; y++)
			{
				bool p = stage->board[x][y];
				board[x][y] = p;
			}
		board = stage->board;
		snake = stage->snake;
		
	}
	~Stage()
	{
		for (int x = 0; x < board_size; x++)
		{

			//for(int y = 0; y < board_size; y++)
			//{

			//}	
			delete board[x];
		}
		delete board;
	}

	void createInput(Stage& game, fann_type* input, int d = -1);
	void think(Stage& game, bool debug = false);
};
