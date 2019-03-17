#include "stdafx.h"
#include <iostream>

#include "../define.h"
#include "cmp_snake_body.h"

using namespace sf;

Snake::Snake() {
	length = 5;
	score = 0;
	dead = false;

	pos.resize(length);
	spawn();	

	if (NB_PLAYER == 1)
		color = Color::White;
	// Random color for visual purposes
	else
		color = Color(32 + rand() % 224, 32 + rand() % 224, 32 + rand() % 224, 255);
	texture.loadFromFile(T_SNAKE);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, T_SIZE, T_SIZE));
	sprite.setColor(color);
	sprite.setOrigin(T_SIZE / 2, T_SIZE / 2);
	sprite.scale((float)S_SIZE / T_SIZE, (float)S_SIZE / T_SIZE);
}

Snake::Snake(Snake& s) {
	length = s.length;
	direction = s.direction;
	pos = s.pos;
	path = s.path;
	texture = s.texture;
	sprite = s.sprite;
	color = s.color;
}

void Snake::spawn() {
	// Random position and random direction, same as with the apple, trial and error until
	// we get a valid position
	// Not optimized but we only do it once at the beginning of the game anyway

	// I don't check for other snakes so sometimes they will spawn at the same place and one
	// of them will die instantly which is sad but anyway it's not a big difference between
	// having 50 snakes or having 45
	// Also sometimes the head are at different places but the body intertwin, which is why
	// most of the time they appear like that at the beginning but it fix itself once they
	// start to move and don't happen again
	do {
		pos[0].x = rand() % G_WIDTH;
		pos[0].y = rand() % G_HEIGHT;
		int dirTab[4] = { RIGHT, LEFT, UP, DOWN };
		direction = dirTab[rand() % 4];
	} while ((pos[0].x < length - 1 && direction == RIGHT)
		|| (pos[0].x > G_WIDTH - length && direction == LEFT)
		|| (pos[0].y < length - 1 && direction == DOWN)
		|| (pos[0].y > G_HEIGHT - length && direction == UP));

	for (int i = 1; i < length; i++) {
		if (direction == LEFT || direction == RIGHT)
			pos[i].x = pos[0].x - i * direction;
		else
			pos[i].x = pos[0].x;

		if (direction == UP || direction == DOWN)
			pos[i].y = pos[0].y + i * direction / 2;
		else
			pos[i].y = pos[0].y;
	}
}

// Just change the first element of the vector to a new position and update all the others
// to the values of the one before it
// The #define are used to make it easier to read and to calculate
// If the direction is the opposite of the current direction, we just keep going with the
// current one as the snake can't go in reverse
// NONE = current direction
void Snake::move(int dir) {
	if (dir == NONE || dir == -direction)
		dir = direction;
	direction = dir;

	for (int i = length-1; i > 0; i--) {
		pos[i].x = pos[i - 1].x;
		pos[i].y = pos[i - 1].y;
	}

	switch (dir) {
		case LEFT:
			pos[0].x--;
			break;
		case RIGHT:
			pos[0].x++;
			break;
		case UP:
			pos[0].y--;
			break;
		case DOWN:
			pos[0].y++;
			break;
	}
}

// We go to the first last element of the path vector and remove it from the vector
// If it's not a valid position (i.e. if it's more than one distance away from the snake's head)
// we clear the path and just use current direction
bool Snake::followPath() {
	if (hasPath()) {
		Vector2i dest = path.at(path.size() - 1) - pos[0];

		if (dest.x == 1)
			move(RIGHT);
		else if (dest.x == -1)
			move(LEFT);
		else if (dest.y == 1)
			move(DOWN);
		else if (dest.y == -1)
			move(UP);
		else {
			path.clear();
			return false;
		}

		path.pop_back();

		return true;
	}

	return false;
}

void Snake::setPath(const std::vector<sf::Vector2i>& p) {
	path = p;
}

void Snake::clearPath() {
	path.clear();
}

void Snake::eat() {
	score++;
	pos.push_back(pos[length++-1]);
}

void Snake::die() {
	dead = true;
}

