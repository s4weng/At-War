#ifndef _HERO_HPP__
#define _HERO_HPP__

#include "Entity.hpp"
#include "AnimatedSprite.hpp"

class Hero : public Entity {

public:

	enum heroClass {

		Archer,
		Archmage,
		Druid,
		typeCount,
	};

	enum Action {

		standRight,
		standLeft,
		walkRight,
		walkLeft,
		actionCount
	};

	enum heroFaction {

		Player,
		Ally,
		Opposition
	};

	Action getPlayerAction();
	void setPlayerAction(Action action);
	//void setAnimation(TextureContainer& textureContainer);
	//void updateCurrentAnimation();

	//void playCurrentAnimation();
	void updateCurrent(sf::Time deltaTime);

	int getHitpoints() const;
	void heal(int hp);
	void damage(int hp);
	bool isAlive() const;

	//Hero(heroClass classOfHero, TextureContainer& textureContainer, heroFaction side);
	Hero(heroClass classOfHero, TextureContainer& textureContainer);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual int getReceiver() const;

private:

	heroFaction sideOfHero;
	heroClass classOfHero;

	sf::Sprite heroSprite;
	//AnimatedSprite heroSprite;
	Action playerAction;

	//Declarations of animations
	//Animation walkingRight, walkingLeft, standingRight, standingLeft;
	//Animation* currentAnimation;

	int hitpoints;
};

#endif