#include "engine.h"
#include "../app.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../components/cmp_music.h"
#include "../components/cmp_text.h"
#include "../add_entity.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// scene_tutorial.cpp - This file is used to call for loads, updates and renders for Tutorial.

using namespace std;
using namespace sf;

void TutorialScene::Load() {

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	Engine::GetWindow().setSize(sf::Vector2u(x2, y2));
	Engine::GetWindow().display();

	float temp = y2 / 44;

	ls::loadLevelFile("res/tutorial.txt", temp);
	auto ho = Engine::getWindowSize().y - (ls::getHeight() * temp);
	ls::setOffset(Vector2f(x2 / 4.72, ho));
	
	{
		auto txtTutorialTitle = makeEntity();
		auto t = txtTutorialTitle->addComponent<TextComponent>("Tutorial");
		t->getText().setCharacterSize(53);
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtTutorialTitle->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 30.f));

		auto txtTutorialHeading1 = makeEntity();
		auto t2 = txtTutorialHeading1->addComponent<TextComponent>("Main Menu Controls");
		t2->getText().setCharacterSize(24);
		t2->getText().setOrigin(t2->getText().getGlobalBounds().width / 2, t2->getText().getGlobalBounds().height / 2);
		txtTutorialHeading1->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, (Engine::GetWindow().getSize().y - (Engine::GetWindow().getSize().y / 1.15))));

		auto txtTutorialHeading2 = makeEntity();
		auto t3 = txtTutorialHeading2->addComponent<TextComponent>("Astar Snake Controls");
		t3->getText().setCharacterSize(24);
		t3->getText().setOrigin(t3->getText().getGlobalBounds().width / 2, t3->getText().getGlobalBounds().height / 2);
		txtTutorialHeading2->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, (Engine::GetWindow().getSize().y - (Engine::GetWindow().getSize().y / 1.73))));

		auto txtTutorialHeading3 = makeEntity();
		auto t4 = txtTutorialHeading3->addComponent<TextComponent>("Neural Network Snake Controls");
		t4->getText().setCharacterSize(24);
		t4->getText().setOrigin(t4->getText().getGlobalBounds().width / 2, t4->getText().getGlobalBounds().height / 2);
		txtTutorialHeading3->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, (Engine::GetWindow().getSize().y - (Engine::GetWindow().getSize().y / 5.25))));

		auto txtBack = makeEntity();
		auto t5 = txtBack->addComponent<TextComponent>("Return to Main Menu Press [Esc]");
		t5->getText().setCharacterSize(14);
		t5->getText().setOrigin(t5->getText().getGlobalBounds().width / 2, t5->getText().getGlobalBounds().height / 2);
		txtBack->setPosition(Vector2f(Engine::GetWindow().getSize().x / 1.12, (Engine::GetWindow().getSize().y - (Engine::GetWindow().getSize().y / 16.0))));

		auto txtVersion3 = makeEntity();
		auto t28 = txtVersion3->addComponent<TextComponent>("Exploratory Software Version 0.4.3");
		t28->getText().setCharacterSize(12);
		t28->getText().setOrigin(t28->getText().getGlobalBounds().width / 2, t28->getText().getGlobalBounds().height / 2);
		txtVersion3->setPosition(Vector2f(t28->getText().getGlobalBounds().width / 1.9, 10));
	}

	AddEntity::makeWalls(this);
}

void TutorialScene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
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
