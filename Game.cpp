#include "Game.hpp"
#include <cassert>

const float Game::playerVelocity = 100.f;
const sf::Time Game::timePerFrame = sf::seconds(1.f/60.f);

Game::Game():
playerDirection(direction::none),
playerTexture(),
playerSprite(),
window(sf::VideoMode(640, 480), "At War"){

	//set up player's sprite
	assert(playerTexture.loadFromFile("Images/Archer.png"));

	playerSprite.setTexture(playerTexture);
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
void Game::updatePlayerVelocity(float& velocity){

	if (playerDirection == direction::right)
		velocity += playerVelocity;

	if (playerDirection == direction::left)
		velocity -= playerVelocity;
}

void Game::update(sf::Time elapsedTime){

	//move the player according to user input
	sf::Vector2f playerMove(0.f, 0.f);
	updatePlayerVelocity(playerMove.x);
	playerSprite.move(playerMove * elapsedTime.asSeconds());
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
				playerDirection = direction::none;
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
		playerDirection = direction::left;

	else if (key == sf::Keyboard::Right)
		playerDirection = direction::right;
}