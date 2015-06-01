#include "Projectile.hpp"
#include "Data.hpp"

#include <cassert>
#include <cmath>

const std::vector<ProjectileData> data = initializeProjectiles();

Projectile::Projectile(Projectile::Type type, Projectile::Side side, TextureContainer& textureContainer):
type(type),
side(side),
projectileSprite(textureContainer.get(data[type].texture)),
direction(){

	sf::FloatRect bounds = projectileSprite.getLocalBounds();
	projectileSprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}

/*void Projectile::guideTowards(sf::Vector2f position){

	assert(isGuided());

	position-= getWorldPosition();
	assert(position != sf::Vector2f(0.f, 0.f));
	direction = position / std::sqrt(position.x * position.x + position.y * position.y);
}*/

int Projectile::getReceiver() const {

	if (side == Side::Enemy)
		return Receiver::EnemyProjectile;

	else if (side == Side::Allied)
		return Receiver::AlliedProjectile;

	else
		return Receiver::PlayerProjectile;
}

sf::FloatRect Projectile::getBoundingRect() const {

	return getWorldTransform().transformRect(projectileSprite.getGlobalBounds());
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