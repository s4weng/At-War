#ifndef _DATA_HPP__
#define _DATA_HPP__

#include "TextureInfo.hpp"
#include "Hero.hpp"

#include <vector>

class Hero;

struct HeroData {

	int hitpoints;
	textureSheet texture;
	Hero::heroFaction faction;
};

std::vector<HeroData> initializeHeroes();

#endif