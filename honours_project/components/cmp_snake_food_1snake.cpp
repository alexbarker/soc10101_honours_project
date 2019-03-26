#include "stdafx.h"
#include "../define.h"
#include "cmp_snake_food_1snake.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// xxx.h - XXX.

using namespace sf;

Crystal1::Crystal1() {
	pos.x = 0;
	pos.y = 0;

	texture.loadFromFile(T_CRYSTAL);
	sprite.setTexture(texture);
	sprite.scale((float)S_SIZE / T_SIZE, (float)S_SIZE / T_SIZE);
}

void Crystal1::spawn(std::vector<Vector2i> obstacles, Crystal1 crystal[NB_CRYSTAL1]) {
	bool occupied[G_WIDTH][G_HEIGHT] = { false };
	for (auto v : obstacles) {
		occupied[v.x][v.y] = true;
	}
	for (int i = 0; i < NB_CRYSTAL1; i++) {
		Vector2i apos = crystal[i].getPosition();
		occupied[apos.x][apos.y] = true;
	}

	do {
		pos.x = rand() % (G_WIDTH);
		pos.y = rand() % (G_HEIGHT);
		sprite.setPosition((float)pos.x*S_SIZE, (float)pos.y*S_SIZE);
	} while (occupied[pos.x][pos.y]);
}

void Crystal1::display(RenderWindow& win) {
	win.draw(sprite);
}

Vector2i Crystal1::getPosition() const{
	return pos;
}