// Same as in GUI, ugly calculations for nice visuals, not worth reading
// Lots of ifs to check the rotation of the sprites, because once again i was
// experimenting with SFML and the possibility to cut images in smaller part etc.
void Snake::display(RenderWindow& win, Config& config) {
	sprite.setPosition((float)pos[0].x * S_SIZE + S_SIZE / 2, (float)pos[0].y * S_SIZE + S_SIZE / 2);
	sprite.setTextureRect(IntRect(0, 0, T_SIZE, T_SIZE));

	if (direction == RIGHT)
		sprite.setRotation(0);
	else if (direction == DOWN)
		sprite.setRotation(90);
	else if (direction == LEFT)
		sprite.setRotation(180);
	else if (direction == UP)
		sprite.setRotation(270);

	win.draw(sprite);

	for (int i = 1; i < length - 1; i++) {
		Vector2i tmp = pos[i - 1] - pos[i + 1];
		Vector2i tmpPlus = pos[i + 1] - pos[i];
		Vector2i tmpMoins = pos[i] - pos[i-1];

		if (tmp.x != 0 && tmp.y != 0) {
			sprite.setTextureRect(IntRect(2 * T_SIZE, 0, T_SIZE, T_SIZE));
			if ((tmpPlus.y == -1 && tmpMoins.x == -1) 
				|| (tmpPlus.x == 1 && tmpMoins.y == 1))
				sprite.setRotation(0);
			else if ((tmpPlus.x == 1 && tmpMoins.y == -1) 
				|| (tmpPlus.y == 1 && tmpMoins.x == -1))
				sprite.setRotation(90);
			else if ((tmpPlus.y == 1 && tmpMoins.x == 1) 
				|| (tmpPlus.x == -1 && tmpMoins.y == -1))
				sprite.setRotation(180);
			else if ((tmpPlus.x == -1 && tmpMoins.y == 1) 
				|| (tmpPlus.y == -1 && tmpMoins.x == 1))
				sprite.setRotation(270);
		}
		else {
			sprite.setTextureRect(IntRect(T_SIZE, 0, T_SIZE, T_SIZE));
			if (tmp.x == -2)
				sprite.setRotation(0);
			else if (tmp.y == -2)
				sprite.setRotation(90);
			else if (tmp.x == 2)
				sprite.setRotation(180);
			else if (tmp.y == 2)
				sprite.setRotation(270);
		}

		sprite.setPosition((float)pos[i].x*S_SIZE + S_SIZE / 2, (float)pos[i].y*S_SIZE + +S_SIZE / 2);
		win.draw(sprite);
	}

	if(pos[length - 2].x - pos[length - 1].x == 1)
		sprite.setRotation(0);
	else if (pos[length - 2].y - pos[length - 1].y == 1)
		sprite.setRotation(90);
	else if (pos[length - 2].x - pos[length - 1].x == -1)
		sprite.setRotation(180);
	else if (pos[length - 2].y - pos[length - 1].y == -1)
		sprite.setRotation(270);

	sprite.setPosition((float)pos[length-1].x * S_SIZE + S_SIZE / 2, (float)pos[length - 1].y * S_SIZE + S_SIZE / 2);
	sprite.setTextureRect(IntRect(3*T_SIZE, 0, T_SIZE, T_SIZE));
	win.draw(sprite);

	if (config.isDisplayPathOn()) {
		RectangleShape rect;
		rect.setFillColor(Color(color.r, color.g, color.b, 32));
		rect.setSize(Vector2f(S_SIZE, S_SIZE));
		for (auto v : path) {
			rect.setPosition(v.x * S_SIZE, v.y * S_SIZE);
			win.draw(rect);
		}
	}
}

bool Snake::isOutOfBounds() const {
	return pos[0].x >= G_WIDTH 
		|| pos[0].x < 0 
		|| pos[0].y >= G_HEIGHT 
		|| pos[0].y < 0;
}

bool Snake::hasPath() const {
	return !path.empty();
}

int Snake::getScore() const {
	return score;
}

bool Snake::isDead() const {
	return dead;
}

Color Snake::getColor() const {
	return color;
}

Vector2i Snake::getHeadPosition() const  {
	return pos[0];
}

std::vector<Vector2i> Snake::getPosition() const {
	return pos;
}

int Snake::getPathSize() const {
	return (int)path.size();
}