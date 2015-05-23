#include "GameController.hpp"
#include "TitleState.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"

const sf::Time GameController::timePerFrame = sf::seconds(1.f/60.f);

GameController::GameController():
window(sf::VideoMode(900, 540), "At-War", sf::Style::Close),
textureContainer(),
fontContainer(),
playerInput(),
stateStack(State::ShareView(window, textureContainer, fontContainer, playerInput)){

	fontContainer.load(Fonts::main, "Fonts/lobsterTwo.otf");
	textureContainer.load(textureSheet::titleBackground, "Images/titleBackground.png");
	textureContainer.load(textureSheet::menuBackground, "Images/menuBackground.png");

	registerStates();
	stateStack.pushState(StateID::Title);
}

void GameController::run(){

	sf::Clock clock;
	sf::Time elapsedTimeSinceUpdate = sf::Time::Zero;

	//main loop while game window is still open
	while (window.isOpen()) {

		//fix time steps so same deltaTime for update(deltaTime) every call
		sf::Time elapsedTime = clock.restart();
		elapsedTimeSinceUpdate += elapsedTime;

		while (elapsedTimeSinceUpdate > timePerFrame) {

			elapsedTimeSinceUpdate -= timePerFrame;
			processInput();
			update(timePerFrame);

			if (stateStack.isEmpty())
				window.close();
		}

		render();
	}
}

void GameController::processInput(){

	sf::Event event;
	while (window.pollEvent(event)){

		stateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void GameController::update(sf::Time deltaTime){

	stateStack.update(deltaTime);
}

void GameController::render(){

	window.clear();
	stateStack.draw();
	window.setView(window.getDefaultView());
	window.display();
}

void GameController::registerStates(){

	stateStack.registerState<TitleState>(StateID::Title);
	stateStack.registerState<MenuState>(StateID::Menu);
	stateStack.registerState<GameState>(StateID::Game);
	stateStack.registerState<PauseState>(StateID::Pause);
}