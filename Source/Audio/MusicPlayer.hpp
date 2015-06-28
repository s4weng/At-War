#ifndef _MUSICPLAYER_HPP__
#define _MUSICPLAYER_HPP__

#include "TextureInfo.hpp"

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
	void setVolume(float volume);

private:

	sf::Music music;
	std::map<Music, std::string> fileNames;
	float volume;
};

#endif