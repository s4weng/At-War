#include "Hero.hpp"
#include <iostream>

//replace this with a map (nested) or 2d array
textureSheet returnTextureSheet(Hero::heroClass classOfHero, Hero::Action action){

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
}

Hero::Hero(heroClass classOfHero, TextureContainer& textureContainer, heroFaction side):
sideOfHero(side),
classOfHero(classOfHero),
heroSprite(),
playerAction(Action::standRight),
walkingRight(),
walkingLeft(),
standingRight(),
standingLeft(),
currentAnimation(){

	setAnimation(textureContainer);
}

void Hero::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(heroSprite, states);
}


void Hero::setAnimation(TextureContainer& textureContainer){

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
}

Hero::Action Hero::getPlayerAction(){

	return playerAction;
}

void Hero::updateCurrentAnimation(){

	if (playerAction == Action::walkRight)
		currentAnimation = &walkingRight;

	else if (playerAction == Action::walkLeft)
		currentAnimation = &walkingLeft;

	else if (playerAction == Action::standRight)
		currentAnimation = &standingRight;

	else
		currentAnimation = &standingLeft;
}

void Hero::setPlayerAction(Action action){

	playerAction = action;
}

void Hero::playCurrentAnimation(){

	heroSprite.play(*currentAnimation);
}

void Hero::updateCurrent(sf::Time deltaTime){

	move(getVelocity() * deltaTime.asSeconds());
	heroSprite.update(deltaTime);
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

int Hero::getHitpoints() const {

	return hitpoints;
}

void Hero::heal(int hp){

	hitpoints += hp;
}

void Hero::damage(int hp){

	hitpoints -= damage;
}

bool Hero::isAlive() const {

	return (hitpoints > 0) ? true : false;
}