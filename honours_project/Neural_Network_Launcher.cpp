#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <chrono>
#include <random>
#include "Neural_Network_Launcher.h"
#include "define.h"

using namespace std;

bool train = true;
const int INF = 123456;
struct fann *ann;
bool board_data[board_size][board_size];

minstd_rand* randomGenerator;

int random(int from, int to)
{
	randomGenerator = new  std::minstd_rand(chrono::system_clock::now().time_since_epoch().count());
	return (*randomGenerator)() % (to - from + 1) + from;
}



enum Direction
{
	LEFT1, UP1, RIGHT1, DOWN1
};

void Stage::init_data()

{
	
	debug = false;
	board = new bool*[board_size];
	for (int x = 0; x < board_size; x++)
	{
		board[x] = new bool[board_size];
		for (int y = 0; y < board_size; y++)
		{
			board[x][y] = 0;
		}
	}
	
}
void Stage::reset()
{
	for (int x = 0; x < board_size; x++)
	{
		for (int y = 0; y < board_size; y++)
		{
			board[x][y] = 0;
		}
	}
	snake.clear();
	direct = UP1;
	candidatDirect = UP1;

	for (int i = 0; i < 1; i++)
		snake.push_front(Point(board_size / 2, board_size / 2));

	board[board_size / 2][board_size / 2] = 1;

	random_apple();
	score = 0;
	
}
bool Stage::iteration()
{
	Point new_position;
	new_position = snake.front();

	prevDirect = direct;
	direct = candidatDirect;

	if (direct == UP1)
		new_position.y--;
	if (direct == DOWN1)
		new_position.y++;
	if (direct == LEFT1)
		new_position.x--;
	if (direct == RIGHT1)
		new_position.x++;

	if (new_position.y < 0 || new_position.y >= board_size ||
		new_position.x < 0 || new_position.x >= board_size)
	{
		reset();
		if (debug)
		{
			//cout<<"Od nowa!"<<endl;
		}
		reward = -1.0;
		return false;
	}
	if (board[new_position.x][new_position.y] == 1)
	{
		reset();
		if (debug)
		{
			//cout<<"Od nowa!"<<endl;
		}
		reward = -1;
		return false;
	}

	if (new_position.x == apple.x && new_position.y == apple.y)
	{
		score++;
		if (debug)
		{
			//cout<<"Score: "<<score<<endl;
		}
		snake.push_front(new_position);
		board[new_position.x][new_position.y] = 1;
		random_apple();
		reward = 1.0;

	}
	else
	{
		reward = -1.0 * sqrt(pow(apple.x - snake.front().x, 2.0f) + pow(apple.y - snake.front().y, 2.0f)) / (sqrt(2)*(float)board_size);
	}

	snake.push_front(new_position);
	board[new_position.x][new_position.y] = 1;

	board[snake.back().x][snake.back().y] = 0;
	snake.pop_back();

	return true;
}
void Stage::random_apple()
{
	do
	{
		apple = Point(random(0, board_size - 1), random(0, board_size - 1));
	} while (board[apple.x][apple.y] == 1);
}


int Stage::makeDir(int base, int d)
{
	if (d == 0)
	{
		if (base == UP1)
		{
			return LEFT1;
		}
		else
			if (base == DOWN1)
			{
				return RIGHT1;
			}
			else
				if (base == LEFT1)
				{
					return DOWN1;
				}
				else
					if (base == RIGHT1)
					{
						return UP1;
					}
	}
	else
		if (d == 1)
		{
			// direct == direct
			return base;
		}
		else
			if (d == 2)
			{
				if (base == UP1)
				{
					return RIGHT1;
				}
				else
					if (base == DOWN1)
					{
						return LEFT1;
					}
					else
						if (base == LEFT1)
						{
							return UP1;
						}
						else
							if (base == RIGHT1)
							{
								return DOWN1;
							}
			}
}

