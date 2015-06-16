#ifndef _PROJECTILE_HPP__
#define _PROJECTILE_HPP__

#include "Entity.hpp"
#include "TextureInfo.hpp"

class Projectile : public Entity {

public:

	enum Type {
	
		Arrow,
		MiniBlast,
		typeCount
	};

	enum Side {

		Player,
		Enemy
	};

	Projectile(Projectile::Type type, Projectile::Side side, TextureContainer& textureContainer);

	virtual unsigned int getReceiver() const;
	float getMaxSpeed() const;
	int getDamage() const;
	void updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getBoundingRect() const;
	virtual bool actionFinished() const;

private:

	Projectile::Type type;
	Projectile::Side side;
	sf::Sprite projectileSprite;
};

#endif