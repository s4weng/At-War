#ifndef _HERO_HPP__
#define _HERO_HPP__

#include "CommandQueue.hpp"
#include "Data.hpp"
#include "Projectile.hpp" //Entity.hpp

extern const std::vector<HeroData> dataTable;

class Hero : public Entity {

public:

	enum heroClass {

		Archer,
		Archmage,
		Druid,
		typeCount,
	};

	enum Action {

		standRight,
		standLeft,
		walkRight,
		walkLeft,
		walkUp,
		walkDown,
		attack,
		actionCount
	};

	enum heroFaction {

		Player,
		Ally,
		Opposition
	};

	Action getPlayerAction();
	void setPlayerAction(Action action);

	void updateCurrent(sf::Time deltaTime, CommandQueue& commandQueue);
	void checkAttack(sf::Time deltaTime, CommandQueue& commandQueue);
	void createArrow(SceneNode& sceneNode, Projectile::Type type, Projectile::Side side, float x, float y, TextureContainer& textureContainer);
	void launchAttack();
	int getHitpoints() const;
	Hero::heroClass getHeroClass() const;
	void heal(int hp);
	void damage(int hp);
	bool isAlive() const;

	Hero(heroClass classOfHero, heroFaction sideOfHero, TextureContainer& textureContainer);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual unsigned int getReceiver() const;

	virtual sf::FloatRect getBoundingRect() const;

private:

	heroFaction sideOfHero;
	heroClass classOfHero;

	sf::Sprite heroSprite;
	Action playerAction;

	Command attackCommand;
	int hitpoints;
	sf::Time attackTimer;
	int attackRateLevel;
};

#endif
