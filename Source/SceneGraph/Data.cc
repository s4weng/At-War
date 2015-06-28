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

	data[Hero::HeroClass::Mage].hitpoints = 100;
	data[Hero::HeroClass::Mage].attackInterval = sf::seconds(1.5);
	data[Hero::HeroClass::Mage].texture = TextureSheet::Mage;
	data[Hero::HeroClass::Mage].attackDistance = 300.f;
	data[Hero::HeroClass::Mage].speed = 100.f;

	data[Hero::HeroClass::Druid].hitpoints = 100;
	data[Hero::HeroClass::Druid].attackInterval = sf::seconds(3);
	data[Hero::HeroClass::Druid].texture = TextureSheet::Druid;
	data[Hero::HeroClass::Druid].attackDistance = 300.f;
	data[Hero::HeroClass::Druid].speed = 70.f;

	data[Hero::HeroClass::Wolf].hitpoints = 100;
	data[Hero::HeroClass::Wolf].attackInterval = sf::seconds(3);
	data[Hero::HeroClass::Wolf].texture = TextureSheet::Wolf;
	data[Hero::HeroClass::Wolf].attackDistance = 100.f;
	data[Hero::HeroClass::Wolf].speed = 70.f;

	return data;
}

std::vector<ProjectileData> initializeProjectiles(){

	std::vector<ProjectileData> data(Projectile::Type::typeCount);

	data[Projectile::Type::Arrow].damage = 10;
	data[Projectile::Type::Arrow].speed = 500.f;
	data[Projectile::Type::Arrow].texture = TextureSheet::Arrow;
	data[Projectile::Type::Arrow].travelDistance = sf::Vector2f(300.f, 0.f);

	data[Projectile::Type::MiniBlast].damage = 10;
	data[Projectile::Type::MiniBlast].speed = 350.f;
	data[Projectile::Type::MiniBlast].texture = TextureSheet::MiniBlast;
	data[Projectile::Type::MiniBlast].travelDistance = sf::Vector2f(400.f, 0.f);

	data[Projectile::Type::MiniBlast1].damage = 10;
	data[Projectile::Type::MiniBlast1].speed = 350.f;
	data[Projectile::Type::MiniBlast1].texture = TextureSheet::MiniBlast;
	data[Projectile::Type::MiniBlast1].travelDistance = sf::Vector2f(400.f, 0.f);

	data[Projectile::Type::Longsword].damage = 50;
	data[Projectile::Type::Longsword].speed = 0.f;
	data[Projectile::Type::Longsword].texture = TextureSheet::Longsword;
	data[Projectile::Type::Longsword].travelDistance = sf::Vector2f(0.f, 50.f);

	return data;
}