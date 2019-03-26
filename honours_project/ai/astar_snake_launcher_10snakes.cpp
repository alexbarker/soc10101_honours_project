#include "../components/stdafx.h"
#include <iostream>
#include <algorithm>

#include "../define.h"
#include "astar_snake_launcher_10snakes.h"
#include "../ai/astar_10snakes.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// xxx.h - XXX.

using namespace sf;

Game10::Game10() {
	snakeAlive = NB_PLAYER10;
	generateObstacles();

	Astar10::init();

	for (int i = 0; i < NB_CRYSTAL10; i++) {
		crystal[i].spawn(obstacles, crystal);
	}
	Astar10::setTo(crystal[0].getPosition(), config);
}

void Game10::play(RenderWindow& win) {
	win.setFramerateLimit(config.getFPS());

	while (win.isOpen()) {
		handleEvents(win);

		if (config.isRunning()) {
			// Update weight of the nodes
			if (config.isWeightBFSOn())
				Astar10::hardReset(obstacles);
			else
				Astar10::softReset(obstacles);

			generateObstacles();
			for (int i = 0; i < NB_PLAYER10; i++) {
				if (!snake[i].isDead()) {
					// Set departure point
					Astar10::setFrom(snake[i].getHeadPosition());

					if (NB_CRYSTAL10 == 1) {
						snake[i].setPath(Astar10::findPath(config));
					}
					else {
						snake[i].clearPath();
						std::vector<Vector2i> path;
						//Calculate path to every crystal and keep the shortest
						for (int j = 0; j < NB_CRYSTAL10; j++) {
							Astar10::setTo(crystal[j].getPosition(), config);
							path = Astar10::findPath(config);
							if (!snake[i].hasPath() || snake[i].getPathSize() >= path.size())
								snake[i].setPath(path);
						}
					}

					// Follow path or stall if we couldn't find one
					if (!snake[i].followPath())
						stall(snake[i]);

					// Update obstacles by adding the snake's head new position to it
					obstacles.push_back(snake[i].getHeadPosition());
					if (collide(snake[i])) {
						// If a snake die we just regenerate obstacles
						generateObstacles();
						snakeAlive--;
						// End game when no snake alive
						if (snakeAlive == 0)
							return;
					}
					else {
						// Change weight of the node where the new head is
						Astar10::update(snake[i].getHeadPosition());
					}
				}
			}
		}

		gui.display(win, fixedObstacles, snake, crystal, config);
	}
}

bool Game10::collide(Snake10& s) {
	if (!s.isDead()) {
		// Check collision with obstacle
		if (s.isOutOfBounds() || std::count(obstacles.begin(), obstacles.end(), s.getHeadPosition()) >= 2) {
			s.die();
			return true;
		}

		// Check collision with crystal
		for (int i = 0; i < NB_CRYSTAL10; i++) {
			if (s.getHeadPosition() == crystal[i].getPosition()) {
				s.eat();
				crystal[i].spawn(obstacles, crystal);
				// If there is only 1 crystal we only update the AI's destination here
				// instead of every frame to gain speed
				if (NB_CRYSTAL10 == 1)
					Astar10::setTo(crystal[0].getPosition(), config);
			}
		}
	}
	return false;
}

void Game10::stall(Snake10& s) {
	Vector2i sHead = s.getHeadPosition();
	if (sHead.x < G_WIDTH - 1 && std::count(obstacles.begin(), obstacles.end(), sHead + Vector2i(1, 0)) == 0)
		s.move(RIGHT);
	else if (sHead.x > 0 && std::count(obstacles.begin(), obstacles.end(), sHead + Vector2i(-1, 0)) == 0)
		s.move(LEFT);
	else if (sHead.y > 0 && std::count(obstacles.begin(), obstacles.end(), sHead + Vector2i(0, -1)) == 0)
		s.move(UP);
	else if (sHead.y < G_HEIGHT - 1 && std::count(obstacles.begin(), obstacles.end(), sHead + Vector2i(0, 1)) == 0)
		s.move(DOWN);
	else
		s.move(NONE);
}

void Game10::addObstacle(Vector2i v) {
	if (std::find(fixedObstacles.begin(), fixedObstacles.end(), v) == fixedObstacles.end())
		fixedObstacles.push_back(v);
}

void Game10::removeObstacle(Vector2i v) {
	if(std::find(fixedObstacles.begin(), fixedObstacles.end(), v) != fixedObstacles.end())
		fixedObstacles.erase(std::find(fixedObstacles.begin(), fixedObstacles.end(), v));
}

void Game10::generateObstacles() {
	obstacles = fixedObstacles;
	for (int i = 0; i < NB_PLAYER10; i++) {
		if (!snake[i].isDead()) {
			std::vector<Vector2i> snakePos = snake[i].getPosition();
			// We don't add the last element of the snake in the list of obstacles
			// as it won't exist anymore once the snake move
			obstacles.reserve(obstacles.size() + snakePos.size() - 1);
			obstacles.insert(obstacles.end(), snakePos.begin(), snakePos.end() - 1);
		}
	}
}

void Game10::gameOver(sf::RenderWindow& win) {
	handleEvents(win);

	Event event;
	while (win.isOpen()) {
		while (win.pollEvent(event)) {
			gui.display(win, fixedObstacles, snake, crystal, config);
			if (event.type == Event::MouseWheelScrolled) {
				gui.scroll(Mouse::getPosition(win), (int)event.mouseWheelScroll.delta);
			}
			else if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					win.close();
			}
		}
	}
}

void Game10::handleEvents(sf::RenderWindow& win) {
	Event event;
	while (win.pollEvent(event)) {
		if (event.type == Event::Closed)
			win.close();
		else if (event.type == Event::MouseWheelScrolled)
			gui.scroll(Mouse::getPosition(win), (int)event.mouseWheelScroll.delta);
		else if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Escape)
				win.close();
			else if (event.key.code == K_PAUSE)
				config.togglePause();
			else if (event.key.code == K_UP_FPS) {
				config.changeFPS(1);
				win.setFramerateLimit(config.getFPS());
			}
			else if (event.key.code == K_DOWN_FPS) {
				config.changeFPS(-1);
				win.setFramerateLimit(config.getFPS());
			}
			else if (event.key.code == K_FPS_CAP) {
				config.toggleFPSCap();
				win.setFramerateLimit(config.getFPS());
			}
			else if (event.key.code == K_TOGGLE_BFS)
				config.toggleWeightBFS();
			else if (event.key.code == K_SHOW_COST)
				config.toggleDisplayCost();
			else if (event.key.code == K_SHOW_WEIGHT)
				config.toggleDisplayWeight();
			else if (event.key.code == K_SHOW_PATH)
				config.toggleDisplayPath();
		}
	}

	if (Mouse::isButtonPressed(M_ADD_OBS))
		addObstacle(Vector2i(Mouse::getPosition(win).x / S_SIZE, Mouse::getPosition(win).y / S_SIZE));
	if (Mouse::isButtonPressed(M_DEL_OBS))
		removeObstacle(Vector2i(Mouse::getPosition(win).x / S_SIZE, Mouse::getPosition(win).y / S_SIZE));

	/*if (Keyboard::isKeyPressed(Keyboard::Left))
		snek[0].move(LEFT);
	else if (Keyboard::isKeyPressed(Keyboard::Right))
		snek[0].move(RIGHT);
	else if (Keyboard::isKeyPressed(Keyboard::Up))
		snek[0].move(UP);
	else if (Keyboard::isKeyPressed(Keyboard::Down))
		snek[0].move(DOWN);
	else
		snek[0].move(NONE);*/
}