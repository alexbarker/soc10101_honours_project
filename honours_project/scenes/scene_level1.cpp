#include "engine.h"
#include "../app.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <system_resources.h>
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../components/cmp_music.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_basic_movement.h"
#include "../components/cmp_state_machine.h"
#include "../components/cmp_physics.h"
#include "system_renderer.h"
#include "scene_level1.h"
#include "../add_entity.h"
#include "../components/cmp_text.h"
#include "../components/stdafx.h"
#include <SFML/Graphics.hpp>

#include "../define.h"
#include "../astar_snake_launcher.h"
#include "../components/cmp_snake_body.h"

// SET09121 2017-8 TR2 001 - Games Engineering
// Picobots
// Version 0.7.0
// Alexander Barker 
// 40333139
// Last Updated on 1st May 2018
// scene_level1.cpp - This file is used to call for loads, updates and renders for Level 1.

using namespace std;
using namespace sf;

/*
int oops() {
	RenderWindow win(VideoMode(W_WIDTH, W_HEIGHT), "Snake", Style::Default);
	win.setKeyRepeatEnabled(true);

	srand(SEED);

	Game g;
	g.play(win);
	g.gameOver(win);

	return EXIT_SUCCESS;
}
*/
void Level1Scene::Load() {

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();

	float temp = y2 / 44;

	ls::loadLevelFile("res/level1.txt", temp);

	AddEntity::makeWalls(this);

	//oops();
}

void Level1Scene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	ls::unload();
	Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

	Event event;
	while (Engine::GetWindow().pollEvent(event)) {
		if (event.type == sf::Event::Resized) {
			UnLoad();
			Engine::GetWindow().setSize(sf::Vector2u(event.size.width, event.size.height));
			Engine::GetWindow().display();
			Load();
		}
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::R)) {
		UnLoad();
		Load();
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
		Engine::ChangeScene(&menu);
	}

	Scene::Update(dt);
}

void Level1Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}
