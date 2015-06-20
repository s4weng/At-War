#include "HeroMover.hpp"
#include <iostream>

HeroMover::HeroMover(float x, float y) : velocity(x, y){
}

void HeroMover::operator() (SceneNode& sceneNode, sf::Time) const {

	Hero &hero = static_cast<Hero&>(sceneNode); //command is performed on SceneNode

	if (hero.actionFinished() && hero.getPrevAction() <= 1){

		hero.setHeroAction(Hero::Action::Walk);
		hero.setVelocity(hero.getVelocity() + velocity);
		hero.updateDirection();
	}

	else
		hero.setPrevAction(Hero::Action::Stand);
}