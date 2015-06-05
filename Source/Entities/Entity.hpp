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
	void updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue);
	void updateDirection();
	void setDirection(Direction direction);
	Direction getDirection() const;

private:

	Direction entityDirection;	
	sf::Vector2f entityVelocity;
};

#endif