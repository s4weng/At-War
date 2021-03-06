#ifndef _HERO_HPP__
#define _HERO_HPP__

#include "CommandQueue.hpp"
#include "Data.hpp"
#include "Projectile.hpp" //Entity.hpp
#include "AnimatedSprite.hpp"

class Hero : public Entity {

public:

	enum HeroClass { //Match HeroClass enum index with Projectile::Type enum index

		Archer,
		Mage,
		Druid,
		Wolf, //currently not matched to weapon
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

	virtual void updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue, AnimationData& animationData);
	void checkAttack(sf::Time deltaTime, CommandQueue& commandQueue);
	void createProjectile(SceneNode& sceneNode, float x, float y, TextureContainer& textureContainer, AnimationData& animationData);
	void launchAttack();
	
	void playCurrentAnimation(bool flip = false);
	void setCurrentAnimation(Animation* animation);
	virtual bool actionFinished() const;

	Hero(HeroClass heroClass, HeroFaction heroFaction, TextureContainer& textureContainer, AnimationData& animationData);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual unsigned int getReceiver() const;
	virtual sf::FloatRect getBoundingRect() const;

	void playSoundEffect(CommandQueue& commandQueue, SoundEffect soundEffect);

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
