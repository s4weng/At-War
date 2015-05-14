#ifndef _ENTITY_HPP__
#define _ENTITY_HPP__

class Entity {

public:

	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f getVelocity() const;

private:

	sf::Vector2f entityVelocity;
};

#endif