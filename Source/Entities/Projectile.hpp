#ifndef _PROJECTILE_HPP__
#define _PROJECTILE_HPP__

#include "Entity.hpp"
#include "TextureInfo.hpp"

class Projectile : public Entity {

public:

	enum Type {
	
		Arrow,
		//Spell,
		typeCount
	};

	enum class Side {

		Player,
		Allied,
		Enemy
	};

	Projectile(Projectile::Type type, Projectile::Side side, TextureContainer& textureContainer);

	//void guideTowards(sf::Vector2f position);
	//bool isGuided() const;

	virtual int getReceiver() const;
	virtual sf::FloatRect getBoundingRect() const;
	float getMaxSpeed() const;
	int getDamage() const;

private:

	virtual void updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states);

	Projectile::Type type;
	Projectile::Side side;
	sf::Sprite projectileSprite;
	sf::Vector2f direction;
};

#endif