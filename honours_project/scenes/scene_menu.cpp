#include "scene_splash.h"
#include "../components/cmp_text.h"
#include "../app.h"
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

#include "../define.h"
#include "../ai/astar_snake_launcher_1snake.h"
#include "../components/cmp_snake_body_1snake.h"
#include "../ai/astar_snake_launcher_10snakes.h"
#include "../components/cmp_snake_body_10snakes.h"
#include "../ai/astar_snake_launcher_50snakes.h"
#include "../components/cmp_snake_body_50snakes.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <chrono>
#include <random>
#include "../ai/neural_network_launcher_100k.h"
#include "../ai/neural_network_launcher_1mil.h"
#include "../ai/neural_network_launcher_10mil.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.5.2
// Alexander Barker 
// 40333139
// Last Updated on 28th March 2019
// scene_menu.cpp - This file is used to call for loads, updates and renders for Main Menu.

using namespace std;
using namespace sf;

sf::Sprite titleSprite;
sf::Texture titleTexture;
Vector2f target;
sf::Vector2u titleTextureSize;  //Added to store texture size.
sf::Vector2u windowSizeMenu;   //Added to store window size.
int fadeCounter = 0;
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
	windowSizeMenu = Engine::GetWindow().getSize();					    //Get size of window.
	float ScaleX = (float)windowSizeMenu.x / titleTextureSize.x;
	float ScaleY = (float)windowSizeMenu.y / titleTextureSize.y;        //Calculate scale.
	target = { x , y };
	titleSprite.setTexture(titleTexture);
	titleSprite.setPosition(windowSizeMenu.x / 2, windowSizeMenu.y / 3.6f);
	titleSprite.setOrigin(titleTextureSize.x / 2, titleTextureSize.y / 2);
}

int startAstar1() {
	RenderWindow win(VideoMode(W_WIDTH, W_HEIGHT+50), "Astar Snake", Style::Default);
	win.setKeyRepeatEnabled(true);

	srand(SEED);

	Game1 g1;
	g1.play(win);
	g1.gameOver(win);

	return EXIT_SUCCESS;
}

int startAstar10() {
	RenderWindow win(VideoMode(W_WIDTH, W_HEIGHT + 50), "Astar 10 Snakes", Style::Default);
	win.setKeyRepeatEnabled(true);

	srand(SEED);

	Game10 g2;
	g2.play(win);
	g2.gameOver(win);

	return EXIT_SUCCESS;
}

int startAstar50() {
	RenderWindow win(VideoMode(W_WIDTH, W_HEIGHT + 50), "Astar 50 Snakes", Style::Default);
	win.setKeyRepeatEnabled(true);

	srand(SEED);

	Game50 g3;
	g3.play(win);
	g3.gameOver(win);

	return EXIT_SUCCESS;
}

int startNN100k() {

	srand(SEED);

	Stage_100k p1;
	p1.reset();
	p1.init_data();
	p1.startNN100k();

	return EXIT_SUCCESS;
}

int startNN1mil() {

	srand(SEED);

	Stage_1mil p2;
	p2.reset();
	p2.init_data();
	p2.startNN1mil();

	return EXIT_SUCCESS;
}

int startNN10mil() {

	srand(SEED);

	Stage_10mil p3;
	p3.reset();
	p3.init_data();
	p3.startNN10mil();

	return EXIT_SUCCESS;
}

void MenuScene::Load() {
	{
		float x2 = Engine::getWindowSize().x;
		float y2 = Engine::getWindowSize().y;
		SetTitle();
		
		effect1.loadFromFile("res/sound/shoot.ogg");
		sound1.setBuffer(effect1);
		effect2.loadFromFile("res/sound/menu.ogg");
		sound2.setBuffer(effect2);

		font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");

		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Green);
		menu[0].setString("Astar Snake");
		menu[0].setPosition(sf::Vector2f((x2 / 2.3) - 120, (y2 / 2.5) + 40));

		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Astar 10 Snakes");
		menu[1].setPosition(sf::Vector2f((x2 / 2.3) - 120, (y2 / 2.5) + 80));

		menu[2].setFont(font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("Astar 50 Snakes");
		menu[2].setPosition(sf::Vector2f((x2 / 2.3) - 120, (y2 / 2.5) + 120));

		menu[3].setFont(font);
		menu[3].setFillColor(sf::Color::White);
		menu[3].setString("Neural Network Snake (100k)");
		menu[3].setPosition(sf::Vector2f((x2 / 2.3) - 120, (y2 / 2.5) + 160));

		menu[4].setFont(font);
		menu[4].setFillColor(sf::Color::White);
		menu[4].setString("Neural Network Snake (1mil)");
		menu[4].setPosition(sf::Vector2f((x2 / 2.3) - 120, (y2 / 2.5) + 200));

		menu[5].setFont(font);
		menu[5].setFillColor(sf::Color::White);
		menu[5].setString("Neural Network Snake (10mil)");
		menu[5].setPosition(sf::Vector2f((x2 / 2.3) - 120, (y2 / 2.5) + 240));

		menu[6].setFont(font);
		menu[6].setFillColor(sf::Color::White);
		menu[6].setString("Tutorial");
		menu[6].setPosition(sf::Vector2f((x2 / 2.3) - 120, (y2 / 2.5) + 280));

		menu[7].setFont(font);
		menu[7].setFillColor(sf::Color::White);
		menu[7].setString("Settings");
		menu[7].setPosition(sf::Vector2f((x2 / 2.3) - 120, (y2 / 2.5) + 320));

		menu[8].setFont(font);
		menu[8].setFillColor(sf::Color::White);
		menu[8].setString("Quit");
		menu[8].setPosition(sf::Vector2f((x2 / 2.3) - 120, (y2 / 2.5) + 360));

		auto txtVersion2 = makeEntity();
		auto t27 = txtVersion2->addComponent<TextComponent>("Exploratory Software Version 0.5.2");
		t27->getText().setCharacterSize(12);
		t27->getText().setOrigin(t27->getText().getGlobalBounds().width / 2, t27->getText().getGlobalBounds().height / 2);
		txtVersion2->setPosition(Vector2f(t27->getText().getGlobalBounds().width / 1.9, 10));

		selectedItemIndex = 0;
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
			startAstar1();
			break;
		case 1:
			sound2.play();
			startAstar10();
			break;
		case 2:
			sound2.play();
			startAstar50();
			break;
		case 3:
			sound2.play();
			startNN100k();
			break;
		case 4:
			sound2.play();
			startNN1mil();
			break;
		case 5:
			sound2.play();
			startNN10mil();
			break;
		case 6:
			sound2.play();
			Engine::ChangeScene(&tutorial);
			std::this_thread::sleep_for(std::chrono::milliseconds(170));
			break;
		case 7:
			sound2.play();
			Engine::ChangeScene(&settings);
			std::this_thread::sleep_for(std::chrono::milliseconds(170));
			break;
		case 8:
			sound2.play();
			Engine::GetWindow().close();
			break;
		}
	}
}

void MenuScene::Render() {
	Scene::Render();

	if (fadeCounter <= 250) {
		titleSprite.setColor(sf::Color(255, 255, 255, fadeCounter));
		fadeCounter++;
		fadeCounter++;
		Renderer::queue(&titleSprite);
	}
	else {
		titleSprite.setColor(sf::Color(255, 255, 255, 255));
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


