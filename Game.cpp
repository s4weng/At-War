#include "Game.hpp"
#include <cassert>
#include <iostream>

const float Game::playerVelocity = 100.f;
const sf::Time Game::timePerFrame = sf::seconds(1.f/60.f);

Game::Game():
playerAction(animationAction::standRight),
textureContainer(),
playerTextureWalk(),
playerTextureStand(),
walkingRight(),
walkingLeft(),
standingRight(),
standingLeft(),
currentAnimation(),
playerSprite(),
window(sf::VideoMode(640, 480), "At War"){

	setAnimation();
	//set up player's sprite
	/*assert(playerTexture.loadFromFile("Images/Archer.png"));

	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(50.f, 200.f);*/
}

void Game::setAnimation(){

    //load the spritesheets
    try {

    	textureContainer.load(textureSheet::walkingArcher, "Images/ArcherWalk.png");
    	textureContainer.load(textureSheet::standingArcher, "Images/ArcherStand.png");
    	textureContainer.load(textureSheet::background, "Images/Background.png");
    }

    catch (std::runtime_error &e){

    	std::cout << "Exception occurred: " << e.what() << std::endl;
    	return;
    }

    /*
    assert(playerTextureWalk.loadFromFile("Images/ArcherWalk.png"));
    assert(playerTextureStand.loadFromFile("Images/ArcherStand.png"));*/

    //set up the animation frames
    walkingRight.setSpriteSheet(textureContainer.get(textureSheet::walkingArcher));
    walkingRight.addFrame(sf::IntRect(11, 11, 48, 70));
    walkingRight.addFrame(sf::IntRect(91, 12, 48, 70));
    walkingRight.addFrame(sf::IntRect(167, 8, 48, 70));
    walkingRight.addFrame(sf::IntRect(248, 10, 48, 70));
    walkingRight.addFrame(sf::IntRect(329, 10, 48, 70));

    walkingLeft.setSpriteSheet(textureContainer.get(textureSheet::walkingArcher));;
    walkingLeft.addFrame(sf::IntRect(330, 97, 48, 70));
    walkingLeft.addFrame(sf::IntRect(246, 97, 48, 70));
    walkingLeft.addFrame(sf::IntRect(172, 97, 48, 70));
    walkingLeft.addFrame(sf::IntRect(93, 97, 48, 70));
    walkingLeft.addFrame(sf::IntRect(9, 95, 48, 70));

    standingRight.setSpriteSheet(textureContainer.get(textureSheet::standingArcher));
    standingRight.addFrame(sf::IntRect(9,9,48,70));

    standingLeft.setSpriteSheet(textureContainer.get(textureSheet::standingArcher));
    standingLeft.addFrame(sf::IntRect(10,98,48,70));

    //set animation
    currentAnimation = &standingRight;

    //set up AnimatedSprite
    playerSprite.setPosition(50.f, 200.f);	
}

void Game::run(){

	sf::Clock clock;
	sf::Time elapsedTimeSinceUpdate = sf::Time::Zero;

	//main loop while game window is still open
	while (window.isOpen()) {

		//fix time steps so same deltaTime for update(deltaTime) every call
		sf::Time elapsedTime = clock.restart();
		elapsedTimeSinceUpdate += elapsedTime;

		while (elapsedTimeSinceUpdate > timePerFrame) {

			elapsedTimeSinceUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}

		render();
	}
}

//helper function
void Game::updatePlayerVelocity(float &velocity){

	if (playerAction == animationAction::walkRight)
		velocity += playerVelocity;

	if (playerAction == animationAction::walkLeft)
		velocity -= playerVelocity;
}

void Game::updateCurrentAnimation(){

	if (playerAction == animationAction::walkRight)
		currentAnimation = &walkingRight;

	else if (playerAction == animationAction::walkLeft)
		currentAnimation = &walkingLeft;

	else if (playerAction == animationAction::standRight)
		currentAnimation = &standingRight;

	else
		currentAnimation = &standingLeft;
}

void Game::update(sf::Time elapsedTime){

	//move the player according to user input
	sf::Vector2f playerMove(0.f, 0.f);
	updatePlayerVelocity(playerMove.x);
	updateCurrentAnimation();
	playerSprite.play(*currentAnimation);
	playerSprite.move(playerMove * elapsedTime.asSeconds());
	playerSprite.update(elapsedTime);
}

void Game::render(){

	window.clear();
	window.draw(playerSprite);
	window.display();
}

void Game::processEvents(){

	sf::Event event;

	//poll input events
	while (window.pollEvent(event)){

		switch (event.type){

			case sf::Event::KeyPressed:

				handleInput(event.key.code);
				break;

			case sf::Event::KeyReleased:

				if (playerAction == animationAction::walkLeft)
					playerAction = animationAction::standLeft;
				else
					playerAction = animationAction::standRight;
				break;

			case sf::Event::Closed:

				window.close();
				break;
		}
	}
}

void Game::handleInput(sf::Keyboard::Key key){

	//set up the direction the player's sprite will face/move
	if (key == sf::Keyboard::Left)
		playerAction = animationAction::walkLeft;

	else if (key == sf::Keyboard::Right)
		playerAction = animationAction::walkRight;
}