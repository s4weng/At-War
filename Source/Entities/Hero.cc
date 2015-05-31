#include "Hero.hpp"

//replace this with a map (nested) or 2d array
/*textureSheet returnTextureSheet(Hero::heroClass classOfHero, Hero::Action action){

	switch (classOfHero) {

		case Hero::heroClass::Archer:

			if (action == Hero::Action::standRight || action == Hero::Action::standLeft)
				return textureSheet::standingArcher;

			else if (action == Hero::Action::walkRight || action == Hero::Action::walkLeft)
				return textureSheet::walkingArcher;

		case Hero::heroClass::Archmage:
		
			if (action == Hero::Action::standRight || action == Hero::Action::standLeft)
				return textureSheet::standingArchmage;

			else if (action == Hero::Action::walkRight || action == Hero::Action::walkLeft)
				return textureSheet::walkingArchmage;
	}
}*/
const std::vector<HeroData> data = initializeHeroes();

Hero::Hero(heroClass classOfHero, TextureContainer& textureContainer):
classOfHero(classOfHero),
heroSprite(textureContainer.get(data[classOfHero].texture)),
playerAction(Action::standRight),
attackCommand(),
isAttack(false),
attackTimer(sf::Time::Zero),
attackRateLevel(1)
//walkingRight(),
//walkingLeft(),
//standingRight(),
//standingLeft(),
//currentAnimation()
{

	heroSprite.setTexture(textureContainer.get(textureSheet::standingArcher));
	sf::FloatRect bounds = heroSprite.getLocalBounds();
	heroSprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

	attackCommand.receiver = Receiver::Scene;
	attackCommand.action = [this, &textureContainer] (SceneNode& sceneNode, sf::Time){

		createArrow(sceneNode, Projectile::Type::Arrow, Projectile::Side::Player, 0.f, 0.5f,textureContainer);
	};
	//setAnimation(textureContainer);
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

	//move(getVelocity() * deltaTime.asSeconds());
	//heroSprite.update(deltaTime);
}

void Hero::checkAttack(sf::Time deltaTime, CommandQueue& commandQueue){

	if (isAttack && attackTimer <= sf::Time::Zero){

		commandQueue.push(attackCommand);
		attackTimer += data[classOfHero].attackInterval / (attackRateLevel + 1.f);
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

	arrow->setPosition(300.f, 300.f);
	//arrow->setPosition(getWorldPosition() + offset);
	arrow->setVelocity(velocity);
	sceneNode.attachNode(std::move(arrow));
}

int Hero::getReceiver() const {

	switch (sideOfHero) {

		case heroFaction::Player:
			return Receiver::PlayerHero;

		case heroFaction::Ally:
			return Receiver::AlliedHero;

		case heroFaction::Opposition:
			return Receiver::EnemyHero;
	}
}

void Hero::launchAttack(){

	if (data[classOfHero].attackInterval != sf::Time::Zero)
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

/*void Hero::setAnimation(TextureContainer& textureContainer){

    //set up the animation frames
    walkingRight.setSpriteSheet(textureContainer.get(textureSheet::walkingArcher));
    walkingRight.addFrame(sf::IntRect(11, 11, 48, 70));
    walkingRight.addFrame(sf::IntRect(91, 12, 48, 70));
    walkingRight.addFrame(sf::IntRect(167, 8, 48, 70));
    walkingRight.addFrame(sf::IntRect(248, 10, 48, 70));
    walkingRight.addFrame(sf::IntRect(329, 10, 48, 70));

    walkingLeft.setSpriteSheet(textureContainer.get(textureSheet::walkingArcher));;
    walkingLeft.addFrame(sf::IntRect(330, 97, 48, 70));
    walkingLeft.addFrame(sf::IntRect(246, 97, 48, 70));
    walkingLeft.addFrame(sf::IntRect(172, 97, 48, 70));
    walkingLeft.addFrame(sf::IntRect(93, 97, 48, 70));
    walkingLeft.addFrame(sf::IntRect(9, 95, 48, 70));

    standingRight.setSpriteSheet(textureContainer.get(textureSheet::standingArcher));
    standingRight.addFrame(sf::IntRect(9,9,48,70));

    standingLeft.setSpriteSheet(textureContainer.get(textureSheet::standingArcher));
    standingLeft.addFrame(sf::IntRect(10,98,48,70));

    //set animation
    currentAnimation = &standingRight;
}*/

/*void Hero::playCurrentAnimation(){

	heroSprite.play(*currentAnimation);
}*/

/*void Hero::updateCurrentAnimation(){

	if (playerAction == Action::walkRight)
		currentAnimation = &walkingRight;

	else if (playerAction == Action::walkLeft)
		currentAnimation = &walkingLeft;

	else if (playerAction == Action::standRight)
		currentAnimation = &standingRight;

	else
		currentAnimation = &standingLeft;
}*/