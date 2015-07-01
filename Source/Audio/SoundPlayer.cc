#include "SoundPlayer.hpp"

#include <SFML/Audio/Listener.hpp>
#include <cmath>

const float listenerZ = 500.f; //Z coordinate, listener's distance from monitor
const float attenuation = 5.f; //attenuation factor
const float minDistance2D = 100.f; //min distance between listener and sound (on a 2D plane)
const float minDistance3D = std::sqrt(minDistance2D*minDistance2D + listenerZ*listenerZ); //Pythagorean to calculate according to 2D minDistance

SoundPlayer::SoundPlayer(): soundEffects(), sounds(){

	soundEffects.load(SoundEffect::shotArrow, "Sounds/ShotArrow.ogg");
	soundEffects.load(SoundEffect::castBlast, "Sounds/CastBlast.ogg");
	soundEffects.load(SoundEffect::buttonPress, "Sounds/ButtonPress.ogg");
	soundEffects.load(SoundEffect::buttonSwitch, "Sounds/ButtonSwitch.ogg");

	sf::Listener::setDirection(0.f, 0.f, -1.f); //this should be default anyway
}

void SoundPlayer::play(SoundEffect soundEffect){

	//non-spatialized sounds
	play(soundEffect, getListenerPosition());
}

void SoundPlayer::play(SoundEffect soundEffect, sf::Vector2f position){

	sounds.push_back(sf::Sound());
	sf::Sound& sound = sounds.back();

	sound.setBuffer(soundEffects.get(soundEffect));

	//Set the 3D audio position; note -y because height goes in opposite direction in SFML
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(attenuation);
	sound.setMinDistance(minDistance3D);

	sound.play();
}

void SoundPlayer::removeStoppedSounds(){

	sounds.remove_if([] (const sf::Sound& sound){

		return sound.getStatus() == sf::Sound::Stopped;
	});
}

void SoundPlayer::setListenerPosition(sf::Vector2f position){

	sf::Listener::setPosition(position.x, -position.y, listenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition() const {

	//return a 2D audio position for non-spatialized sounds
	sf::Vector3f position = sf::Listener::getPosition();
	return sf::Vector2f(position.x, -position.y);
}