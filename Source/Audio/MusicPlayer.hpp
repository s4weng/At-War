#ifndef _MUSICPLAYER_HPP__
#define _MUSICPLAYER_HPP__

#include "ResourceInfo.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>

class MusicPlayer : private sf::NonCopyable {

public:

	MusicPlayer();
	void play(Music theme);
	void stop();
	void pause();
	void resume();
	void setVolume(float newVolume);

private:

	sf::Music music;
	std::map<Music, std::string> fileNames;
	float volume;
};

#endif