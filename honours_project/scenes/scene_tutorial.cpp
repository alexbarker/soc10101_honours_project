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
// Version 0.5.2
// Alexander Barker 
// 40333139
// Last Updated on 28th March 2019
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

		//-----------Main Menu---------//
		auto txtVersion21 = makeEntity();
		auto t31 = txtVersion21->addComponent<TextComponent>("Insert information about Main Menu.1");
		t31->getText().setCharacterSize(16);
		t31->getText().setOrigin(t31->getText().getGlobalBounds().width / 2, t31->getText().getGlobalBounds().height / 2);
		txtVersion21->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y * 0.20));

		auto txtVersion22 = makeEntity();
		auto t32 = txtVersion22->addComponent<TextComponent>("Insert information about Main Menu.2");
		t32->getText().setCharacterSize(16);
		t32->getText().setOrigin(t32->getText().getGlobalBounds().width / 2, t32->getText().getGlobalBounds().height / 2);
		txtVersion22->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y * 0.23));

		auto txtVersion23 = makeEntity();
		auto t33 = txtVersion23->addComponent<TextComponent>("Insert information about Main Menu.3");
		t33->getText().setCharacterSize(16);
		t33->getText().setOrigin(t33->getText().getGlobalBounds().width / 2, t33->getText().getGlobalBounds().height / 2);
		txtVersion23->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y * 0.26));

		auto txtTutorialHeading2 = makeEntity();
		auto t3 = txtTutorialHeading2->addComponent<TextComponent>("Astar Snake Controls");
		t3->getText().setCharacterSize(24);
		t3->getText().setOrigin(t3->getText().getGlobalBounds().width / 2, t3->getText().getGlobalBounds().height / 2);
		txtTutorialHeading2->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, (Engine::GetWindow().getSize().y - (Engine::GetWindow().getSize().y / 1.73))));

		//-----------Astar Controls---------//
		auto txtVersion24 = makeEntity();
		auto t34 = txtVersion24->addComponent<TextComponent>("Insert information about Astar Controls.1");
		t34->getText().setCharacterSize(16);
		t34->getText().setOrigin(t34->getText().getGlobalBounds().width / 2, t34->getText().getGlobalBounds().height / 2);
		txtVersion24->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y * 0.495));

		auto txtVersion25 = makeEntity();
		auto t35 = txtVersion25->addComponent<TextComponent>("Insert information about Astar Controls.2");
		t35->getText().setCharacterSize(16);
		t35->getText().setOrigin(t35->getText().getGlobalBounds().width / 2, t35->getText().getGlobalBounds().height / 2);
		txtVersion25->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y * 0.525));

		auto txtVersion26 = makeEntity();
		auto t36 = txtVersion26->addComponent<TextComponent>("Insert information about Astar Controls.3");
		t36->getText().setCharacterSize(16);
		t36->getText().setOrigin(t36->getText().getGlobalBounds().width / 2, t36->getText().getGlobalBounds().height / 2);
		txtVersion26->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y * 0.555));

		auto txtTutorialHeading3 = makeEntity();
		auto t4 = txtTutorialHeading3->addComponent<TextComponent>("Neural Network Snake Controls");
		t4->getText().setCharacterSize(24);
		t4->getText().setOrigin(t4->getText().getGlobalBounds().width / 2, t4->getText().getGlobalBounds().height / 2);
		txtTutorialHeading3->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, (Engine::GetWindow().getSize().y - (Engine::GetWindow().getSize().y / 5.25))));

		//-----------Astar Controls---------//
		auto txtVersion27 = makeEntity();
		auto t37 = txtVersion27->addComponent<TextComponent>("Insert information about NN Controls.1");
		t37->getText().setCharacterSize(16);
		t37->getText().setOrigin(t37->getText().getGlobalBounds().width / 2, t37->getText().getGlobalBounds().height / 2);
		txtVersion27->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y * 0.88));

		auto txtVersion28 = makeEntity();
		auto t38 = txtVersion28->addComponent<TextComponent>("Insert information about NN Controls.2");
		t38->getText().setCharacterSize(16);
		t38->getText().setOrigin(t38->getText().getGlobalBounds().width / 2, t38->getText().getGlobalBounds().height / 2);
		txtVersion28->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y * 0.91));

		auto txtVersion29 = makeEntity();
		auto t39 = txtVersion29->addComponent<TextComponent>("Insert information about NN Controls.3");
		t39->getText().setCharacterSize(16);
		t39->getText().setOrigin(t39->getText().getGlobalBounds().width / 2, t39->getText().getGlobalBounds().height / 2);
		txtVersion29->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y * 0.94));

		auto txtBack = makeEntity();
		auto t5 = txtBack->addComponent<TextComponent>("Return to Main Menu Press [Esc]");
		t5->getText().setCharacterSize(14);
		t5->getText().setOrigin(t5->getText().getGlobalBounds().width / 2, t5->getText().getGlobalBounds().height / 2);
		txtBack->setPosition(Vector2f(Engine::GetWindow().getSize().x / 1.12, (Engine::GetWindow().getSize().y - (Engine::GetWindow().getSize().y / 16.0))));

		auto txtVersion3 = makeEntity();
		auto t28 = txtVersion3->addComponent<TextComponent>("Exploratory Software Version 0.5.2");
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
