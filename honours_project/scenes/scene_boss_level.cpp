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
#include "scene_boss_level.h"
#include "../add_entity.h"

// SET09121 2017-8 TR2 001 - Games Engineering
// Picobots
// Version 0.7.0
// Alexander Barker 
// 40333139
// Last Updated on 1st May 2018
// scene_boss_level.cpp - This file is used to update and render the boss scene.

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

sf::Sprite backgroundSprite8a;
sf::Texture backgroungTexture8a;
sf::Vector2u backgroundSize8a;  //Added to store texture size.
sf::Vector2u windowSize8a;   //Added to store window size.
sf::Sprite titleSprite8b;
sf::Texture titleTexture8b;
sf::Vector2u titleSize8b;
sf::Vector2u windowSize8b;
int fadeCounter8 = 0;

sf::SoundBuffer effect11;
sf::Sound sound11;

void BossLevelScene::SetTitle() {
	titleTexture8b = *Resources::load<Texture>("title.png");
	float x1 = Engine::GetWindow().getSize().x;
	float y1 = Engine::GetWindow().getSize().y;
	titleSize8b = titleTexture8b.getSize(); //Get size of texture.
	windowSize8b = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSize8b.x / titleSize8b.x;
	float ScaleY = (float)windowSize8b.y / titleSize8b.y;     //Calculate scale.
	titleSprite8b.setTexture(titleTexture8b);
	titleSprite8b.setPosition(windowSize8b.x / 9.2, windowSize8b.y / 12.5);
	titleSprite8b.setScale(ScaleX / 6, ScaleY / 6);
	titleSprite8b.setOrigin(titleSize8b.x / 2, titleSize8b.y / 2);
}

void BossLevelScene::SetBackground() {
	backgroungTexture8a = *Resources::load<Texture>("mainfullscreen.png");
	float x = Engine::GetWindow().getSize().x;
	float y = Engine::GetWindow().getSize().y;
	backgroundSize8a = backgroungTexture8a.getSize(); //Get size of texture.
	windowSize8a = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSize8a.x / backgroundSize8a.x;
	float ScaleY = (float)windowSize8a.y / backgroundSize8a.y;     //Calculate scale.
	backgroundSprite8a.setTexture(backgroungTexture8a);
	backgroundSprite8a.setPosition(0, 0);
	backgroundSprite8a.setScale(ScaleX, ScaleY);
	backgroundSprite8a.setOrigin(0, 0);
}

void BossLevelScene::Load() {
	s3.playing();

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();

	float temp = y2 / 44;

	ls::loadLevelFile("res/bosslevel.txt", temp);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * temp);
	ls::setOffset(Vector2f(x2 / 4.72, ho));

	effect11.loadFromFile("res/sound/explosion.ogg");
	sound11.setBuffer(effect11);

	SetBackground();
	SetTitle();

	player = AddEntity::makePlayer(this, Vector2f(x2 / 2, y2 / 2));

	auto enemy2 = ls::findTiles(ls::ENEMY2);
	for (auto n : enemy2) {
		auto pos = ls::getTilePosition(n);
		pos += Vector2f(10.f, 10.f);
		AddEntity::makeEnemy2(this, pos);
	}

	auto enemy3 = ls::findTiles(ls::ENEMY3);
	for (auto n : enemy3) {
		auto pos = ls::getTilePosition(n);
		pos += Vector2f(10.f, 10.f);
		AddEntity::makeEnemy3(this, pos);
	}

	AddEntity::makeWalls(this);
}

void BossLevelScene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void BossLevelScene::Update(const double& dt) {

	const auto pp = player->getPosition();
	if (ls::getTileAt(pp) == ls::END) {
		Engine::ChangeScene((Scene*)&level1);
	}
	else if (ls::getTileAt(pp) == ls::ENDGAME) {
		s1.play1(0, true);
		Engine::ChangeScene((Scene*)&menu);
	}
	else if (!player->isAlive()) {
		sound11.play();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		Engine::ChangeScene((Scene*)&bosslevel);
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

void BossLevelScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();

	if (fadeCounter8 <= 250) {
		titleSprite8b.setColor(sf::Color(255, 255, 255, fadeCounter8));
		fadeCounter8--;
		Renderer::queue(&backgroundSprite8a);
		Renderer::queue(&titleSprite8b);
	}
	else {
		fadeCounter8 = 0;
		Renderer::queue(&backgroundSprite8a);
		Renderer::queue(&titleSprite8b);
	}
}
