#include "HeroAttacker.hpp"

void HeroAttacker::operator() (SceneNode& sceneNode, sf::Time) const {
		
	Hero &hero = static_cast<Hero&>(sceneNode);

	if (hero.actionFinished() && hero.getPrevAction() <= 2)
		hero.launchAttack();
	else
		hero.setPrevAction(Hero::Action::Stand);
}