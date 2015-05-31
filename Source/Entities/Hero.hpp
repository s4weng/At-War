#ifndef _HERO_HPP__
#define _HERO_HPP__

//#include "Entity.hpp"
//#include "AnimatedSprite.hpp"
#include "CommandQueue.hpp"
#include "Data.hpp"
#include "Projectile.hpp" //Entity.hpp

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
		walkUp,
		walkDown,
		attack,
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
	void updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue);
	void checkAttack(sf::Time deltaTime, CommandQueue& commandQueue);
	void createArrow(SceneNode& sceneNode, Projectile::Type type, Projectile::Side side, float x, float y, TextureContainer& textureContainer);
	void launchAttack();
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

	Command attackCommand;
	bool isAttack;
	int hitpoints;
};

#endif
