#ifndef _HERO_HPP__
#define _HERO_HPP__

#include "CommandQueue.hpp"
#include "Data.hpp"
#include "Projectile.hpp" //Entity.hpp
#include "AnimatedSprite.hpp"

class AnimationData;

class Hero : public Entity {

public:

	enum HeroClass { //Match HeroClass enum index with Projectile::Type enum index

		Archer,
		Druid,
		Crusader,
		classCount,
	};

	enum Action { //Match index with Projectile::Side

		Stand,
		Walk,
		Attack,
		Flinch,
		Fall,
		actionCount
	};

	enum HeroFaction {

		Player,
		Enemy
	};

	Hero::HeroClass getHeroClass() const;
	Action getHeroAction() const;
	Action getPrevAction() const;
	void setHeroAction(Action action);
	void setPrevAction(Action action);
	void setDefaultHeroAction();
	void playCurrentAnimation(bool flip = false);

	virtual void updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue);
	void checkAttack(sf::Time deltaTime, CommandQueue& commandQueue);
	void createProjectile(SceneNode& sceneNode, float x, float y, TextureContainer& textureContainer);
	void launchAttack();

	void setCurrentAnimation(Animation* animation);
	virtual bool actionFinished() const;

	Hero(HeroClass heroClass, HeroFaction heroFaction, TextureContainer& textureContainer);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual unsigned int getReceiver() const;
	virtual sf::FloatRect getBoundingRect() const;

private:

	HeroFaction heroFaction;
	HeroClass heroClass;

	AnimatedSprite heroSprite;

	Animation* prevAnimation;
	Animation* currentAnimation;

	Action prevAction;
	Action heroAction;

	Command attackCommand;
	Command enemyAttackCommand;
	sf::Time attackTimer;
	int attackRateLevel;
};

#endif
