#include "World.hpp"

#include <iostream>

World::World(sf::RenderWindow& window):
window(window),
view(window.getDefaultView()),
worldBounds(0.f, 0.f, 1500.f, view.getSize().y),
playerSpawnPosition(view.getSize().x/2.f, worldBounds.height - view.getSize().y/2.f),
playerHero(nullptr),
enemyHero(nullptr),
scrollSpeed(-10.f) {

loadTextures();
initScene();
view.setCenter(playerSpawnPosition);
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

	std::unique_ptr<Hero> oppositionHero(new Hero(Entity::Direction::Left, Hero::heroClass::Archmage, Hero::heroFaction::Opposition, textureContainer));
	enemyHero = oppositionHero.get();
	enemyHero->setPosition(800.f, 300.f);
	sceneLayers[Ground]->attachNode(std::move(oppositionHero)); //attach hero to ground layer

	std::unique_ptr<Hero> mainHero(new Hero(Entity::Direction::Right, Hero::heroClass::Archer, Hero::heroFaction::Player, textureContainer));
	playerHero = mainHero.get();
	playerHero->setPosition(playerSpawnPosition);
	sceneLayers[Ground]->attachNode(std::move(mainHero));
}

void World::draw(){

	window.setView(view);
	window.draw(sceneGraph);
}

void World::update(sf::Time deltaTime){

	view.move(-scrollSpeed * deltaTime.asSeconds(), 0.f);
	playerHero->setVelocity(0.f, 0.f);
	enemyHero->setVelocity(0.f, 0.f);
	
	if (moveTowards())
		enemyHero->launchAttack();

	//forward any command in the queue to the scene graph
	while (!commandQueue.isEmpty())
		sceneGraph.onCommand(commandQueue.pop(), deltaTime);

	sceneGraph.update(deltaTime, commandQueue);
	checkPlayerBounds();
}

void World::checkPlayerBounds(){

	//ensure player doesn't leave visible area of our world
	sf::FloatRect viewBounds(view.getCenter() - view.getSize()/2.f, view.getSize());
	const float borderDistance = 18.f;

	sf::Vector2f playerPosition = playerHero->getPosition();
	playerPosition.x = std::max(playerPosition.x, viewBounds.left + borderDistance);
	playerPosition.x = std::min(playerPosition.x, viewBounds.left + viewBounds.width - borderDistance);
	playerPosition.y = std::max(playerPosition.y, viewBounds.top + borderDistance);
	playerPosition.y = std::min(playerPosition.y, viewBounds.top + viewBounds.height - borderDistance);
	playerHero->setPosition(playerPosition);
}

CommandQueue& World::getCommandQueue(){

	return commandQueue;
}

bool World::moveTowards(){

	float x, y = 0;
	float enemyAttackDistance = dataTable[enemyHero->getHeroClass()].attackDistance;
	float enemySpeed = dataTable[enemyHero->getHeroClass()].speed;
	sf::Vector2f playerPosition = playerHero->getPosition();
	sf::Vector2f enemyPosition = enemyHero->getPosition();

	if (playerPosition.x - enemyPosition.x > enemyAttackDistance)
		x = enemySpeed;

	else if (playerPosition.x - enemyPosition.x < -enemyAttackDistance)
		x = -enemySpeed;

	if (playerPosition.y - enemyPosition.y > 10.f)
		y = enemySpeed;

	else if (playerPosition.y - enemyPosition.y < -10.f)
		y = -enemySpeed;

	enemyHero->setVelocity(x,y);

	return (x == 0 && y == 0);
}