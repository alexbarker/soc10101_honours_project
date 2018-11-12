#pragma once

#include "scenes/scene_splash.h"
#include "scenes/scene_menu.h"
#include "components/cmp_music.h"
#include "scenes/scene_level1.h"
#include "scenes/scene_level2.h"
#include "scenes/scene_level3.h"
#include "scenes/scene_level4.h"
#include "scenes/scene_level5.h"
#include "scenes/scene_level6.h"
#include "scenes/scene_level7.h"
#include "scenes/scene_boss_level.h"
#include "scenes/scene_settings.h"
#include "scenes/scene_game_over.h"
#include "scenes/scene_end_game.h"
#include "scenes/scene_high_scores.h"
#include "scenes/scene_tutorial.h"
#include "scenes/scene_load.h"

extern SplashScene splash;
extern MenuScene menu;
extern Level1Scene level1;
extern Level2Scene level2;
extern Level3Scene level3;
extern Level4Scene level4;
extern Level5Scene level5;
extern Level6Scene level6;
extern Level7Scene level7;
extern BossLevelScene bosslevel;
extern SettingsScene  settings;
extern GameOverScene  gameover;
extern EndGameScene  endgame;
extern HighScoresScene  highscores;
extern TutorialScene  tutorial;
extern LoadScene  load;

extern MusicPlayer s1;
extern MusicPlayer s2;
extern MusicPlayer s3;



