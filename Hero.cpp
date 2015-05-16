#include "Hero.hpp"
#include <iostream>

//replace this with a map (nested) or 2d array
textureSheet returnTextureSheet(Hero::heroClass classOfHero, Hero::animationAction action){

	switch (classOfHero) {

		case Hero::heroClass::Archer:

			if (action == Hero::animationAction::standRight || action == Hero::animationAction::standLeft)
				return textureSheet::standingArcher;

			else if (action == Hero::animationAction::walkRight || action == Hero::animationAction::walkLeft)
				return textureSheet::walkingArcher;

		case Hero::heroClass::Mage:
		
			if (action == Hero::animationAction::standRight || action == Hero::animationAction::standLeft)
				return textureSheet::standingMage;

			else if (action == Hero::animationAction::walkRight || action == Hero::animationAction::walkLeft)
				return textureSheet::walkingMage;
	}
}

Hero::Hero(heroClass classOfHero, TextureContainer& textureContainer):
classOfHero(classOfHero),
heroSprite(),
playerAction(animationAction::standRight),
walkingRight(),
walkingLeft(),
standingRight(),
standingLeft(),
currentAnimation() {

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

Hero::animationAction Hero::getPlayerAction(){

	return playerAction;
}

void Hero::updateCurrentAnimation(){

	if (playerAction == animationAction::walkRight)
		currentAnimation = &walkingRight;

	else if (playerAction == animationAction::walkLeft)
		currentAnimation = &walkingLeft;

	else if (playerAction == animationAction::standRight)
		currentAnimation = &standingRight;

	else
		currentAnimation = &standingLeft;
}

void Hero::setPlayerAction(animationAction action){

	playerAction = action;
}

void Hero::playCurrentAnimation(){

	heroSprite.play(*currentAnimation);
}

void Hero::updateCurrent(sf::Time deltaTime){

	move(getVelocity() * deltaTime.asSeconds());
	heroSprite.update(deltaTime);
}
