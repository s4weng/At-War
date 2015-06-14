#include "World.hpp"

#include "Receiver.hpp"
#include <iostream>

#define MAXHP 100

World::World(sf::RenderWindow& window):
window(window),
view(window.getDefaultView()),
battlefield(sf::FloatRect(0.f, 0.f, 1500.f, view.getSize().y)),
worldBounds(0.f, 0.f, 3000.f, view.getSize().y),
playerSpawnPosition(view.getSize().x/2.f, worldBounds.height - view.getSize().y/2.f),
playerHero(nullptr),
scrollSpeed(0.f),
animationData(textureContainer){

loadTextures();
initScene();
view.setCenter(playerSpawnPosition);
}


void World::loadTextures(){

	//load the spritesheets
    try {

    	textureContainer.load(TextureSheet::Background, "Images/Background.png");
    }

    catch (std::runtime_error& exception){

    	std::cout << "Exception occurred: " << exception.what() << std::endl;
    	return;
    }
}


void World::initScene(){

	//initialize scene layers, attach to scene graph's root node
	for (int i = 0; i < LayerCount; ++i){

		SceneNode::sceneNodePtr layer(new SceneNode());
		//enums are named constants, so sceneLayers[0] = sceneLayers[Background]
		sceneLayers[i] = layer.get();
		sceneGraph.attachNode(std::move(layer));
	}

	//set up background, repeat itself
	sf::Texture& texture = textureContainer.get(TextureSheet::Background);
	sf::IntRect textureRect(worldBounds);
	texture.setRepeated(true);

	//SpriteNode that links to background texture
	std::shared_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[Background]->attachNode(std::move(backgroundSprite));

	std::shared_ptr<Hero> mainHero(new Hero(Hero::HeroClass::Archer, Hero::HeroFaction::Player, textureContainer));
	playerHero = mainHero.get();
	playerHero->setDirection(Entity::Direction::Right);
	playerHero->setPosition(playerSpawnPosition);
	sceneLayers[Ground]->attachNode(std::move(mainHero));

	addEnemySpawns();
	spawnEnemies();
	updateAnimations();
	playAnimations();
}


void World::draw(){

	window.setView(view);
	window.draw(*sceneLayers[Background]);
	sceneLayers[Ground]->sortChildren();
	window.draw(*sceneLayers[Ground]);
}


void World::update(sf::Time deltaTime){

	adjustView(deltaTime);

	updateEntities();

	removeOutsideBounds();

	//forward any command in the queue to the scene graph
	while (!commandQueue.isEmpty())
		sceneLayers[Ground]->onCommand(commandQueue.pop(), deltaTime);

	//handleCollisions();
	sceneGraph.removeDead();
	removeDead();
	updateAnimations();
	playAnimations();

	//spawnEnemies();

	sceneGraph.update(deltaTime, commandQueue);

	//checkPlayerBounds();
}


void World::updateAnimations(){

	playerHero->setCurrentAnimation(animationData.getAnimation(playerHero->getHeroAction(), playerHero->getHeroClass()));

	for (auto& enemyHero : currentEnemies)
		enemyHero->setCurrentAnimation(animationData.getAnimation(enemyHero->getHeroAction(), enemyHero->getHeroClass()));
}

void World::playAnimations(){

	(playerHero->getDirection() == Entity::Direction::Right) ? playerHero->playCurrentAnimation() : playerHero->playCurrentAnimation(true);

	for (auto& enemyHero : currentEnemies)
		(enemyHero->getDirection() == Entity::Direction::Right) ? enemyHero->playCurrentAnimation() : enemyHero->playCurrentAnimation(true);
}


void World::updateEntities(){

	playerHero->updateDirection();
	updateEnemyDirections();
	playerHero->setVelocity(0.f, 0.f);
	playerHero->setDefaultHeroAction();

	for (auto& enemyHero : currentEnemies)
		enemyHero->setDefaultHeroAction();

	moveEnemies();
}


