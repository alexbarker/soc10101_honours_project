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
#include "scene_level7.h"
#include "../add_entity.h"

// SET09121 2017-8 TR2 001 - Games Engineering
// Picobots
// Version 0.7.0
// Alexander Barker 
// 40333139
// Last Updated on 1st May 2018
// scene_level7.cpp - This file is used to call for loads, updates and renders for Level 7.

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

sf::Sprite backgroundSprite7a;
sf::Texture backgroungTexture7a;
sf::Vector2u backgroundSize7a;  //Added to store texture size.
sf::Vector2u windowSize7a;   //Added to store window size.
sf::Sprite titleSprite7b;
sf::Texture titleTexture7b;
sf::Vector2u titleSize7b;
sf::Vector2u windowSize7b;
int fadeCounter7 = 0;

sf::SoundBuffer effect10;
sf::Sound sound10;

void Level7Scene::SetTitle() {
	titleTexture7b = *Resources::load<Texture>("title.png");
	float x1 = Engine::GetWindow().getSize().x;
	float y1 = Engine::GetWindow().getSize().y;
	titleSize7b = titleTexture7b.getSize(); //Get size of texture.
	windowSize7b = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSize7b.x / titleSize7b.x;
	float ScaleY = (float)windowSize7b.y / titleSize7b.y;     //Calculate scale.
	titleSprite7b.setTexture(titleTexture7b);
	titleSprite7b.setPosition(windowSize7b.x / 9.2, windowSize7b.y / 12.5);
	titleSprite7b.setScale(ScaleX / 6, ScaleY / 6);
	titleSprite7b.setOrigin(titleSize7b.x / 2, titleSize7b.y / 2);
}

void Level7Scene::SetBackground() {
	backgroungTexture7a = *Resources::load<Texture>("mainfullscreen.png");
	float x = Engine::GetWindow().getSize().x;
	float y = Engine::GetWindow().getSize().y;
	backgroundSize7a = backgroungTexture7a.getSize(); //Get size of texture.
	windowSize7a = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSize7a.x / backgroundSize7a.x;
	float ScaleY = (float)windowSize7a.y / backgroundSize7a.y;     //Calculate scale.
	backgroundSprite7a.setTexture(backgroungTexture7a);
	backgroundSprite7a.setPosition(0, 0);
	backgroundSprite7a.setScale(ScaleX, ScaleY);
	backgroundSprite7a.setOrigin(0, 0);
}

void Level7Scene::Load() {
	s2.playing();

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();

	float temp = y2 / 44;

	ls::loadLevelFile("res/level7.txt", temp);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * temp);
	ls::setOffset(Vector2f(x2 / 4.72, ho));

	effect10.loadFromFile("res/sound/explosion.ogg");
	sound10.setBuffer(effect10);

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
		AddEntity::makeEnergyCrystal(this, (pos + Vector2f(0, -10)));
	}
}

void Level7Scene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level7Scene::Update(const double& dt) {

	const auto pp = player->getPosition();
	if (ls::getTileAt(pp) == ls::END) {
		s2.stop();
		s3.play3(2, true);
		s3.playing();
		Engine::ChangeScene((Scene*)&bosslevel);
	}
	else if (!player->isAlive()) {
		sound10.play();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		Engine::ChangeScene((Scene*)&level7);
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

void Level7Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();

	if (fadeCounter7 <= 250) {
		titleSprite7b.setColor(sf::Color(255, 255, 255, fadeCounter7));
		fadeCounter7--;
		Renderer::queue(&backgroundSprite7a);
		Renderer::queue(&titleSprite7b);
	}
	else {
		fadeCounter7 = 0;
		Renderer::queue(&backgroundSprite7a);
		Renderer::queue(&titleSprite7b);
	}
}
