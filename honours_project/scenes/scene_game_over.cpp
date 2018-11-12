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
// scene_game_over.cpp - This file is unused.

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

void GameOverScene::Load() {
}

void GameOverScene::UnLoad() {
	Scene::UnLoad();
}

void GameOverScene::Update(const double& dt) {
	Scene::Update(dt);
}

void GameOverScene::Render() {
	Scene::Render();
}