void World::adjustView(sf::Time deltaTime){

	float deltaMovement = playerHero->getPosition().x - view.getCenter().x;

	if (deltaMovement > 0){
		float viewBound = view.getCenter().x + view.getSize().x / 2.f;
		float battlefieldBound = battlefield.getCenter().x + battlefield.getSize().x / 2.f;

		if (deltaMovement + viewBound < battlefieldBound)
			view.move(playerHero->getVelocity().x * deltaTime.asSeconds(), 0.f);
	}

	else if (deltaMovement < 0){

		float viewBound = view.getCenter().x - view.getSize().x / 2.f;
		float battlefieldBound = battlefield.getCenter().x - battlefield.getSize().x / 2.f;

		if (deltaMovement + viewBound > battlefieldBound)
			view.move(playerHero->getVelocity().x * deltaTime.asSeconds(), 0.f);
	}
}


void World::checkPlayerBounds(){

	//ensure player doesn't leave visible area of our world
	//viewBounds calculates the current top-left corner of battlefield view
	sf::FloatRect viewBounds(battlefield.getCenter() - battlefield.getSize()/2.f, battlefield.getSize());
	const float borderDistance = 18.f;

	sf::Vector2f playerPosition = playerHero->getPosition();
	playerPosition.x = std::max(playerPosition.x, viewBounds.left + borderDistance);
	playerPosition.x = std::min(playerPosition.x, viewBounds.left + viewBounds.width - borderDistance);
	playerPosition.y = std::max(playerPosition.y, viewBounds.top + borderDistance + 20.f);
	playerPosition.y = std::min(playerPosition.y, viewBounds.top + viewBounds.height - borderDistance - 20.f);
	playerHero->setPosition(playerPosition);
}


CommandQueue& World::getCommandQueue(){

	return commandQueue;
}


bool World::checkReceivers(SceneNode::Pair& colliders, Receiver::Receiver first, Receiver::Receiver second){

	unsigned int firstReceiver = colliders.first->getReceiver();
	unsigned int secondReceiver = colliders.second->getReceiver();

	if (first & firstReceiver && second & secondReceiver)
		return true;

	//swap to follow proper ordering
	else if (first & secondReceiver && second & firstReceiver){

		std::swap(colliders.first, colliders.second);
		return true;
	}

	else
		return false;
}


void World::handleCollisions(){

	//keep pairs unique; will use minmax to insert them
	std::set<SceneNode::Pair> collisionPairs;
	sceneGraph.checkSceneCollision(sceneGraph, collisionPairs);

	for (SceneNode::Pair pair : collisionPairs){

		/*//player collides with an enemy, if either are (melee) attacking the other
		if (checkReceivers(pair, Receiver::PlayerHero, Receiver::EnemyHero){

			if (playerHero->getIsAttack())

			if (enemyHero->getIsAttack())

		}*/

		//two projectiles collide
	    if (checkReceivers(pair, Receiver::PlayerProjectile, Receiver::EnemyProjectile)){

	    	auto& firstProjectile = static_cast<Projectile&>(*pair.first);
	    	auto& secondProjectile = static_cast<Projectile&>(*pair.second);

	    	firstProjectile.damage(10);
	    	secondProjectile.damage(10);
	    }

		//player or enemy collides with range attack
		else if (checkReceivers(pair, Receiver::PlayerHero, Receiver::EnemyProjectile)){
	    
	    	auto& projectile = static_cast<Projectile&>(*pair.second);
			playerHero->damage(projectile.getDamage());
			projectile.damage(10);
		}

		else if (checkReceivers(pair, Receiver::EnemyHero, Receiver::PlayerProjectile)){

	    	auto& projectile = static_cast<Projectile&>(*pair.second);
	    	auto& enemyHero = static_cast<Hero&>(*pair.first);

			projectile.damage(10);
			enemyHero.damage(50);
		}

	}
}


void World::removeDead(){

	auto removeBegin = std::remove_if(currentEnemies.begin(), currentEnemies.end(), std::mem_fn(&SceneNode::isDead));
	currentEnemies.erase(removeBegin, currentEnemies.end());
}


