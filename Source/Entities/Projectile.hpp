#ifndef _PROJECTILE_HPP__
#define _PROJECTILE_HPP__

#include "Entity.hpp"
#include "TextureInfo.hpp"
#include "AnimatedSprite.hpp"

class Projectile : public Entity {

public:

	enum Type {
	
		Arrow,
		MiniBlast1, //replace with different attack for mage
		MiniBlast,
		Longsword,
		typeCount
	};

	enum Side {

		Player,
		Enemy
	};

	enum Action {

		Flying,
		Breaking,
		actionCount
	};

	Projectile(Projectile::Type type, Projectile::Side side, TextureContainer& textureContainer, AnimationData& animationData);

	virtual unsigned int getReceiver() const;
	float getMaxSpeed() const;
	int getDamage() const;
	void setStartPosition(sf::Vector2f position);
	virtual void updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue, AnimationData& animationData);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getBoundingRect() const;
	virtual bool actionFinished() const;

	void playCurrentAnimation(bool flip = false);
	void setCurrentAnimation(Animation* animation);

private:

	Projectile::Type type;
	Projectile::Side side;

	AnimatedSprite projectileSprite;
	Animation* currentAnimation;

	Action action;

	sf::Vector2f startPosition;
};

#endif