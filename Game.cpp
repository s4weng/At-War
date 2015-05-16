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

	sf::Event event;

	//poll input events
	while (window.pollEvent(event)){

		switch (event.type){

			case sf::Event::KeyPressed:

				world.handleInput(event.key.code);
				break;

			case sf::Event::KeyReleased:

				world.handleReleasedKey();
				break;

			case sf::Event::Closed:

				window.close();
				break;
		}
	}
}