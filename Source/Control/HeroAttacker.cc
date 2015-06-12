#include "HeroAttacker.hpp"

void HeroAttacker::operator() (SceneNode& sceneNode, sf::Time) const {
		
	Hero &hero = static_cast<Hero&>(sceneNode);
	hero.setHeroAction(Hero::Action::Attack);
	hero.launchAttack();
}