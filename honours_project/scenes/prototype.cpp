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
	ls::setOffset(Vector2f(100, ho));

	{
		auto txtSnakeTitle = makeEntity();
		auto t = txtSnakeTitle->addComponent<TextComponent>("Snake Prototype");
		t->getText().setCharacterSize(38);
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2 + 20, t->getText().getGlobalBounds().height / 1.2);
		txtSnakeTitle->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 50.f));

	}

	AddEntity::makeWalls(this);
}

void PrototypeScene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	Scene::UnLoad();
}

void PrototypeScene::Update(const double& dt) {
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

void PrototypeScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}
