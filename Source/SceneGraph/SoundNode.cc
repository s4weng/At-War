#include "SoundNode.hpp"

SoundNode::SoundNode(SoundPlayer& soundPlayer): soundPlayer(soundPlayer){
}

void SoundNode::playSound(SoundEffect soundEffect, sf::Vector2f position){

	soundPlayer.play(soundEffect, position);
}

unsigned int SoundNode::getReceiver() const {

	return Receiver::SoundEffect;
}