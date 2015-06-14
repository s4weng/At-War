#include "HeroAttacker.hpp"

void HeroAttacker::operator() (SceneNode& sceneNode, sf::Time) const {
		
	Hero &hero = static_cast<Hero&>(sceneNode);

	if (hero.actionFinished() && hero.getPrevAction() <= 2){

		hero.setHeroAction(Hero::Action::Attack);
		hero.launchAttack();
	}

	else
		hero.setPrevAction(Hero::Action::Stand);
}