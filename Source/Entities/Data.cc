#include "Data.hpp"
#include "Hero.hpp"
#include "Projectile.hpp"

std::vector<HeroData> initializeHeroes(){

	std::vector<HeroData> data(Hero::heroClass::typeCount);

	data[Hero::heroClass::Archer].hitpoints = 100;
	data[Hero::heroClass::Archer].attackInterval = sf::seconds(1);
	data[Hero::heroClass::Archer].texture = textureSheet::standingArcher;
	data[Hero::heroClass::Archer].attackDistance = 300.f;
	data[Hero::heroClass::Archer].speed = 100.f;

	data[Hero::heroClass::Archmage].hitpoints = 100;
	data[Hero::heroClass::Archmage].attackInterval = sf::seconds(0);
	data[Hero::heroClass::Archmage].texture = textureSheet::standingArchmage;
	data[Hero::heroClass::Archmage].attackDistance = 300.f;
	data[Hero::heroClass::Archmage].speed = 100.f;

	return data;
}

std::vector<ProjectileData> initializeProjectiles(){

	std::vector<ProjectileData> data(Projectile::Type::typeCount);

	data[Projectile::Type::Arrow].damage = 5;
	data[Projectile::Type::Arrow].speed = 350.f;
	data[Projectile::Type::Arrow].texture = textureSheet::Arrow;

	return data;
}