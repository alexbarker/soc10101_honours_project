#include "engine.h"
#include "game.h"
#include "scenes/scene_splash.h"
#include <SFML/Audio.hpp>

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype
// Version 0.1.2
// Alexander Barker 
// 40333139
// Last Updated on 16th November 2018
// main.cpp - This file is used to start the engine with predefined size and name.

using namespace std;

SplashScene splash;
MenuScene menu;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;
Level4Scene level4;
Level5Scene level5;
Level6Scene level6;
Level7Scene level7;
BossLevelScene bosslevel;
SettingsScene settings;
GameOverScene gameover;
EndGameScene endgame;
PrototypeScene prototype;
TutorialScene tutorial;
LoadScene load;

int main() {

	Engine::Start(1504, 846, "Honours Project", &splash);
}
