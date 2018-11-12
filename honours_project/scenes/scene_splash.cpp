#include "engine.h"
#include "../game.h"
#include "scene_splash.h"
#include "../components/cmp_text.h"
#include "../scenes/scene_menu.h"
#include "../components/cmp_music.h"
#include <LevelSystem.h>
#include <SFML/Audio.hpp>
#include "../components/cmp_sprite.h"
#include <SFML/Graphics/Sprite.hpp>
#include <system_renderer.h>
#include <system_resources.h>
#include "LevelSystem.h"

// SET09121 2017-8 TR2 001 - Games Engineering
// Picobots
// Version 0.7.0
// Alexander Barker 
// 40333139
// Last Updated on 29th April 2018
// scene_splash.cpp - This file is used to call for loads, updates and renders for Splash Screen.

using namespace std;
using namespace sf;
MusicPlayer s1;
MusicPlayer s2;
MusicPlayer s3;

sf::Sprite splashSprite1;
sf::Texture splashTexture1;
Vector2f splash_target1;
sf::Vector2u splashSize1;  //Added to store texture size.
sf::Vector2u windowSizeSplash1;   //Added to store window size.
sf::Sprite splashSprite2;
sf::Texture splashTexture2;
Vector2f splash_target2;
sf::Vector2u splashSize2;  //Added to store texture size.
sf::Vector2u windowSizeSplash2;   //Added to store window size.
sf::Time now1;
sf::Time now2;

void SplashScene::SetBackground() {
	s1.playing();
	splashTexture1 = *Resources::load<Texture>("SplashScreen1.png");
	float x = Engine::GetWindow().getSize().x;
	float y = Engine::GetWindow().getSize().y;
	splashSize1 = splashTexture1.getSize(); //Get size of texture.
	windowSizeSplash1 = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX = (float)windowSizeSplash1.x / splashSize1.x;
	float ScaleY = (float)windowSizeSplash1.y / splashSize1.y;     //Calculate scale.
	splash_target1 = { x , y };
	splashSprite1.setTexture(splashTexture1);
	splashSprite1.setPosition(0, 0);
	splashSprite1.setScale(ScaleX, ScaleY);
	splashSprite1.setOrigin(0, 0);
	setLoaded(true);
	s1.playing();

	sf::Clock clock; // starts the clock
	while (now1 < sf::milliseconds(4000)) {
		now1 = clock.getElapsedTime();
	}
	clock.restart();

	s1.playing();
	splashTexture2 = *Resources::load<Texture>("SplashScreen2.png");
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	splashSize2 = splashTexture2.getSize(); //Get size of texture.
	windowSizeSplash2 = Engine::GetWindow().getSize();             //Get size of window.
	float ScaleX1 = (float)windowSizeSplash2.x / splashSize2.x;
	float ScaleY1 = (float)windowSizeSplash2.y / splashSize2.y;     //Calculate scale.
	splash_target2 = { x2 , y2 };
	splashSprite2.setTexture(splashTexture2);
	splashSprite2.setPosition(0, 0);
	splashSprite2.setScale(ScaleX1, ScaleY1);
	splashSprite2.setOrigin(0, 0);
	setLoaded(true);
	s1.playing();
	while (now2 < sf::milliseconds(4000)) {
		now2 = clock.getElapsedTime();
	}
	clock.restart();
	//std::this_thread::sleep_for(std::chrono::milliseconds(4000));
}

void SplashScene::Load() {
	s1.play1(0, true);
	SetBackground();
	setLoaded(true);
	s1.playing();
	Engine::ChangeScene(&menu);
}

void SplashScene::UnLoad() {
	float x2 = Engine::GetWindow().getSize().x;
	float y2 = Engine::GetWindow().getSize().y;
	Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, x2, y2)));
	Scene::UnLoad();
}

void SplashScene::Update(const double& dt) {
	Scene::Update(dt);
}

void SplashScene::Render() {
	Renderer::queue(&splashSprite1);
	Renderer::queue(&splashSprite2);
	Scene::Render();
}