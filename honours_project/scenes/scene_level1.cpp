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
#include "scene_level1.h"
#include "../add_entity.h"
#include "../components/cmp_text.h"

// SET09121 2017-8 TR2 001 - Games Engineering
// Picobots
// Version 0.7.0
// Alexander Barker 
// 40333139
// Last Updated on 1st May 2018
// scene_level1.cpp - This file is used to call for loads, updates and renders for Level 1.

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

sf::Sprite backgroundSprite1a;
sf::Texture backgroungTexture1a;
sf::Vector2u backgroundSize1a;  //Added to store texture size.
sf::Vector2u windowSize1a;   //Added to store window size.
sf::Sprite titleSprite1b;
sf::Texture titleTexture1b;
sf::Vector2u titleSize1b;
sf::Vector2u windowSize1b;
int fadeCounter1 = 0;

sf::SoundBuffer effect4;
sf::Sound sound4;

void Level1Scene::SetTitle() {
	titleTexture1b = *Resources::load<Texture>("title.png");
	float x1 = Engine::GetWindow().getSize().x;
	float y1 = Engine::GetWindow().getSize().y;
	titleSize1b = titleTexture1b.getSize(); //Get size of texture.
	windowSize1b = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSize1b.x / titleSize1b.x;
	float ScaleY = (float)windowSize1b.y / titleSize1b.y;     //Calculate scale.
	titleSprite1b.setTexture(titleTexture1b);
	titleSprite1b.setPosition(windowSize1b.x / 9.2, windowSize1b.y / 12.5);
	titleSprite1b.setScale(ScaleX / 6, ScaleY / 6);
	titleSprite1b.setOrigin(titleSize1b.x / 2, titleSize1b.y / 2);
}

void Level1Scene::SetBackground() {
	backgroungTexture1a = *Resources::load<Texture>("mainfullscreen.png");
	float x = Engine::GetWindow().getSize().x;
	float y = Engine::GetWindow().getSize().y;
	//if(x2 > 1900){backgroungTexture1a = *Resources::load<Texture>("mainfullscreen.png");}
	//else{backgroungTexture1a = *Resources::load<Texture>("main1.png");}
	backgroundSize1a = backgroungTexture1a.getSize(); //Get size of texture.
	windowSize1a = Engine::GetWindow().getSize();
	float ScaleX = (float)windowSize1a.x / backgroundSize1a.x;
	float ScaleY = (float)windowSize1a.y / backgroundSize1a.y;     //Calculate scale.
	backgroundSprite1a.setTexture(backgroungTexture1a);
	backgroundSprite1a.setPosition(0, 0);
	backgroundSprite1a.setScale(ScaleX, ScaleY);
	backgroundSprite1a.setOrigin(0, 0);
}

void Level1Scene::Load() {
	s1.stop();
	s3.stop();
	s2.play2(1, true);

	//for(auto ent : ents.list) {ent->setForDelete();}
	//ents.list.clear();

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();

	float temp = y2 / 44;

	ls::loadLevelFile("res/level1.txt", temp);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * temp);
	ls::setOffset(Vector2f(x2 / 4.72, ho));

	effect4.loadFromFile("res/sound/explosion.ogg");
	sound4.setBuffer(effect4);

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
		AddEntity::makeEnemy1(this, (pos + Vector2f(0, 20)));
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
		AddEntity::makeEnergyCrystal(this, pos);
	}
}

void Level1Scene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

	const auto pp = player->getPosition();
	if (ls::getTileAt(pp) == ls::END) {
		Engine::ChangeScene((Scene*)&level2);
	}
	else if (!player->isAlive()) {
		sound4.play();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		Engine::ChangeScene((Scene*)&level1);
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

void Level1Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();

	if (fadeCounter1 <= 250) {
		titleSprite1b.setColor(sf::Color(255, 255, 255, fadeCounter1));
		fadeCounter1--;
		Renderer::queue(&backgroundSprite1a);
		Renderer::queue(&titleSprite1b);
	}
	else {
		fadeCounter1 = 0;
		Renderer::queue(&backgroundSprite1a);
		Renderer::queue(&titleSprite1b);
	}
}
