#ifndef _HERO_HPP__
#define _HERO_HPP__

#include "Entity.hpp"
#include "AnimatedSprite.hpp"

class Hero : public Entity {

public:

	enum class heroClass {

		Archer,
		Mage,
	};

	enum class animationAction {

		standRight,
		standLeft,
		walkRight,
		walkLeft,
	};

	animationAction getPlayerAction();
	void setPlayerAction(animationAction action);
	void setAnimation(TextureContainer& textureContainer);
	void updateCurrentAnimation();

	void playCurrentAnimation();
	void updateCurrent(sf::Time deltaTime);

	Hero(heroClass classOfHero, TextureContainer& textureContainer);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	heroClass classOfHero;
	AnimatedSprite heroSprite;

	animationAction playerAction;

	//Declarations of animations
	Animation walkingRight, walkingLeft, standingRight, standingLeft;

	Animation* currentAnimation;
};

#endif