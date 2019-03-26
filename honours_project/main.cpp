#include "engine.h"
#include "app.h"
#include "scenes/scene_splash.h"
#include <SFML/Audio.hpp>

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 19th March 2019
// main.cpp - This file is used to start the engine with predefined size and name.

using namespace std;

SplashScene splash;
MenuScene menu;
SettingsScene settings;
TutorialScene tutorial;

int main() {

	Engine::Start(1504, 846, "Honours Project", &splash);
}