void Stage::createInput(Stage& game, fann_type* input, int d)
{
	int x = game.snake.front().x;
	int y = game.snake.front().y;
	int direct = game.direct;

	if (d != -1)
	{
		direct = makeDir(game.direct, d);
		if (direct == UP1)
			y--;
		if (direct == DOWN1)
			y++;
		if (direct == LEFT1)
			x--;
		if (direct == RIGHT1)
			x++;
	}



	input[0] = 1.0*sqrt(pow(game.apple.x - x, 2.0f) + pow(game.apple.y - y, 2.0f)) / (sqrt(2)*(float)board_size);;

	Point left(x, y);
	Point front(x, y);
	Point right(x, y);
	if (direct == UP1)
	{
		left.x--;
		front.y--;
		right.x++;
	}
	if (direct == DOWN1)
	{
		left.x++;
		front.y++;
		right.x--;
	}
	if (direct == LEFT1)
	{
		left.y++;
		front.x--;
		right.y--;
	}
	if (direct == RIGHT1)
	{
		left.y--;
		front.x++;
		right.y++;
	}

	//
	if (left.y >= 0 && left.y < board_size && left.x >= 0 && left.x < board_size)
	{
		if (game.board[left.x][left.y] == 0)
			input[1] = 0;
		else if (left.x == game.apple.x && left.y == game.apple.y)
			input[1] = 1;
		else input[1] = -1;
	}
	else
		input[1] = -1;

	if (front.y >= 0 && front.y < board_size && front.x >= 0 && front.x < board_size)
	{
		if (game.board[front.x][front.y] == 0)
			input[2] = 0;
		else if (front.x == game.apple.x && front.y == game.apple.y)
			input[2] = 1;
		else input[2] = -1;
	}
	else
		input[2] = -1;


	if (right.y >= 0 && right.y < board_size && right.x >= 0 && right.x < board_size)
	{
		if (game.board[right.x][right.y] == 0)
			input[3] = 0;
		else if (right.x == game.apple.x && right.y == game.apple.y)
			input[3] = 1;
		else input[3] = -1;
	}
	else
		input[3] = -1;

}

int curiosity = training_iterations;//%



void Stage::think(Stage& game, bool debug)
{
	
	fann_type *output_tmp;
	int d = 1;
	float max = -INF;


	fann_type input_front[4];
	createInput(game, input_front, 1);
	output_tmp = fann_run(ann, input_front);
	if (debug)cout << "1~:" << input_front[0] << " " << input_front[1] << " " << input_front[2] << " " << input_front[3] << " " << endl;
	if (output_tmp[0] >= max)
	{
		max = output_tmp[0];
		d = 1;
	}
	if (debug)cout << "~" << output_tmp[0] << endl;



	fann_type input_left[4];
	createInput(game, input_left, 0);
	output_tmp = fann_run(ann, input_left);
	if (debug)cout << "0~:" << input_left[0] << " " << input_left[1] << " " << input_left[2] << " " << input_left[3] << " " << endl;
	if (output_tmp[0] >= max)
	{
		max = output_tmp[0];
		d = 0;
	}
	if (debug)cout << "~" << output_tmp[0] << endl;



	fann_type input_right[4];
	createInput(game, input_right, 2);
	output_tmp = fann_run(ann, input_right);
	if (debug)cout << "2~:" << input_right[0] << " " << input_right[1] << " " << input_right[2] << " " << input_right[3] << " " << endl;
	if (output_tmp[0] >= max)
	{
		max = output_tmp[0];
		d = 2;
	}
	if (debug)cout << "~" << output_tmp[0] << endl;
	if (debug)cout << "D:" << d << endl;

	bool tmp = false;
	if (!debug &&  random(0, 100) < curiosity)
	{
		tmp = true;
		d = random(0, 2);
		curiosity -= 1;
	}


	fann_type input[4];
	createInput(game, input, 3);


	if (debug)cout << "RI: " << input[0] << " " << input[1] << " " << input[2] << " " << input[3] << " " << endl;
	game.candidatDirect = makeDir(game.direct, d);
	game.iteration();
	fann_type output[1];
	output[0] = game.reward;
	if (debug)cout << "R:" << game.reward << endl;

	/// cmake!  

	//if(debug){
	/*
	if(game.reward < -0.95)
	{
		fann_set_learning_rate(ann, 0.7);
		for(int i = 0; i < 100; i++)
			fann_train(ann, input, output);
	}
	 else if(game.reward > 0)
	 {
		fann_set_learning_rate(ann, 10.7);
		//for(int i = 0; i < 100; i++)
			fann_train(ann, input, output);
	}
	else
		fann_set_learning_rate(ann, 0.1);
	if(tmp)
		fann_set_learning_rate(ann, 0.05);//}
		*/

	fann_train(ann, input, output);

	if (debug)output_tmp = fann_run(ann, input);
	if (debug)cout << "XXXTEST: " << output_tmp[0] << " -<> " << output[0] << endl;
}



