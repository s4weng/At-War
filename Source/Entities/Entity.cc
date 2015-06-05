#include "Entity.hpp"

#include <iostream>

void Entity::setVelocity(float velocityX, float velocityY){

	entityVelocity.x = velocityX;
	entityVelocity.y = velocityY;
}

void Entity::setVelocity(sf::Vector2f velocity){

	entityVelocity = velocity;
}


sf::Vector2f Entity::getVelocity() const {

	return entityVelocity;
}

void Entity::updateDirection(){

	if (entityVelocity.x > 0.f)
		entityDirection = Direction::Right;

	if (entityVelocity.x < 0.f)
		entityDirection = Direction::Left;
}

void Entity::setDirection(Direction direction){

	entityDirection = direction;
}

Entity::Direction Entity::getDirection() const {

	return entityDirection;
}

void Entity::updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue){

	move(entityVelocity * deltaTime.asSeconds());
}