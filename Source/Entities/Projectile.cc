#include "Projectile.hpp"
#include "Data.hpp"
#include "World.hpp"

#include <cassert>
#include <math.h>

Projectile::Projectile(Projectile::Type type, Projectile::Side side, TextureContainer& textureContainer):
type(type),
side(side),
projectileSprite(textureContainer.get(projectileDataTable[type].texture), projectileDataTable[type].textureRect)
{

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

void Projectile::updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue){

	Entity::updateCurrent(deltaTime, commandQueue);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(projectileSprite, states);
}

sf::FloatRect Projectile::getBoundingRect() const {

	return getWorldTransform().transformRect(projectileSprite.getGlobalBounds());
}

bool Projectile::actionFinished() const {

	return true;
}