#include "scene_splash.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "../components/cmp_music.h"
#include "system_renderer.h"
#include "system_resources.h"
#include "../components/cmp_sprite.h"
#include "scene_menu.h"
#include "maths.h"
#include "LevelSystem.h"
#include <SFML/Graphics.hpp>
#include "../add_entity.h"

// SET09121 2017-8 TR2 001 - Games Engineering
// Picobots
// Version 0.7.0
// Alexander Barker 
// 40333139
// Last Updated on 1st May 2018
// scene_menu.cpp - This file is used to call for loads, updates and renders for Main Menu.

using namespace std;
using namespace sf;

sf::Sprite titleSprite;
sf::Texture titleTexture;
Vector2f target;
sf::Vector2u titleTextureSize;  //Added to store texture size.
sf::Vector2u windowSizeMenu;   //Added to store window size.
int fadeCounter = 0;

sf::Texture roboarmTexture;
sf::IntRect roboSource(0, 0, 400, 300);
sf::Sprite roboarm(roboarmTexture, roboSource);
sf::Texture roboarmTexture2;
sf::IntRect roboSource2(0, 0, -400, 300);
sf::Sprite roboarm2(roboarmTexture2, roboSource2);
sf::Clock clock1;

sf::SoundBuffer effect1;
sf::Sound sound1;
sf::SoundBuffer effect2;
sf::Sound sound2;

void MenuScene::SetTitle() {
	titleTexture = *Resources::load<Texture>("title.png");
	float x = Engine::GetWindow().getSize().x;
	float y = Engine::GetWindow().getSize().y;
	titleTextureSize = titleTexture.getSize();							//Get size of texture.
	windowSizeMenu = Engine::GetWindow().getSize();               //Get size of window.
	float ScaleX = (float)windowSizeMenu.x / titleTextureSize.x;
	float ScaleY = (float)windowSizeMenu.y / titleTextureSize.y;     //Calculate scale.
	target = { x , y };
	titleSprite.setTexture(titleTexture);
	titleSprite.setPosition(windowSizeMenu.x / 2, windowSizeMenu.y / 3);
	titleSprite.setOrigin(titleTextureSize.x / 2, titleTextureSize.y / 2);
}

void MenuScene::Load() {
	{
		s2.stop();
		s3.stop();
		s1.playing();
		float x2 = Engine::getWindowSize().x;
		float y2 = Engine::getWindowSize().y;
		SetTitle();

		effect1.loadFromFile("res/sound/shoot.ogg");
		sound1.setBuffer(effect1);
		effect2.loadFromFile("res/sound/menu.ogg");
		sound2.setBuffer(effect2);

		roboarm.setPosition(x2 - 400.0f, 200.0f);
		roboarmTexture.loadFromFile("res/img/RoboarmSprite.png");
		roboarm2.setPosition(0, 200.0f);
		roboarmTexture2.loadFromFile("res/img/RoboarmSprite.png");

		font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");

		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Green);
		menu[0].setString("New Game");
		menu[0].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 40));

		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Load Game");
		menu[1].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 80));

		menu[2].setFont(font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("High Scores");
		menu[2].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 120));

		menu[3].setFont(font);
		menu[3].setFillColor(sf::Color::White);
		menu[3].setString("Tutorial");
		menu[3].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 160));

		menu[4].setFont(font);
		menu[4].setFillColor(sf::Color::White);
		menu[4].setString("Settings");
		menu[4].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 200));

		menu[5].setFont(font);
		menu[5].setFillColor(sf::Color::White);
		menu[5].setString("Quit");
		menu[5].setPosition(sf::Vector2f((x2 / 2) - 80, (y2 / 2) + 240));

		selectedItemIndex = 0;

		//std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	}
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
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
		fadeCounter = 0;
		UnLoad();
		Load();
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
			sound2.play();
			Engine::ChangeScene(&level1);
			break;
		case 1:
			sound2.play();
			Engine::ChangeScene(&load);
			break;
		case 2:
			sound2.play();
			Engine::ChangeScene(&highscores);
			break;
		case 3:
			sound2.play();
			Engine::ChangeScene(&tutorial);
			break;
		case 4:
			sound2.play();
			Engine::ChangeScene(&settings);
			std::this_thread::sleep_for(std::chrono::milliseconds(170));
			break;
		case 5:
			sound2.play();
			Engine::GetWindow().close();
			break;
		}
	}
}

void MenuScene::Render() {
	Scene::Render();

	if (clock1.getElapsedTime().asSeconds() > 0.2f) {
		if (roboSource.left == 6000) {
			roboSource.left = 0;
			roboSource2.left = 0;
			if (clock1.getElapsedTime().asSeconds() > 0.2f) { AddEntity::makeFakePlayer2(this, Vector2f(0.f, 450.f), Vector2f(70.f, 950.f), 2.0f); }
			if (clock1.getElapsedTime().asSeconds() > 0.2f) { AddEntity::makeFakePlayer1(this, Vector2f(Engine::getWindowSize().x - 25.f, 450.f), Vector2f(Engine::getWindowSize().x - 70.f, 450.f), 2.0f); }
		}
		else {

			roboSource.left += 400;
			roboarm.setTextureRect(roboSource);
			roboSource2.left += 400;
			roboarm2.setTextureRect(roboSource2);
			clock1.restart();
		}
	}

	if (fadeCounter <= 250) {
		roboarm.setColor(sf::Color(255, 255, 255, fadeCounter));
		roboarm2.setColor(sf::Color(255, 255, 255, fadeCounter));
		titleSprite.setColor(sf::Color(255, 255, 255, fadeCounter));
		fadeCounter++;
		Renderer::queue(&roboarm);
		Renderer::queue(&roboarm2);
		Renderer::queue(&titleSprite);
	}
	else {
		roboarm.setColor(sf::Color(255, 255, 255, 255));
		roboarm2.setColor(sf::Color(255, 255, 255, 255));
		titleSprite.setColor(sf::Color(255, 255, 255, 255));
		Renderer::queue(&roboarm);
		Renderer::queue(&roboarm2);
		Renderer::queue(&titleSprite);
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			Renderer::queue(&menu[i]);
		}
	}
}

void MenuScene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	Scene::UnLoad();
}

void MenuScene::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		sound1.play();
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Green);
	}
}

void MenuScene::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		sound1.play();
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Green);
	}
}


