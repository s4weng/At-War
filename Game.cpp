#include "Game.hpp"
#include <cassert>
#include <iostream>

const sf::Time Game::timePerFrame = sf::seconds(1.f/60.f);

Game::Game():
window(sf::VideoMode(640, 480), "At War"),
world(window) {
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
			world.update(timePerFrame);
		}

		render();
	}
}

void Game::render(){

	window.clear();
	world.draw();
	window.setView(window.getDefaultView());
	window.display();
}

void Game::processEvents(){

	CommandQueue& commandQueue = world.getCommandQueue();

	sf::Event event;

	while (window.pollEvent(event)){

		if (event.type == sf::Event::KeyReleased)
			world.setReleasedKeyAnimation();

		else {

			playerInput.handleEvent(event, commandQueue);
			world.setInputAnimation(event.key.code);
		}

		if (event.type == sf::Event::Closed)
			window.close();
	}

	playerInput.handleRealtimeInput(commandQueue);
}