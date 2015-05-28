#include "Entity.hpp"

void Entity::setVelocity(float velocityX, float velocityY){

	entityVelocity.x = velocityX;
}

sf::Vector2f Entity::getVelocity() const {

	return entityVelocity;
}

void Entity::updateCurrent(sf::Time deltaTime){

	move(entityVelocity * deltaTime.asSeconds());
}