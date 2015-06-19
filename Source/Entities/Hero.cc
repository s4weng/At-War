#include "Hero.hpp"
#include "World.hpp"
#include "AnimationData.hpp"

#include <iostream>

Hero::Hero(HeroClass heroClass, HeroFaction heroFaction, TextureContainer& textureContainer, AnimationData& animationData):
heroFaction(heroFaction), 
heroClass(heroClass),
heroSprite(),
prevAction(Action::Stand),
heroAction(Action::Stand),
attackCommand(),
attackTimer(sf::Time::Zero),
attackRateLevel(1){

	this->setCurrentAnimation(animationData.getAnimation(heroAction, heroClass));
	this->playCurrentAnimation();

	setHitpoints(100);
	setIsAttack(false);

	attackCommand.receiver = Receiver::Scene;
	attackCommand.action = [this, &textureContainer, &animationData] (SceneNode& sceneNode, sf::Time){

		createProjectile(sceneNode, 0.5f, -0.2f,textureContainer, animationData);
	};

	enemyAttackCommand.receiver = Receiver::Scene;
	enemyAttackCommand.action = [this, &textureContainer, &animationData] (SceneNode& sceneNode, sf::Time){

		createProjectile(sceneNode, 0.5f, -0.2f,textureContainer, animationData);
	};
}

void Hero::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(heroSprite, states);
}

Hero::Action Hero::getHeroAction() const {

	return heroAction;
}

Hero::Action Hero::getPrevAction() const {

	return prevAction;
}

void Hero::setHeroAction(Action action){

	heroAction = action;
	prevAction = heroAction;
}

void Hero::setPrevAction(Action action){

	prevAction = action;
}

bool Hero::actionFinished() const {

	return heroSprite.isFinished();
}

void Hero::setDefaultHeroAction(){

	heroAction = Hero::Action::Stand;
}

void Hero::playCurrentAnimation(bool flip){

	heroSprite.play(*currentAnimation, flip);
}

void Hero::setCurrentAnimation(Animation* animation){

	if (heroSprite.isFinished())
		currentAnimation = animation;
}

void Hero::updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue, AnimationData& animationData){

	setCurrentAnimation(animationData.getAnimation(heroAction, heroClass));
	(getDirection() == Entity::Direction::Right) ? playCurrentAnimation() : playCurrentAnimation(true);

	heroSprite.update(deltaTime);
	checkAttack(deltaTime, commandQueue);
	Entity::updateCurrent(deltaTime, commandQueue, animationData);
}

sf::FloatRect Hero::getBoundingRect() const {

	return getWorldTransform().transformRect(heroSprite.getGlobalBounds());
}


void Hero::checkAttack(sf::Time deltaTime, CommandQueue& commandQueue){

	if (isAttack && attackTimer <= sf::Time::Zero){

		if (heroFaction == HeroFaction::Player)
			commandQueue.push(attackCommand);
		else if (heroFaction == HeroFaction::Enemy)
			commandQueue.push(enemyAttackCommand);

		attackTimer += heroDataTable[heroClass].attackInterval / (attackRateLevel + 1.f);
		isAttack = false;
	}

	else if (attackTimer > sf::Time::Zero){

		attackTimer -= deltaTime;
		isAttack = false;
	}
}

void Hero::createProjectile(SceneNode& sceneNode, float x, float y, TextureContainer& textureContainer, AnimationData& animationData){

	setHeroAction(Hero::Action::Attack);

	std::shared_ptr<Projectile> weapon(new Projectile(Projectile::Type(heroClass), Projectile::Side(heroFaction), textureContainer, animationData));

	sf::Vector2f offset(x*heroSprite.getGlobalBounds().width, y*heroSprite.getGlobalBounds().height);
	sf::Vector2f velocity(weapon->getMaxSpeed(), 0);

	sf::Vector2f startPosition = getWorldPosition() + offset;
	weapon->setPosition(startPosition); //SFML method for starting position
	weapon->setStartPosition(startPosition); //for calculating projectile travel distance

	if (getDirection() == Entity::Direction::Left){

		weapon->setVelocity(-velocity);
		weapon->setDirection(Direction::Left);
	}

	else {
		
		weapon->setVelocity(velocity),
		weapon->setDirection(Direction::Right);
	}

	sceneNode.attachNode(std::move(weapon));
}

unsigned int Hero::getReceiver() const {

	switch (heroFaction) {

		case Hero::HeroFaction::Player:
			return Receiver::PlayerHero;

		case Hero::HeroFaction::Enemy:
			return Receiver::EnemyHero;
	}
}

void Hero::launchAttack(){

		isAttack = true;
}

Hero::HeroClass Hero::getHeroClass() const {

	return heroClass;
}