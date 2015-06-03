#include "HeroMover.hpp"

HeroMover::HeroMover(float x, float y) : velocity(x, y){
}

void HeroMover::operator() (SceneNode& sceneNode, sf::Time) const {

	Hero &hero = static_cast<Hero&>(sceneNode); //command is performed on SceneNode
	hero.setVelocity(hero.getVelocity() + velocity);
}