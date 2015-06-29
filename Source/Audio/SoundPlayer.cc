#include "SoundPlayer.hpp"

#include <SFML/Audio/Listener.hpp>

SoundPlayer::SoundPlayer(): soundEffects(), sounds(){

	soundEffects.load(SoundEffect::shotArrow, "Sounds/ShotArrow.ogg");
	soundEffects.load(SoundEffect::castBlast, "Sounds/CastBlast.ogg");
	soundEffects.load(SoundEffect::buttonPress, "Sounds/ButtonPress.ogg");
	soundEffects.load(SoundEffect::buttonSwitch, "Sounds/ButtonSwitch.ogg");
}

void SoundPlayer::play(SoundEffect soundEffect){

	sounds.push_back(sf::Sound(soundEffects.get(soundEffect)));
	sounds.back().play();
}

void SoundPlayer::removeStoppedSounds(){

	sounds.remove_if([] (const sf::Sound& sound){

		return sound.getStatus() == sf::Sound::Stopped;
	});
}