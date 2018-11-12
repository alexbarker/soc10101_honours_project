#include "engine.h"
#include "../game.h"
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
#include "scene_level4.h"
#include "../add_entity.h"

// SET09121 2017-8 TR2 001 - Games Engineering
// Picobots
// Version 0.7.0
// Alexander Barker 
// 40333139
// Last Updated on 1st May 2018
// scene_level4.cpp - This file is used to call for loads, updates and renders for Level 4.

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

sf::Sprite backgroundSprite4a;
sf::Texture backgroungTexture4a;
sf::Vector2u backgroundSize4a;  //Added to store texture size.
sf::Vector2u windowSize4a;   //Added to store window size.
sf::Sprite titleSprite4b;
sf::Texture titleTexture4b;
sf::Vector2u titleSize4b;
sf::Vector2u windowSize4b;
int fadeCounter4 = 0;

sf::SoundBuffer effect7;
sf::Sound sound7;

void Level4Scene::SetTitle() {
	titleTexture4b = *Resources::load<Texture>("title.png");
	float x1 = Engine::GetWindow().getSize().x;
	float y1 = Engine::GetWindow().getSize().y;
	titleSize4b = titleTexture4b.getSize(); //Get size of texture.
	windowSize4b = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSize4b.x / titleSize4b.x;
	float ScaleY = (float)windowSize4b.y / titleSize4b.y;     //Calculate scale.
	titleSprite4b.setTexture(titleTexture4b);
	titleSprite4b.setPosition(windowSize4b.x / 9.2, windowSize4b.y / 12.5);
	titleSprite4b.setScale(ScaleX / 6, ScaleY / 6);
	titleSprite4b.setOrigin(titleSize4b.x / 2, titleSize4b.y / 2);
}

void Level4Scene::SetBackground() {
	backgroungTexture4a = *Resources::load<Texture>("mainfullscreen.png");
	float x = Engine::GetWindow().getSize().x;
	float y = Engine::GetWindow().getSize().y;
	backgroundSize4a = backgroungTexture4a.getSize(); //Get size of texture.
	windowSize4a = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSize4a.x / backgroundSize4a.x;
	float ScaleY = (float)windowSize4a.y / backgroundSize4a.y;     //Calculate scale.
	backgroundSprite4a.setTexture(backgroungTexture4a);
	backgroundSprite4a.setPosition(0, 0);
	backgroundSprite4a.setScale(ScaleX, ScaleY);
	backgroundSprite4a.setOrigin(0, 0);
}

void Level4Scene::Load() {
	s2.playing();

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();

	float temp = y2 / 44;

	ls::loadLevelFile("res/level4.txt", temp);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * temp);
	ls::setOffset(Vector2f(x2 / 4.72, ho));

	effect7.loadFromFile("res/sound/explosion.ogg");
	sound7.setBuffer(effect7);

	SetBackground();
	SetTitle();

	player = AddEntity::makePlayer(this, Vector2f(x2 / 2, y2 / 2));

	auto sent = ls::findTiles(ls::ENEMY);
	for (auto n : sent) {
		auto pos = ls::getTilePosition(n);
		pos += Vector2f(10.f, 10.f);
		AddEntity::makeSentinel(this, pos);
	}

	auto enemy1 = ls::findTiles(ls::ENEMY1);
	for (auto n : enemy1) {
		auto pos = ls::getTilePosition(n);
		pos += Vector2f(10.f, 10.f);
		AddEntity::makeEnemy1(this, (pos + Vector2f(0, 0)));
	}

	auto enemy2 = ls::findTiles(ls::ENEMY2);
	for (auto n : enemy2) {
		auto pos = ls::getTilePosition(n);
		pos += Vector2f(10.f, 10.f);
		AddEntity::makeEnemy2(this, pos);
	}

	AddEntity::makeWalls(this);

	auto energyCrystals = ls::findTiles(ls::CRYSTAL);
	for (auto nn : energyCrystals) {
		auto pos = ls::getTilePosition(nn);
		pos += Vector2f(10.f, 10.f);
		AddEntity::makeEnergyCrystal(this, (pos + Vector2f(0, 10)));
	}
}

void Level4Scene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level4Scene::Update(const double& dt) {

	const auto pp = player->getPosition();
	if (ls::getTileAt(pp) == ls::END) {
		Engine::ChangeScene((Scene*)&level5);
	}
	else if (!player->isAlive()) {
		sound7.play();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		Engine::ChangeScene((Scene*)&level4);
	}

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
		s1.play1(0, true);
		Engine::ChangeScene(&menu);
	}
	Scene::Update(dt);
}

void Level4Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();

	if (fadeCounter4 <= 250) {
		titleSprite4b.setColor(sf::Color(255, 255, 255, fadeCounter4));
		fadeCounter4--;
		Renderer::queue(&backgroundSprite4a);
		Renderer::queue(&titleSprite4b);
	}
	else {
		fadeCounter4 = 0;
		Renderer::queue(&backgroundSprite4a);
		Renderer::queue(&titleSprite4b);
	}
}
