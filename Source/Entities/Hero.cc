#include "Hero.hpp"

const std::vector<HeroData> dataTable = initializeHeroes();

Hero::Hero(heroClass classOfHero, heroFaction sideOfHero, TextureContainer& textureContainer):
sideOfHero(sideOfHero), 
classOfHero(classOfHero),
heroSprite(textureContainer.get(dataTable[classOfHero].texture)),
playerAction(Action::standRight),
attackCommand(),
attackTimer(sf::Time::Zero),
attackRateLevel(1){

	setIsAttack(false);

	sf::FloatRect bounds = heroSprite.getLocalBounds();
	heroSprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

	attackCommand.receiver = Receiver::Scene;
	attackCommand.action = [this, &textureContainer] (SceneNode& sceneNode, sf::Time){

		createArrow(sceneNode, Projectile::Type::Arrow, Projectile::Side::Player, 0.5f, -0.1f,textureContainer);
	};
}

void Hero::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(heroSprite, states);
}

Hero::Action Hero::getPlayerAction(){

	return playerAction;
}

void Hero::setPlayerAction(Action action){

	playerAction = action;
}

void Hero::updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue){

	checkAttack(deltaTime, commandQueue);
	Entity::updateCurrent(deltaTime, commandQueue);
}

sf::FloatRect Hero::getBoundingRect() const {

	return getWorldTransform().transformRect(heroSprite.getGlobalBounds());
}


void Hero::checkAttack(sf::Time deltaTime, CommandQueue& commandQueue){

	if (isAttack && attackTimer <= sf::Time::Zero){

		commandQueue.push(attackCommand);
		attackTimer += dataTable[classOfHero].attackInterval / (attackRateLevel + 1.f);
		isAttack = false;
	}

	else if (attackTimer > sf::Time::Zero){

		attackTimer -= deltaTime;
		isAttack = false;
	}
}

void Hero::createArrow(SceneNode& sceneNode, Projectile::Type type, Projectile::Side side, float x, float y, TextureContainer& textureContainer){

	std::unique_ptr<Projectile> arrow(new Projectile(type, side, textureContainer));

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

	switch (sideOfHero) {

		case Hero::heroFaction::Player:
			return Receiver::PlayerHero;

		case Hero::heroFaction::Ally:
			return Receiver::AlliedHero;

		case Hero::heroFaction::Opposition:
			return Receiver::EnemyHero;
	}
}

void Hero::launchAttack(){

		isAttack = true;
}

int Hero::getHitpoints() const {

	return hitpoints;
}

void Hero::heal(int hp){

	hitpoints += hp;
}

void Hero::damage(int hp){

	hitpoints -= hp;
}

bool Hero::isAlive() const {

	return (hitpoints > 0);
}

Hero::heroClass Hero::getHeroClass() const {

	return classOfHero;
}
