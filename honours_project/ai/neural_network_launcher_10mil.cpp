#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <chrono>
#include <random>
#include "neural_network_launcher_10mil.h"
#include "../define.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// xxx.h - XXX.

using namespace std;

bool train_10mil = true;
const int INF_10mil = 123456;
struct fann *ann_10mil;

bool board_data_10mil[board_size_10mil][board_size_10mil];
minstd_rand* randomGenerator_10mil;

int Stage_10mil::random(int from, int to) {
	randomGenerator_10mil = new  std::minstd_rand(chrono::system_clock::now().time_since_epoch().count());
	return (*randomGenerator_10mil)() % (to - from + 1) + from;
}

void Stage_10mil::init_data() {
	debug = false;
	board = new bool*[board_size_10mil];

	for (int x = 0; x < board_size_10mil; x++) {
		board[x] = new bool[board_size_10mil];
		for (int y = 0; y < board_size_10mil; y++) {
			board[x][y] = 0;
		}
	}
	
}

void Stage_10mil::reset() {

	for (int x = 0; x < board_size_10mil; x++) {
		for (int y = 0; y < board_size_10mil; y++) {
			board[x][y] = 0;
		}
	}
	snake.clear();
	direct = UP;
	candidatDirect = UP;

	for (int i = 0; i < 1; i++)
		snake.push_front(Point_10mil(board_size_10mil / 2, board_size_10mil / 2));

	board[board_size_10mil / 2][board_size_10mil / 2] = 1;

	random_crystal();
	score = 0;
}

bool Stage_10mil::iteration() {
	Point_10mil new_position;
	new_position = snake.front();

	prevDirect = direct;
	direct = candidatDirect;

	if (direct == UP)
		new_position.y--;
	if (direct == DOWN)
		new_position.y++;
	if (direct == LEFT)
		new_position.x--;
	if (direct == RIGHT)
		new_position.x++;

	if (new_position.y < 0 || new_position.y >= board_size_10mil || new_position.x < 0 || new_position.x >= board_size_10mil) {
		reset();
		reward = -1.0;
		return false;
	}
	if (board[new_position.x][new_position.y] == 1) {
		reset();
		reward = -1;
		return false;
	}

	if (new_position.x == crystal.x && new_position.y == crystal.y) {
		score++;
		if (debug) {
			//cout<<"Score: "<<score<<endl;
		}
		snake.push_front(new_position);
		board[new_position.x][new_position.y] = 1;
		random_crystal();
		reward = 1.0;

	}
	else {
		reward = -1.0 * sqrt(pow(crystal.x - snake.front().x, 2.0f) + pow(crystal.y - snake.front().y, 2.0f)) / (sqrt(2)*(float)board_size_10mil);
	}

	snake.push_front(new_position);
	board[new_position.x][new_position.y] = 1;

	board[snake.back().x][snake.back().y] = 0;
	snake.pop_back();

	return true;
}

void Stage_10mil::random_crystal() {
	do {
		crystal = Point_10mil(random(3, (board_size_10mil - 3)), random(3, (board_size_10mil - 3)));
	} 
	while (board[crystal.x][crystal.y] == 1);
}

int Stage_10mil::makeDir(int base, int d) {
	if (d == 0) {
		if (base == UP) {
			return LEFT;
		}
		else
			if (base == DOWN) {
				return RIGHT;
			}
			else
				if (base == LEFT) {
					return DOWN;
				}
				else
					if (base == RIGHT) {
						return UP;
					}
	}
	else
		if (d == 1) {
			return base;
		}
		else
			if (d == 2) {
				if (base == UP) {
					return RIGHT;
				}
				else
					if (base == DOWN) {
						return LEFT;
					}
					else
						if (base == LEFT) {
							return UP;
						}
						else
							if (base == RIGHT) {
								return DOWN;
							}
			}
}

