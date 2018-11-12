#include "engine.h"
#include "game.h"
#include "scenes/scene_splash.h"
#include <SFML/Audio.hpp>

// SET09121 2017-8 TR2 001 - Games Engineering
// Picobots
// Version 0.7.0
// Alexander Barker 
// 40333139
// Last Updated on 1st May 2018
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
HighScoresScene highscores;
TutorialScene tutorial;
LoadScene load;

int main() {

	Engine::Start(1504, 846, "Picobots", &splash);
}
