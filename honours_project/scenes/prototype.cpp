#include "engine.h"
#include "../game.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../components/cmp_music.h"
#include "../components/cmp_text.h"
#include "../add_entity.h"
#include <system_resources.h>
#include "system_renderer.h"
#include "prototype.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype
// Version 0.1.2
// Alexander Barker 
// 40333139
// Last Updated on 16th November 2018
// prototype.cpp - This file displays split-screen games of snake with metrics.

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
sf::Sprite titleSprite111b;
sf::Texture titleTexture111b;
sf::Vector2u titleSize111b;
sf::Vector2u windowSize111b;
int fadeCounter111 = 0;

sf::SoundBuffer effect45;
sf::Sound sound45;

/*
void PrototypeScene::SetTitle1() {
	titleTexture111b = *Resources::load<Texture>("littletitle.png");
	float x1 = Engine::GetWindow().getSize().x;
	float y1 = Engine::GetWindow().getSize().y;
	titleSize111b = titleTexture111b.getSize(); //Get size of texture.
	windowSize111b = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSize111b.x / titleSize111b.x;
	float ScaleY = (float)windowSize111b.y / titleSize111b.y;     //Calculate scale.
	titleSprite111b.setTexture(titleTexture111b);
	titleSprite111b.setPosition(windowSize111b.x / 9.2, windowSize111b.y / 12.5);
	titleSprite111b.setScale(ScaleX / 8, ScaleY / 8);
	titleSprite111b.setOrigin(titleSize111b.x / 2, titleSize111b.y / 2);
}
*/

void PrototypeScene::Load() {
	//s2.stop();
	//s3.stop();
	//s1.playing();

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();

	float temp = y2 / 44;

	ls::loadLevelFile("res/prototypelevel.txt", temp);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * temp);
	ls::setOffset(Vector2f(30, ho));

	effect45.loadFromFile("res/sound/explosion.ogg");
	sound45.setBuffer(effect45);
	//SetTitle1();

	{
		auto txtSnakeTitle = makeEntity();
		auto t = txtSnakeTitle->addComponent<TextComponent>("Snake Prototype");
		t->getText().setCharacterSize(38);
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2 + 20, t->getText().getGlobalBounds().height / 1.2);
		txtSnakeTitle->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y / 16));

	}

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

void PrototypeScene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void PrototypeScene::Update(const double& dt) {
	const auto pp = player->getPosition();
	if (ls::getTileAt(pp) == ls::END) {
		Engine::ChangeScene((Scene*)&prototype);
	}
	else if (!player->isAlive()) {
		sound45.play();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		Engine::ChangeScene((Scene*)&prototype);
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
		//s1.play1(0, true);
		Engine::ChangeScene(&menu);
	}

	Scene::Update(dt);
}

void PrototypeScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();

	if (fadeCounter111 <= 250) {
		titleSprite111b.setColor(sf::Color(255, 255, 255, fadeCounter111));
		fadeCounter111--;
		Renderer::queue(&titleSprite111b);
	}
	else {
		fadeCounter111 = 0;
		Renderer::queue(&titleSprite111b);
	}
}