void World::removeOutsideBounds(){

	Command command;
	command.receiver = Receiver::Projectile | Receiver::EnemyHero;
	command.action = ([this] (SceneNode& sceneNode, sf::Time){

		Entity& entity = static_cast<Entity&>(sceneNode);

		sf::FloatRect rect(battlefield.getCenter().x - (battlefield.getSize().x / 2.f), 0, battlefield.getSize().x, battlefield.getSize().y);

		//kill entity outside battlefield; change value according to max entity HP
		if (!(rect.intersects(entity.getBoundingRect())))
			entity.damage(MAXHP);
	});

	commandQueue.push(command);
}


void World::moveEnemies(){

	for (auto& enemyHero : currentEnemies){

		if (!moveTowards(enemyHero)){

			if (enemyHero->actionFinished() && enemyHero->getPrevAction() <= 2)
				enemyHero->launchAttack();
			else
				enemyHero->setPrevAction(Hero::Action::Stand);
		}

		else
			enemyHero->setHeroAction(Hero::Action::Walk);
	}
}


bool World::moveTowards(std::shared_ptr<Hero> enemyHero){

	float x = 0, y = 0;

	if (enemyHero->actionFinished() && enemyHero->getPrevAction() <= 1){

		float enemyAttackDistance = dataTable[enemyHero->getHeroClass()].attackDistance;
		float enemySpeed = dataTable[enemyHero->getHeroClass()].speed;
		float distanceDiffX = playerHero->getPosition().x - enemyHero->getPosition().x;
		float distanceDiffY = playerHero->getPosition().y - enemyHero->getPosition().y;


		//make sure enemy faces correct direction if player moves to other side
		if (distanceDiffX > 0)
			enemyHero->setDirection(Entity::Direction::Right);

		if (distanceDiffX < 0)
			enemyHero->setDirection(Entity::Direction::Left);

		//enemy moves to within attacking distance of player
		if (distanceDiffX > enemyAttackDistance)
			x = enemySpeed;

		else if (distanceDiffX < -enemyAttackDistance)
			x = -enemySpeed;

		if (distanceDiffY > 10.f)
			y = enemySpeed;

		else if (distanceDiffY < -10.f)
			y = -enemySpeed;

		enemyHero->setVelocity(x, y);
	}

	else
		enemyHero->setPrevAction(Hero::Action::Stand);

	//if the enemy doesn't have to move anymore (i.e. is in attacking distance)
	return (x != 0 || y != 0);
}


void World::updateEnemyDirections(){

	for (auto& enemyHero : currentEnemies)
		enemyHero->updateDirection();
}


void World::spawnEnemies(){

	//if the closest spawn point is within the current battlefield
	while (!enemySpawns.empty() && (enemySpawns.back().x < (battlefield.getCenter().x + battlefield.getSize().x / 2.f))){

		SpawnPoint newEnemy = enemySpawns.back();

		std::shared_ptr<Hero> enemyHero(new Hero(newEnemy.heroClass, Hero::HeroFaction::Enemy, textureContainer));
		enemyHero->setPosition(newEnemy.x, newEnemy.y);
		enemyHero->setDirection(Entity::Direction::Left);

		std::shared_ptr<Hero> newPtr = enemyHero;

		sceneLayers[Ground]->attachNode(std::move(enemyHero));

		currentEnemies.push_back(newPtr);
		enemySpawns.pop_back();
	}
}


void World::addEnemySpawns(){

	addEnemySpawn(Hero::HeroClass::Druid, 500.f, 300.f);
	addEnemySpawn(Hero::HeroClass::Druid, 700.f, 350.f);

	//addEnemySpawn(Hero::HeroClass::Druid, 2000.f, 300.f);
	//addEnemySpawn(Hero::HeroClass::Druid, 2200.f, 350.f);

	std::sort(enemySpawns.begin(), enemySpawns.end(),
		[](SpawnPoint a, SpawnPoint b){

			return a.x < b.x;
		});
}

void World::addEnemySpawn(Hero::HeroClass heroClass, float x, float y){

	SpawnPoint enemy(heroClass, x, y);
	enemySpawns.push_back(enemy);
}

World::SpawnPoint::SpawnPoint(Hero::HeroClass heroClass, float x, float y):
heroClass(heroClass),
x(x),
y(y){
}