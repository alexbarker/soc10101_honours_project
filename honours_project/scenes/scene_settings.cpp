#include "engine.h"
#include "scene_settings.h"
#include "../game.h"
#include "system_renderer.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include "../components/cmp_music.h"
#include "../components/cmp_text.h"

// SET09121 2017-8 TR2 001 - Games Engineering
// Picobots
// Version 0.7.0
// Alexander Barker 
// 40333139
// Last Updated on 1st May 2018
// scene_settings.cpp - This file is used to call for loads, updates and renders for Settings.

using namespace std;
using namespace sf;

sf::SoundBuffer effect1a;
sf::Sound sound1a;
sf::SoundBuffer effect2a;
sf::Sound sound2a;

static shared_ptr<Entity> player;

void SettingsScene::Load() {

	s2.stop();
	s3.stop();
	s1.playing();

	effect1a.loadFromFile("res/sound/shoot.ogg");
	sound1a.setBuffer(effect1a);
	effect2a.loadFromFile("res/sound/menu.ogg");
	sound2a.setBuffer(effect2a);

	{
		auto txtSettings = makeEntity();
		auto t = txtSettings->addComponent<TextComponent>("Settings");
		t->getText().setCharacterSize(54);
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtSettings->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));
	}

	float x2 = Engine::getWindowSize().x;
	float y2 = Engine::getWindowSize().y;
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");

	settingsMenu[0].setFont(font);
	settingsMenu[0].setFillColor(sf::Color::Green);
	settingsMenu[0].setString("Default");
	settingsMenu[0].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 40));

	settingsMenu[1].setFont(font);
	settingsMenu[1].setFillColor(sf::Color::White);
	settingsMenu[1].setString("1504 x 846");
	settingsMenu[1].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 80));

	settingsMenu[2].setFont(font);
	settingsMenu[2].setFillColor(sf::Color::White);
	settingsMenu[2].setString("1920 x 1080");
	settingsMenu[2].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 120));

	settingsMenu[3].setFont(font);
	settingsMenu[3].setFillColor(sf::Color::White);
	settingsMenu[3].setString("Fullscreen");
	settingsMenu[3].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 160));

	settingsMenu[4].setFont(font);
	settingsMenu[4].setFillColor(sf::Color::White);
	settingsMenu[4].setString("Back to Title");
	settingsMenu[4].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 200));

	selectedItemIndex2 = 0;

	setLoaded(true);
}

void SettingsScene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	Scene::UnLoad();
}

void SettingsScene::Update(const double& dt) {
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

	if (sf::Keyboard::isKeyPressed(Keyboard::Up)) {
		MoveUp();
		std::this_thread::sleep_for(std::chrono::milliseconds(170));
	}
	else if (sf::Keyboard::isKeyPressed(Keyboard::Down)) {
		MoveDown();
		std::this_thread::sleep_for(std::chrono::milliseconds(170));
	}
	else if (sf::Keyboard::isKeyPressed(Keyboard::Enter)) {
		switch (GetPressedItem())
		{
		case 0:
			sound2a.play();
			Engine::setNewWindowSize(Vector2u(1504, 864), 2);
			std::this_thread::sleep_for(std::chrono::milliseconds(170));
			break;
		case 1:
			sound2a.play();
			Engine::setNewWindowSize(Vector2u(1504, 864), 2);
			std::this_thread::sleep_for(std::chrono::milliseconds(170));
			break;
		case 2:
			sound2a.play();
			Engine::setNewWindowSize(Vector2u(1920, 1080), 2);
			std::this_thread::sleep_for(std::chrono::milliseconds(170));
			break;
		case 3:
			sound2a.play();
			Engine::setNewWindowSize(Vector2u(1920, 1080), 1);
			std::this_thread::sleep_for(std::chrono::milliseconds(170));
			break;
		case 4:
			sound2a.play();
			Engine::ChangeScene(&menu);
			std::this_thread::sleep_for(std::chrono::milliseconds(170));
			break;
		}
	}
}

void SettingsScene::Render() {
	Scene::Render();

	for (int j = 0; j < MAX_NUMBER_OF_Settings; j++)
	{
		Renderer::queue(&settingsMenu[j]);
	}
}

void SettingsScene::MoveUp()
{
	if (selectedItemIndex2 - 1 >= 0)
	{
		sound1a.play();
		settingsMenu[selectedItemIndex2].setFillColor(sf::Color::White);
		selectedItemIndex2--;
		settingsMenu[selectedItemIndex2].setFillColor(sf::Color::Green);
	}
}

void SettingsScene::MoveDown()
{
	if (selectedItemIndex2 + 1 < MAX_NUMBER_OF_Settings)
	{
		sound1a.play();
		settingsMenu[selectedItemIndex2].setFillColor(sf::Color::White);
		selectedItemIndex2++;
		settingsMenu[selectedItemIndex2].setFillColor(sf::Color::Green);
	}
}
