#ifndef _DATA_HPP__
#define _DATA_HPP__

#include "TextureInfo.hpp"

#include <vector>
#include <array>
#include <SFML/System.hpp>

struct HeroData {

	int hitpoints;
	sf::Time attackInterval;
	float attackDistance;
	float speed;
	TextureSheet texture;
};

struct ProjectileData {

	int damage;
	float speed;
	TextureSheet texture;
};

std::vector<HeroData> initializeHeroes();
std::vector<ProjectileData> initializeProjectiles();

#endif