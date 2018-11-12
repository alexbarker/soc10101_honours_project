#pragma once
#include "engine.h"
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include "SFML/Graphics.hpp"
#include "../components/cmp_music.h"

#define MAX_NUMBER_OF_Settings 5

class SettingsScene : public Scene {
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex2; }

public:
	sf::IntRect uvRect;

private:
	int selectedItemIndex2;
	sf::Font font;
	sf::Text settingsMenu[MAX_NUMBER_OF_Settings];
};
