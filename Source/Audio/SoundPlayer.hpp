#ifndef _SOUNDPLAYER_HPP__
#define _SOUNDPLAYER_HPP__

#include "ResourceInfo.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <list>

class SoundPlayer : private sf::NonCopyable {

public:

	SoundPlayer();

	void play(SoundEffect soundEffect);
	void play(SoundEffect soundEffect, sf::Vector2f position);
	void removeStoppedSounds();

	void setListenerPosition(sf::Vector2f position);
	sf::Vector2f getListenerPosition() const;

private:

	SoundEffectHolder soundEffects;
	std::list<sf::Sound> sounds; //vector(array) might relocate existing sounds mid-play
};

#endif