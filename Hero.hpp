#ifndef _HERO_HPP__
#define _HERO_HPP__

#include "Entity.hpp"
#include "AnimatedSprite.hpp"

class Hero : public Entity {

public:

	enum class heroClass {

		Archer,
		Mage
	};

	//change to two enum classes later on; left and right
	enum Action {

		standRight,
		standLeft,
		walkRight,
		walkLeft,
		ActionCount
	};

	enum heroFaction {

		Player,
		Ally,
		Opposition
	};

	Action getPlayerAction();
	void setPlayerAction(Action action);
	void setAnimation(TextureContainer& textureContainer);
	void updateCurrentAnimation();

	void playCurrentAnimation();
	void updateCurrent(sf::Time deltaTime);

	Hero(heroClass classOfHero, TextureContainer& textureContainer, heroFaction side);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual int getReceiver() const;

private:

	heroFaction sideOfHero;

	heroClass classOfHero;

	AnimatedSprite heroSprite;

	Action playerAction;

	//Declarations of animations
	Animation walkingRight, walkingLeft, standingRight, standingLeft;

	Animation* currentAnimation;
};

#endif