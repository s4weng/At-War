#include "Projectile.hpp"
#include "Data.hpp"

#include <cassert>
#include <math.h>
#include <iostream>

const std::vector<ProjectileData> data = initializeProjectiles();

Projectile::Projectile(Projectile::Type type, Projectile::Side side, TextureContainer& textureContainer):
type(type),
side(side),
projectileSprite(textureContainer.get(data[type].texture)),
hitpoints(10){

	sf::FloatRect bounds = projectileSprite.getLocalBounds();
	projectileSprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}

unsigned int Projectile::getReceiver() const {

	if (side == Side::Enemy)
		return Receiver::EnemyProjectile;

	else if (side == Side::Allied)
		return Receiver::AlliedProjectile;

	else
		return Receiver::PlayerProjectile;
}

float Projectile::getMaxSpeed() const {

	return data[type].speed;
}

int Projectile::getDamage() const {

	return data[type].damage;
}

void Projectile::updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue){

	Entity::updateCurrent(deltaTime, commandQueue);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(projectileSprite, states);
}

sf::FloatRect Projectile::getBoundingRect() const {

	return getWorldTransform().transformRect(projectileSprite.getGlobalBounds());
}

void Projectile::damage(int hp){

	hitpoints -= hp;
}

bool Projectile::isDead() const {

	return (hitpoints <= 0);
}