#include "Projectile.hpp"
#include "Data.hpp"
#include "World.hpp"

#include <cassert>
#include <math.h>

#include <iostream>

Projectile::Projectile(Projectile::Type type, Projectile::Side side, TextureContainer& textureContainer, AnimationData& animationData):
type(type),
side(side),
projectileSprite(),
action(Action::Flying)
{

	setCurrentAnimation(animationData.getAnimation(action, type));
	playCurrentAnimation();

	setHitpoints(10);
	sf::FloatRect bounds = projectileSprite.getLocalBounds();
	projectileSprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}

unsigned int Projectile::getReceiver() const {

	if (side == Side::Enemy)
		return Receiver::EnemyProjectile;

	else
		return Receiver::PlayerProjectile;
}

float Projectile::getMaxSpeed() const {

	return projectileDataTable[type].speed;
}

int Projectile::getDamage() const {

	return projectileDataTable[type].damage;
}

void Projectile::playCurrentAnimation(bool flip){

	projectileSprite.play(*currentAnimation, flip);
}

void Projectile::setCurrentAnimation(Animation* animation){

	currentAnimation = animation;
}

void Projectile::setStartPosition(sf::Vector2f position){

	startPosition = position;
}

void Projectile::updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue, AnimationData& animationData){

	//if projectile has exceeded its travel distance
	if (abs(SceneNode::getWorldPosition().x - startPosition.x) > projectileDataTable[type].travelDistance.x || abs(SceneNode::getWorldPosition().y - startPosition.y) > projectileDataTable[type].travelDistance.y)
		setHitpoints(0);

	if (getHitpoints() <= 0) action = Projectile::Action::Breaking;

	setCurrentAnimation(animationData.getAnimation(action, type));
	(getDirection() == Entity::Direction::Right) ? playCurrentAnimation() : playCurrentAnimation(true);

	Entity::updateCurrent(deltaTime, commandQueue, animationData);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(projectileSprite, states);
}

sf::FloatRect Projectile::getBoundingRect() const {

	return getWorldTransform().transformRect(projectileSprite.getGlobalBounds());
}

bool Projectile::actionFinished() const {

	if (action == Projectile::Action::Flying) return false;

	else return true;
}