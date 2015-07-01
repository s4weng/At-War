#include "HeroSoundPlayer.hpp"

HeroSoundPlayer::HeroSoundPlayer(SoundEffect soundEffect, sf::Vector2f position):
soundEffect(soundEffect),
position(position){
}

void HeroSoundPlayer::operator() (SceneNode& sceneNode, sf::Time) const {

	SoundNode &sound = static_cast<SoundNode&>(sceneNode);

	sound.playSound(soundEffect, position);
}