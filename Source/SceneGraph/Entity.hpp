#ifndef _ENTITY_HPP__
#define _ENTITY_HPP__

#include "TextureInfo.hpp"
#include "SceneNode.hpp"

class Entity : public SceneNode {

public:

	enum class Direction {

		Left,
		Right
	};

	void setVelocity(float velocityX, float velocityY);
	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f getVelocity() const;
	virtual void updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue, AnimationData& animationData);
	void updateDirection();
	void setDirection(Direction direction);
	Direction getDirection() const;

	void setHitpoints(int hp);
	int getHitpoints() const;
	void damage(int hp);
	bool isDead() const;

	virtual bool actionFinished() const = 0;

private:

	Direction entityDirection;	
	sf::Vector2f entityVelocity;
	int entityHitpoints;
};

#endif