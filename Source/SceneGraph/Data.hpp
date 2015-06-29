#ifndef _DATA_HPP__
#define _DATA_HPP__

#include "ResourceInfo.hpp"

#include <vector>
#include <array>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

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
	sf::Vector2f travelDistance;
};

std::vector<HeroData> initializeHeroes();
std::vector<ProjectileData> initializeProjectiles();

#endif