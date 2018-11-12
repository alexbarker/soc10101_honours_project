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

// SET09121 2017-8 TR2 001 - Games Engineering
// Picobots
// Version 0.7.0
// Alexander Barker 
// 40333139
// Last Updated on 1st May 2018
// scene_tutorial.cpp - This file is used to call for loads, updates and renders for Tutorial.

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

void TutorialScene::Load() {
	s2.stop();
	s3.stop();
	s1.playing();

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();

	float temp = y2 / 44;

	ls::loadLevelFile("res/tutoriallevel.txt", temp);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * temp);
	ls::setOffset(Vector2f(x2 / 4.72, ho));

	{
		auto txtTutorialTitle = makeEntity();
		auto t = txtTutorialTitle->addComponent<TextComponent>("Tutorial");
		t->getText().setCharacterSize(53);
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtTutorialTitle->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));

		auto txtTutorialBack = makeEntity();
		auto t2 = txtTutorialBack->addComponent<TextComponent>("Press Esc to return to Title");
		t2->getText().setCharacterSize(24);
		t2->getText().setOrigin(t2->getText().getGlobalBounds().width / 2, t2->getText().getGlobalBounds().height / 2);
		txtTutorialBack->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, (Engine::GetWindow().getSize().y - (Engine::GetWindow().getSize().y / 9))));

		auto txtTutorialLeft = makeEntity();
		auto t3 = txtTutorialLeft->addComponent<TextComponent>("Movement");
		t3->getText().setCharacterSize(24);
		t3->getText().setOrigin(t3->getText().getGlobalBounds().width / 2, t3->getText().getGlobalBounds().height / 2);
		auto t4 = txtTutorialLeft->addComponent<TextComponent>("Press LEFT ARROW key to move left.");
		t4->getText().setCharacterSize(14);
		t4->getText().setOrigin(t4->getText().getGlobalBounds().width / 2, t4->getText().getGlobalBounds().height / 2 - 50);
		auto t5 = txtTutorialLeft->addComponent<TextComponent>("Press RIGHT ARROW key to move right.");
		t5->getText().setCharacterSize(14);
		t5->getText().setOrigin(t5->getText().getGlobalBounds().width / 2, t5->getText().getGlobalBounds().height / 2 - 100);
		txtTutorialLeft->setPosition(Vector2f(Engine::GetWindow().getSize().x / 9, (Engine::GetWindow().getSize().y / 9)));
		auto t6 = txtTutorialLeft->addComponent<TextComponent>("Press DOWN ARROW key to move down.");
		t6->getText().setCharacterSize(14);
		t6->getText().setOrigin(t6->getText().getGlobalBounds().width / 2, t6->getText().getGlobalBounds().height / 2 - 150);
		txtTutorialLeft->setPosition(Vector2f(Engine::GetWindow().getSize().x / 9, (Engine::GetWindow().getSize().y / 9)));
		auto t7 = txtTutorialLeft->addComponent<TextComponent>("Press UP ARROW key to move up.");
		t7->getText().setCharacterSize(14);
		t7->getText().setOrigin(t7->getText().getGlobalBounds().width / 2, t7->getText().getGlobalBounds().height / 2 - 200);
		txtTutorialLeft->setPosition(Vector2f(Engine::GetWindow().getSize().x / 9, (Engine::GetWindow().getSize().y / 9)));

		auto txtTutorialRight = makeEntity();
		auto t8 = txtTutorialRight->addComponent<TextComponent>("Controls");
		t8->getText().setCharacterSize(24);
		t8->getText().setOrigin(t8->getText().getGlobalBounds().width / 2, t8->getText().getGlobalBounds().height / 2);
		auto t9 = txtTutorialRight->addComponent<TextComponent>("Press R to restart.");
		t9->getText().setCharacterSize(14);
		t9->getText().setOrigin(t9->getText().getGlobalBounds().width / 2, t9->getText().getGlobalBounds().height / 2 - 50);
		auto t10 = txtTutorialRight->addComponent<TextComponent>("Press F for fullscreen.");
		t10->getText().setCharacterSize(14);
		t10->getText().setOrigin(t10->getText().getGlobalBounds().width / 2, t10->getText().getGlobalBounds().height / 2 - 100);
		auto t11 = txtTutorialRight->addComponent<TextComponent>("Press D to exit fullscreen.");
		t11->getText().setCharacterSize(14);
		t11->getText().setOrigin(t11->getText().getGlobalBounds().width / 2, t11->getText().getGlobalBounds().height / 2 - 150);
		auto t12 = txtTutorialRight->addComponent<TextComponent>("Press ESC to return to title.");
		t12->getText().setCharacterSize(14);
		t12->getText().setOrigin(t12->getText().getGlobalBounds().width / 2, t12->getText().getGlobalBounds().height / 2 - 200);
		auto t13 = txtTutorialRight->addComponent<TextComponent>("Press Q to quit.");
		t13->getText().setCharacterSize(14);
		t13->getText().setOrigin(t13->getText().getGlobalBounds().width / 2, t13->getText().getGlobalBounds().height / 2 - 250);
		txtTutorialRight->setPosition(Vector2f(Engine::GetWindow().getSize().x - (Engine::GetWindow().getSize().x / 9), (Engine::GetWindow().getSize().y / 9)));
	}

	player = AddEntity::makeTutorialPlayer(this, Vector2f(Engine::getWindowSize().x / 2, Engine::getWindowSize().y / 2));
	AddEntity::makeWalls(this);
}

void TutorialScene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void TutorialScene::Update(const double& dt) {
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

void TutorialScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}
