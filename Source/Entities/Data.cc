#include "Data.hpp"
#include "Hero.hpp"
#include "Projectile.hpp"

std::vector<HeroData> initializeHeroes(){

	std::vector<HeroData> data(Hero::HeroClass::classCount);

	data[Hero::HeroClass::Archer].hitpoints = 100;
	data[Hero::HeroClass::Archer].attackInterval = sf::seconds(1.5);
	data[Hero::HeroClass::Archer].texture = TextureSheet::Archer;
	data[Hero::HeroClass::Archer].attackDistance = 300.f;
	data[Hero::HeroClass::Archer].speed = 100.f;

	data[Hero::HeroClass::Druid].hitpoints = 100;
	data[Hero::HeroClass::Druid].attackInterval = sf::seconds(3);
	data[Hero::HeroClass::Druid].texture = TextureSheet::Druid;
	data[Hero::HeroClass::Druid].attackDistance = 300.f;
	data[Hero::HeroClass::Druid].speed = 70.f;

	return data;
}

std::vector<ProjectileData> initializeProjectiles(){

	std::vector<ProjectileData> data(Projectile::Type::typeCount);

	data[Projectile::Type::Arrow].damage = 10;
	data[Projectile::Type::Arrow].speed = 350.f;
	data[Projectile::Type::Arrow].texture = TextureSheet::Arrow;
	data[Projectile::Type::Arrow].textureRect = sf::IntRect(0, 0, 33, 6);

	data[Projectile::Type::MiniBlast].damage = 10;
	data[Projectile::Type::MiniBlast].speed = 350.f;
	data[Projectile::Type::MiniBlast].texture = TextureSheet::MiniBlast;
	data[Projectile::Type::MiniBlast].textureRect = sf::IntRect(35, 0, 26, 9);

	return data;
}