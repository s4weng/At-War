#ifndef _HERO_HPP__
#define _HERO_HPP__

#include "Entity.hpp"

class Hero : public Entity {

public:

	enum class heroClass {

		Archer,
		Mage,
	};

	explicit Hero(heroClass classOfHero);

private:

	heroClass classOfHero;
};

#endif