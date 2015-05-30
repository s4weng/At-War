#ifndef _ENTITY_HPP__
#define _ENTITY_HPP__

#include "TextureInfo.hpp"
#include "SceneNode.hpp"

class Entity : public SceneNode {

public:

	void setVelocity(float velocityX, float velocityY);
	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f getVelocity() const;

private:

	void updateCurrent(sf::Time deltaTime);

	sf::Vector2f entityVelocity;
};

#endif