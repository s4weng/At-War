#include "Data.hpp"
#include "Hero.hpp"
#include "Projectile.hpp"

std::vector<HeroData> initializeHeroes(){

	std::vector<HeroData> data(Hero::heroClass::typeCount);

	data[Hero::heroClass::Archer].hitpoints = 100;
	data[Hero::heroClass::Archer].attackInterval = sf::seconds(1);
	data[Hero::heroClass::Archer].texture = textureSheet::standingArcher;

	/*data[Hero::heroClass::Archmage].hitpoints = 80;
	data[Hero::heroClass::Archmage].attackInterval = sf::seconds(1);
	data[Hero::heroClass::Archmage].texture = textureSheet::standingArchmage;*/

	/*data[Hero::heroClass::Druid].hitpoints = 30;
	data[Hero::heroClass::Druid].texture = textureSheet::standingDruid;*/

	return data;
}

std::vector<ProjectileData> initializeProjectiles(){

	std::vector<ProjectileData> data(Projectile::Type::typeCount);

	data[Projectile::Type::Arrow].damage = 5;
	data[Projectile::Type::Arrow].speed = 100.f;
	data[Projectile::Type::Arrow].texture = textureSheet::Arrow;

	return data;
	//data[Projectile::Type::Spell].
}