#include "engine.h"
#include "../game.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../components/cmp_music.h"

// SET09121 2017-8 TR2 001 - Games Engineering
// Picobots
// Version 0.7.0
// Alexander Barker 
// 40333139
// Last Updated on 14th April 2018
// scene_high_scores.cpp - This file only displays a blank screen.

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

void HighScoresScene::Load() {
	s2.stop();
	s3.stop();
	s1.playing();
}

void HighScoresScene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	Scene::UnLoad();
}

void HighScoresScene::Update(const double& dt) {
	Scene::Update(dt);
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
}

void HighScoresScene::Render() {
	Scene::Render();
}
