#include "Entity.hpp"

void Entity::setVelocity(sf::Vector2f velocity){

	entityVelocity = velocity;
}

sf::Vector2f getVelocity() const{

	return entityVelocity;
}