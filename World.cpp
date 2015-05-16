#include "World.hpp"
#include <iostream>

const float World::heroVelocity = 100.f;

World::World(sf::RenderWindow& window):
window(window),
view(window.getDefaultView()),
worldBounds(0.f, 0.f, 1500.f, view.getSize().y),
playerSpawnPosition(view.getSize().x/2.f, worldBounds.height - view.getSize().y/2.f),
playerHero(nullptr),
scrollSpeed(-5.f) {

loadTextures();
initScene();
view.setCenter(playerSpawnPosition);
}

void World::loadTextures(){

	//load the spritesheets
    try {

    	textureContainer.load(textureSheet::walkingArcher, "Images/ArcherWalk.png");
    	textureContainer.load(textureSheet::standingArcher, "Images/ArcherStand.png");
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

	std::unique_ptr<Hero> mainHero(new Hero(Hero::heroClass::Archer, textureContainer));
	playerHero = mainHero.get();
	playerHero->setPosition(playerSpawnPosition);
	playerHero->setVelocity(50.f, 0.f);
	sceneLayers[Ground]->attachNode(std::move(mainHero)); //attach hero to ground layer

	/*std::unique_ptr<Hero> allyHero(new Hero(Hero::heroClass::Archer, textureContainer));
	allyHero->setPosition(-80.f, 50.f);
	playerHero->attachNode(std::move(allyHero));*/
}

void World::draw(){

	window.setView(view);
	window.draw(sceneGraph);
}

void World::update(sf::Time deltaTime){

	view.move(-scrollSpeed * deltaTime.asSeconds(), 0.f);
	playerHero->setVelocity(0.f, 0.f);
	updatePlayerVelocity();
	playerHero->updateCurrentAnimation();
	playerHero->playCurrentAnimation();
	sceneGraph.update(deltaTime);
	checkPlayerBounds();
}

void World::checkPlayerBounds(){

	//ensure player doesn't leave visible area of our world
	sf::FloatRect viewBounds(view.getCenter() - view.getSize()/2.f, view.getSize());
	const float borderDistance = 18.f;

	sf::Vector2f position = playerHero->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	playerHero->setPosition(position);
}

void World::updatePlayerVelocity(){

	if (playerHero->getPlayerAction() == Hero::animationAction::walkRight)
		playerHero->setVelocity(heroVelocity + scrollSpeed, 0.f);

	if (playerHero->getPlayerAction() == Hero::animationAction::walkLeft)
		playerHero->setVelocity(-heroVelocity - scrollSpeed, 0.f);
}

void World::handleInput(sf::Keyboard::Key key){

	//set up the direction the player's sprite will face/move
	if (key == sf::Keyboard::Left)
		playerHero->setPlayerAction(Hero::animationAction::walkLeft);

	else if (key == sf::Keyboard::Right)
		playerHero->setPlayerAction(Hero::animationAction::walkRight);
}

void World::handleReleasedKey(){

	if (playerHero->getPlayerAction() == Hero::animationAction::walkLeft)
		playerHero->setPlayerAction(Hero::animationAction::standLeft);
	else
		playerHero->setPlayerAction(Hero::animationAction::standRight);

}