#ifndef _HEROATTACKER_HPP__
#define _HEROATTACKER_HPP__

#include "Hero.hpp"

struct HeroAttacker {

	void operator() (SceneNode& sceneNode, sf::Time) const;
};

#endif