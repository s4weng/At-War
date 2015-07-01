#ifndef _HEROSOUNDPLAYER_HPP__
#define _HEROSOUNDPLAYER_HPP__

#include "ResourceInfo.hpp"
#include "SoundNode.hpp"

#include <SFML/System/Vector2.hpp>

struct HeroSoundPlayer {

	HeroSoundPlayer(SoundEffect soundEffect, sf::Vector2f position);
	void operator() (SceneNode& sceneNode, sf::Time) const;

	SoundEffect soundEffect;
	sf::Vector2f position;
};

#endif