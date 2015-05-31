#ifndef _DATA_HPP__
#define _DATA_HPP__

#include "TextureInfo.hpp"

#include <vector>
#include <SFML/System.hpp>

struct HeroData {

	int hitpoints;
	sf::Time attackInterval;
	textureSheet texture;
};

struct ProjectileData {

	int damage;
	float speed;
	textureSheet texture;
};

std::vector<HeroData> initializeHeroes();
std::vector<ProjectileData> initializeProjectiles();

#endif