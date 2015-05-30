#include "Entity.hpp"

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

void Entity::updateCurrent(sf::Time deltaTime){

	move(entityVelocity * deltaTime.asSeconds());
}