void Stage_10mil::createInput(Stage_10mil& game, fann_type* input, int d) {
	int x = game.snake.front().x;
	int y = game.snake.front().y;
	int direct = game.direct;

	if (d != -1) {
		direct = makeDir(game.direct, d);
		if (direct == UP)
			y--; y--;
		if (direct == DOWN)
			y++; y++;
		if (direct == LEFT)
			x--;
		if (direct == RIGHT)
			x++;
	}

	input[0] = 1.0*sqrt(pow(game.crystal.x - x, 2.0f) + pow(game.crystal.y - y, 2.0f)) / (sqrt(2)*(float)board_size_10mil);;

	Point_10mil left(x, y);
	Point_10mil front(x, y);
	Point_10mil right(x, y);

	if (direct == UP) {
		left.x--;
		front.y--;
		right.x++;
	}
	if (direct == DOWN) {
		left.x++;
		front.y++;
		right.x--;
	}
	if (direct == LEFT) {
		left.y++;
		front.x--;
		right.y--;
	}
	if (direct == RIGHT) {
		left.y--;
		front.x++;
		right.y++;
	}

	if (left.y >= 0 && left.y < board_size_10mil && left.x >= 0 && left.x < board_size_10mil) {
		if (game.board[left.x][left.y] == 0)
			input[1] = 0;
		else if (left.x == game.crystal.x && left.y == game.crystal.y)
			input[1] = 1;
		else input[1] = -1;
	}
	else
		input[1] = -1;

	if (front.y >= 0 && front.y < board_size_10mil && front.x >= 0 && front.x < board_size_10mil) {
		if (game.board[front.x][front.y] == 0)
			input[2] = 0;
		else if (front.x == game.crystal.x && front.y == game.crystal.y)
			input[2] = 1;
		else input[2] = -1;
	}
	else
		input[2] = -1;

	if (right.y >= 0 && right.y < board_size_10mil && right.x >= 0 && right.x < board_size_10mil) {
		if (game.board[right.x][right.y] == 0)
			input[3] = 0;
		else if (right.x == game.crystal.x && right.y == game.crystal.y)
			input[3] = 1;
		else input[3] = -1;
	}
	else
		input[3] = -1;
}

int curiosity_10mil = training_iterations_10mil;

void Stage_10mil::think(Stage_10mil& game, bool debug) {
	
	fann_type *output_tmp;
	int d = 1;
	float max = -INF_10mil;

	fann_type input_front[4];
	createInput(game, input_front, 1);
	output_tmp = fann_run(ann_10mil, input_front);

	if (debug)cout << "1~:" << input_front[0] << " " << input_front[1] << " " << input_front[2] << " " << input_front[3] << " " << endl;
	if (output_tmp[0] >= max) {
		max = output_tmp[0];
		d = 1;
	}
	if (debug)cout << "~" << output_tmp[0] << endl;

	fann_type input_left[4];
	createInput(game, input_left, 0);
	output_tmp = fann_run(ann_10mil, input_left);
	if (debug)cout << "0~:" << input_left[0] << " " << input_left[1] << " " << input_left[2] << " " << input_left[3] << " " << endl;
	if (output_tmp[0] >= max) {
		max = output_tmp[0];
		d = 0;
	}
	if (debug)cout << "~" << output_tmp[0] << endl;

	fann_type input_right[4];
	createInput(game, input_right, 2);
	output_tmp = fann_run(ann_10mil, input_right);
	if (debug)cout << "2~:" << input_right[0] << " " << input_right[1] << " " << input_right[2] << " " << input_right[3] << " " << endl;
	if (output_tmp[0] >= max) {
		max = output_tmp[0];
		d = 2;
	}
	if (debug)cout << "~" << output_tmp[0] << endl;
	if (debug)cout << "D:" << d << endl;

	bool tmp = false;
	if (!debug &&  random(0, 100) < curiosity_10mil) {
		tmp = true;
		d = random(0, 2);
		curiosity_10mil -= 1;
	}

	fann_type input[4];
	createInput(game, input, 3);

	if (debug)cout << "RI: " << input[0] << " " << input[1] << " " << input[2] << " " << input[3] << " " << endl;
	game.candidatDirect = makeDir(game.direct, d);
	game.iteration();
	fann_type output[1];
	output[0] = game.reward;
	if (debug)cout << "R:" << game.reward << endl;

	fann_train(ann_10mil, input, output);

	if (debug)output_tmp = fann_run(ann_10mil, input);
	if (debug)cout << "XXXTEST: " << output_tmp[0] << " -<> " << output[0] << endl;
}

