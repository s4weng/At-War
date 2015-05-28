#include "Data.hpp"
#include "Hero.hpp"

std::vector<HeroData> initializeHeroes(){

	std::vector<HeroData> data(Hero::heroClass::typeCount);

	data[hero::heroClass::Archer].hitpoints = 100;
	data[hero::heroClass::Archer].texture = textureSheet::standingArcher;
	data[hero::heroClass::Archer].faction = heroFaction::Player;

	data[hero::heroClass::Archmage].hitpoints = 80;
	data[hero::heroClass::Archmage].texture = textureSheet::standingArchmage;
	data[hero::heroClass::Archmage].faction = heroFaction::Ally;

	data[hero::heroClass::Druid].hitpoints = 30;
	data[hero::heroClass::Druid].texture = textureSheet::standingDruid;
	data[hero::heroClass::Druid].faction = heroFaction::Opposition;

	return data;
}