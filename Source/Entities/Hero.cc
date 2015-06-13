#include "Hero.hpp"
#include "AnimationData.hpp"

#include <iostream>

const std::vector<HeroData> dataTable = initializeHeroes();

Hero::Hero(HeroClass heroClass, HeroFaction heroFaction, TextureContainer& textureContainer):
heroFaction(heroFaction), 
heroClass(heroClass),
heroSprite(),
prevAction(Action::Stand),
heroAction(Action::Stand),
attackCommand(),
attackTimer(sf::Time::Zero),
attackRateLevel(1){

	setHitpoints(100);
	setIsAttack(false);
	//sf::FloatRect bounds = heroSprite.getLocalBounds();
	//heroSprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

	attackCommand.receiver = Receiver::Scene;
	attackCommand.action = [this, &textureContainer] (SceneNode& sceneNode, sf::Time){

		createArrow(sceneNode, Projectile::Type::Arrow, Projectile::Side::Player, 0.5f, 0.28f,textureContainer);
	};

	enemyAttackCommand.receiver = Receiver::Scene;
	enemyAttackCommand.action = [this, &textureContainer] (SceneNode& sceneNode, sf::Time){

		createArrow(sceneNode, Projectile::Type::Arrow, Projectile::Side::Enemy, 0.5f, 0.5f,textureContainer);
	};
}

void Hero::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(heroSprite, states);
}

Hero::Action Hero::getHeroAction() const {

	return heroAction;
}

bool Hero::setHeroAction(Action action){

	//action priority is ordered declared in enum; don't let hero switch to lower priority action if higher one is in play
	if (action == Hero::Action::Stand){

		heroAction = action;
		prevAction = heroAction;
		return true;
	}

	else if (action == Hero::Action::Walk && prevAction <= 1){

		heroAction = action;
		prevAction = heroAction;
		return true;
	}

	else if (action == Hero::Action::Attack && prevAction <=2){

		heroAction = action;
		prevAction = heroAction;
		return true;		
	}

	else if (action == Hero::Action::Flinch && prevAction <=3){

		heroAction = action;
		prevAction = heroAction;
		return true;
	}

	else if (action == Hero::Action::Fall && prevAction <=4){

		heroAction = action;
		prevAction = heroAction;			
		return true;
	}

	prevAction = Hero::Action::Stand;
	return false;
}


void Hero::setDefaultHeroAction(){

	heroAction = Hero::Action::Stand;
}


void Hero::playCurrentAnimation(bool flip){

	heroSprite.play(*currentAnimation, flip);
}


void Hero::updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue){

	heroSprite.update(deltaTime);
	checkAttack(deltaTime, commandQueue);
	Entity::updateCurrent(deltaTime, commandQueue);
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

		attackTimer += dataTable[heroClass].attackInterval / (attackRateLevel + 1.f);
		isAttack = false;
	}

	else if (attackTimer > sf::Time::Zero){

		attackTimer -= deltaTime;
		isAttack = false;
	}
}

void Hero::createArrow(SceneNode& sceneNode, Projectile::Type type, Projectile::Side side, float x, float y, TextureContainer& textureContainer){

	std::shared_ptr<Projectile> arrow(new Projectile(type, side, textureContainer));

	sf::Vector2f offset(x*heroSprite.getGlobalBounds().width, y*heroSprite.getGlobalBounds().height);
	sf::Vector2f velocity(arrow->getMaxSpeed(), 0);

	arrow->setPosition(getWorldPosition() + offset);

	(getDirection() == Entity::Direction::Left) ? 
	arrow->setVelocity(-velocity),
	arrow->setDirection(Direction::Left) :
	arrow->setVelocity(velocity),
	arrow->setDirection(Direction::Right);

	sceneNode.attachNode(std::move(arrow));
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

void Hero::setCurrentAnimation(Animation* animation){

	currentAnimation = animation;
}