void Stage::oops3()
{
	minstd_rand* randomGenerator;
	randomGenerator = new  std::minstd_rand(chrono::system_clock::now().time_since_epoch().count());

	const unsigned int num_input = 4;
	const unsigned int num_output = 1;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = 8;
	ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);

	fann_set_learning_rate(ann, 0.7);
	fann_set_learning_momentum(ann, 0.1);

	fann_set_activation_function_hidden(ann, FANN_GAUSSIAN);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

	sf::RenderWindow window(sf::VideoMode(600, 600), "Snake A.I.");


	Stage game;
	game.debug = false;

	int field_size = width / board_size;
	sf::RectangleShape field_object(sf::Vector2f(field_size, field_size));
	field_object.setFillColor(sf::Color(255, 157, 0));
	sf::RectangleShape apple_object(sf::Vector2f(field_size, field_size));
	apple_object.setFillColor(sf::Color(0, 255, 0));
	sf::RectangleShape head_object(sf::Vector2f(field_size, field_size));
	head_object.setFillColor(sf::Color(255, 97, 0));


	int speed_block = 0;
	int speed_block_max = 50;
	int iteration_time_ai = 100;
	int iteration_time_normal = 200;
	int iteration_time_fast = 100;
	bool ai = true;


	for (int i = 0; i < training_iterations; i++)
	{
		think(game, false);

		game.iteration();
		if (i % (training_iterations / 100) == 0) cout << i << endl;
	}



	int iteration_time = iteration_time_normal;
	auto timerBegin = chrono::high_resolution_clock::now();
	while (window.isOpen())
	{


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::Space)
				{
					if (ai)
					{
						ai = false;
						iteration_time = iteration_time_normal;
					}
					else
					{
						ai = true;
						iteration_time = iteration_time_ai;
					}
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P) timerBegin = chrono::high_resolution_clock::now();
				if (event.key.code == sf::Keyboard::Left)
				{
					if (game.direct != RIGHT1)
					{
						game.candidatDirect = LEFT1;
						if (game.prevDirect != game.direct)
							speed_block = 0;
						game.prevDirect = game.direct;
					}
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					if (game.direct != DOWN1)
					{
						game.candidatDirect = UP1;
						if (game.prevDirect != game.direct)
							speed_block = 0;
						game.prevDirect = game.direct;
					}
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					if (game.direct != LEFT1)
					{
						game.candidatDirect = RIGHT1;
						if (game.prevDirect != game.direct)
							speed_block = 0;
						game.prevDirect = game.direct;
					}
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					if (game.direct != UP1)
					{
						game.candidatDirect = DOWN1;
						if (game.prevDirect != game.direct)
							speed_block = 0;
						game.prevDirect = game.direct;
					}
				}
			}

			if (!ai)
			{
				if (event.type == sf::Event::KeyPressed && speed_block >= speed_block_max)
					iteration_time = iteration_time_fast;
				else
					iteration_time = iteration_time_normal;
			}
		}

		auto timerEnd = chrono::high_resolution_clock::now();
		int timer = chrono::duration_cast<std::chrono::milliseconds>(timerEnd - timerBegin).count();
		if (timer > iteration_time)
		{
			timerBegin = timerEnd;
			speed_block++;

			if (ai)
				think(game, false);
			else
				game.iteration();
		}


		window.clear(sf::Color::Black);

		for (int x = 0; x < board_size; x++)
			for (int y = 0; y < board_size; y++)
			{
				if (game.board[x][y])
				{
					field_object.setPosition(x * field_size, y * field_size);
					window.draw(field_object);
				}
			}
		apple_object.setPosition(game.apple.x * field_size, game.apple.y * field_size);
		window.draw(apple_object);
		head_object.setPosition(game.snake.front().x * field_size, game.snake.front().y * field_size);
		window.draw(head_object);

		window.display();
	}
}