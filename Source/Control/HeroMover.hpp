#ifndef _HEROMOVER_HPP__
#define _HEROMOVER_HPP__

#include "Hero.hpp"

struct HeroMover {

	HeroMover(float x, float y);
	void operator() (SceneNode& sceneNode, sf::Time) const;

	sf::Vector2f velocity;
};

#endif