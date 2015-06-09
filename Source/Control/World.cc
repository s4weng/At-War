#include "World.hpp"

#include "Receiver.hpp"
#include <iostream>

World::World(sf::RenderWindow& window):
window(window),
view(window.getDefaultView()),
battlefield(sf::FloatRect(0.f, 0.f, 1500.f, view.getSize().y)),
worldBounds(0.f, 0.f, 3000.f, view.getSize().y),
playerSpawnPosition(view.getSize().x/2.f, worldBounds.height - view.getSize().y/2.f),
playerHero(nullptr),
scrollSpeed(0.f){

loadTextures();
initScene();
view.setCenter(playerSpawnPosition);
addEnemySpawns();
}


void World::loadTextures(){

	//load the spritesheets
    try {

    	textureContainer.load(textureSheet::standingArcher, "Images/Archer.png");
    	textureContainer.load(textureSheet::standingArchmage, "Images/Archmage.png");
    	textureContainer.load(textureSheet::Arrow, "Images/Arrow.png");
    	textureContainer.load(textureSheet::background, "Images/Background.png");
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
	sf::Texture& texture = textureContainer.get(textureSheet::background);
	sf::IntRect textureRect(worldBounds);
	texture.setRepeated(true);

	//SpriteNode that links to background texture
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[Background]->attachNode(std::move(backgroundSprite));

	/*std::unique_ptr<Hero> oppositionHero(new Hero(Hero::heroClass::Archmage, Hero::heroFaction::Opposition, textureContainer));
	enemyHero = oppositionHero.get();
	enemyHero->setDirection(Entity::Direction::Left);
	enemyHero->setPosition(800.f, 300.f);
	sceneLayers[Ground]->attachNode(std::move(oppositionHero)); //attach hero to ground layer*/

	std::unique_ptr<Hero> mainHero(new Hero(Hero::heroClass::Archer, Hero::heroFaction::Player, textureContainer));
	playerHero = mainHero.get();
	playerHero->setDirection(Entity::Direction::Right);
	playerHero->setPosition(playerSpawnPosition);
	sceneLayers[Ground]->attachNode(std::move(mainHero));

	addEnemySpawns();
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

	//forward any command in the queue to the scene graph
	while (!commandQueue.isEmpty())
		sceneLayers[Ground]->onCommand(commandQueue.pop(), deltaTime);

	handleCollisions();
	sceneGraph.removeDead();
	spawnEnemies();

	sceneGraph.update(deltaTime, commandQueue);

	checkPlayerBounds();
}


void World::updateEntities(){

	playerHero->updateDirection();
	//enemyHero->updateDirection();
	playerHero->setVelocity(0.f, 0.f);
	
	//if (!moveTowards())
	//	enemyHero->launchAttack();	
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
			projectile.damage(10);
			//enemyHero->damage(50);
		}

	}
}


/*bool World::moveTowards(){

	float x = 0, y = 0;
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

	enemyHero->setVelocity(x,y);

	//if the enemy doesn't have to move anymore (i.e. is in attacking distance)
	return (x != 0 || y != 0);
}*/


void World::spawnEnemies(){

	//if the closest spawn point is within the current battlefield
	while (!enemySpawns.empty() && (enemySpawns.back().x < (battlefield.getCenter().x + battlefield.getSize().x / 2.f))){

		SpawnPoint newEnemy = enemySpawns.back();
		std::unique_ptr<Hero> enemyHero(new Hero(newEnemy.classOfHero, Hero::heroFaction::Opposition, textureContainer));
		enemyHero->setPosition(newEnemy.x, newEnemy.y);

		sceneLayers[Ground]->attachNode(std::move(enemyHero));
		enemySpawns.pop_back();
	}
}


void World::addEnemySpawns(){

	addEnemySpawn(Hero::heroClass::Archmage, 500.f, 300.f);
	addEnemySpawn(Hero::heroClass::Archmage, 700.f, 350.f);

	std::sort(enemySpawns.begin(), enemySpawns.end(),
		[](SpawnPoint a, SpawnPoint b){

			return a.x < b.x;
		});
}

void World::addEnemySpawn(Hero::heroClass classOfHero, float x, float y){

	SpawnPoint enemy(classOfHero, x, y);
	enemySpawns.push_back(enemy);
}

World::SpawnPoint::SpawnPoint(Hero::heroClass classOfHero, float x, float y):
classOfHero(classOfHero),
x(x),
y(y){
}