void Stage_10mil::startNN10mil() {
	randomGenerator_10mil = new  std::minstd_rand(chrono::system_clock::now().time_since_epoch().count());

	const unsigned int num_input = 4;
	const unsigned int num_output = 1;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = 8;
	ann_10mil = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);

	fann_set_learning_rate(ann_10mil, 0.7);
	fann_set_learning_momentum(ann_10mil, 0.1);

	fann_set_activation_function_hidden(ann_10mil, FANN_GAUSSIAN);
	fann_set_activation_function_output(ann_10mil, FANN_SIGMOID_SYMMETRIC);

	sf::RenderWindow window(sf::VideoMode(900, 600), "Neural Network Snake - 10 Million");

	Stage_10mil game;
	game.debug = false;

	int field_size = width_10mil / board_size_10mil; 
	sf::RectangleShape field_object(sf::Vector2f(field_size, field_size));
	field_object.setFillColor(sf::Color(180, 225, 90));
	texture1.loadFromFile(T_CRYSTAL);
	crystal_object.setTexture(texture1);
	sf::RectangleShape head_object(sf::Vector2f(field_size, field_size));
	head_object.setFillColor(sf::Color(200, 225, 80));

	vert_bar.setSize(sf::Vector2f(6, 600));
	vert_bar.setFillColor(sf::Color::White);
	vert_bar.setPosition(600, 0);

	horz_bar.setSize(sf::Vector2f(300, 6));
	horz_bar.setFillColor(sf::Color::White);
	horz_bar.setPosition(600, 200);

	int speed_block = 0;
	int speed_block_max = 50;
	int iteration_time_ai = 100;
	int iteration_time_normal = 200;
	int iteration_time_fast = 100;
	bool ai = true;

	for (int i = 0; i < training_iterations_10mil; i++){
		think(game, false);

		game.iteration();
		if (i % (training_iterations_10mil / 100) == 0) cout << i << endl;
	}

	int iteration_time = iteration_time_normal;
	auto timerBegin = chrono::high_resolution_clock::now();

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::Space) {
					if (ai) {
						ai = false;
						iteration_time = iteration_time_normal;
					}
					else {
						ai = true;
						iteration_time = iteration_time_ai;
					}
				}
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::P) timerBegin = chrono::high_resolution_clock::now();
				if (event.key.code == sf::Keyboard::Left) {
					if (game.direct != RIGHT) {
						game.candidatDirect = LEFT;
						if (game.prevDirect != game.direct)
							speed_block = 0;
						game.prevDirect = game.direct;
					}
				}
				if (event.key.code == sf::Keyboard::Up) {
					if (game.direct != DOWN) {
						game.candidatDirect = UP;
						if (game.prevDirect != game.direct)
							speed_block = 0;
						game.prevDirect = game.direct;
					}
				}
				if (event.key.code == sf::Keyboard::Right) {
					if (game.direct != LEFT) {
						game.candidatDirect = RIGHT;
						if (game.prevDirect != game.direct)
							speed_block = 0;
						game.prevDirect = game.direct;
					}
				}
				if (event.key.code == sf::Keyboard::Down) {
					if (game.direct != UP) {
						game.candidatDirect = DOWN;
						if (game.prevDirect != game.direct)
							speed_block = 0;
						game.prevDirect = game.direct;
					}
				}
			}

			if (!ai) {
				if (event.type == sf::Event::KeyPressed && speed_block >= speed_block_max)
					iteration_time = iteration_time_fast;
				else
					iteration_time = iteration_time_normal;
			}
		}

		auto timerEnd = chrono::high_resolution_clock::now();
		int timer = chrono::duration_cast<std::chrono::milliseconds>(timerEnd - timerBegin).count();

		if (timer > iteration_time) {
			timerBegin = timerEnd;
			speed_block++;

			if (ai)
				think(game, false);
			else
				game.iteration();
		}

		window.clear(sf::Color::Black);

		for (int x = 0; x < board_size_10mil; x++)
			for (int y = 0; y < board_size_10mil; y++) {
				if (game.board[x][y]) {
					field_object.setPosition(x * field_size, y * field_size);
					window.draw(field_object);
				}
			}
		crystal_object.setPosition(game.crystal.x * field_size, game.crystal.y * field_size);
		window.draw(crystal_object);
		head_object.setPosition(game.snake.front().x * field_size, game.snake.front().y * field_size);
		window.draw(head_object);
		window.draw(vert_bar);
		window.draw(horz_bar);
		window.display();
	}
}