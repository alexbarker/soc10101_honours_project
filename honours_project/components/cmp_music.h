#pragma once

#include "SFML/Audio.hpp"
#include <vector>
#include <iostream>

class MusicPlayer final : private sf::NonCopyable
{
public:
	MusicPlayer();
	~MusicPlayer() = default;
	MusicPlayer(const MusicPlayer&) = delete;
	const MusicPlayer& operator = (const MusicPlayer&) = delete;

	void play1(const int file, bool loop = false);
	void play2(const int file, bool loop = false);
	void play3(const int file, bool loop = false);
	void stop();
	void setPaused(bool paused);
	bool playing() const;
	float getVolume() const;

private:

	float m_volume;
	sf::Music m_music;
};
